/*******************************************************************\

Module: Unwinding Netlists

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include "unwind_netlist.h"
#include "instantiate_netlist.h"

#include <util/ebmc_util.h>

/*******************************************************************\

Function: unwind

  Inputs:

 Outputs:

 Purpose: Unwind timeframe by timeframe

\*******************************************************************/

void unwind(
  const netlistt &netlist,
  bmc_mapt &bmc_map,
  messaget &message,
  cnft &solver,
  bool add_initial_state,
  unsigned t)
{
  bool first=(t==0);
  bool last=(t==bmc_map.timeframe_map.size()-1);

  if(add_initial_state && first)
  {
    // do initial state
    message.status() << "Initial State" << messaget::eom;
    
    for(const auto & n : netlist.initial)
      solver.l_set_to(bmc_map.translate(0, n), true);
  }

  // do transitions
  if(last)
    message.status() << "Transition " << t << messaget::eom;
  else
    message.status() << "Transition " << t << "->" << t+1 << messaget::eom;
  
  const bmc_mapt::timeframet &timeframe=bmc_map.timeframe_map[t];
  
  for(std::size_t n=0; n<timeframe.size(); n++)
  {
    const aig_nodet &node=netlist.get_node(literalt(n, false));

    if(node.is_and())
    {
      literalt la=bmc_map.translate(t, node.a);
      literalt lb=bmc_map.translate(t, node.b);

      cnf_gate_and(solver, la, lb, timeframe[n].solver_literal);
    }
  }

  // general AIG constraints
  for(const auto & c : netlist.constraints)
    solver.l_set_to(bmc_map.translate(t, c), true);

  // transition constraints
  for(const auto & c : netlist.transition)
    solver.l_set_to(bmc_map.translate(t, c), true);

  if(!last)
  {     
    // joining the latches between timeframe and timeframe+1
    for(var_mapt::mapt::const_iterator
        v_it=netlist.var_map.map.begin();
        v_it!=netlist.var_map.map.end();
        v_it++)
    {
      const var_mapt::vart &var=v_it->second;
      if(var.is_latch())
      {
        for(std::size_t bit_nr=0; bit_nr<var.bits.size(); bit_nr++)
        {
          const var_mapt::vart::bitt &bit=var.bits[bit_nr];
          
          literalt l_from=bit.next;
          literalt l_to=bit.current;

          solver.set_equal(
            bmc_map.translate(t, l_from),
            bmc_map.translate(t+1, l_to));
        }
      }
    }
  }
}

/*******************************************************************\

Function: unwind

  Inputs:

 Outputs:

 Purpose: 

\*******************************************************************/

void unwind(
  const netlistt &netlist,
  bmc_mapt &bmc_map,
  messaget &message,
  cnft &solver,
  bool add_initial_state)
{
  for(unsigned t=0; t<bmc_map.timeframe_map.size(); t++)
    unwind(netlist, bmc_map, message, solver, add_initial_state, t);
}

/*******************************************************************\

Function: unwind_property

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void unwind_property(
  const bmc_mapt &bmc_map,
  literalt property_node,
  bvt &prop_bv)
{
  prop_bv.resize(bmc_map.timeframe_map.size());

  for(unsigned t=0;
      t<bmc_map.timeframe_map.size();
      t++)
  {
    literalt l=bmc_map.translate(t, property_node);
    prop_bv[t]=l;
  }
}

/*******************************************************************\

Function: unwind_property

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void unwind_property(
  const exprt &property_expr,
  bvt &prop_bv,
  message_handlert &message_handler,
  propt &solver,
  const bmc_mapt &map,
  const namespacet &ns)
{
  if(property_expr.is_true())
  {
    prop_bv.resize(map.get_no_timeframes(), const_literal(true));
    return;
  }
  
  if(property_expr.id()!=ID_AG &&
     property_expr.id()!=ID_sva_always)
    throw "unsupported property - only SVA always implemented";
  
  assert(property_expr.operands().size()==1);

  const exprt &p=property_expr.op0();
  
  for(unsigned c=0; c<map.get_no_timeframes(); c++)
  {
    literalt l=instantiate_convert(solver, map, p, c, c+1, ns, message_handler);
    prop_bv.push_back(l);
  }
}

