/*******************************************************************\

Module: k Induction

Author: Daniel Kroening, daniel.kroening@inf.ethz.ch

\*******************************************************************/

#include <trans-word-level/instantiate_word_level.h>
#include <trans-word-level/property.h>
#include <trans-word-level/trans_trace_word_level.h>
#include <trans-word-level/unwind.h>

#include <solvers/sat/satcheck.h>
#include <solvers/flattening/boolbv.h>

#include "ebmc_base.h"
#include "k_induction.h"

/*******************************************************************\

   Class: k_inductiont

 Purpose:

\*******************************************************************/

class k_inductiont:public ebmc_baset
{
public:
  k_inductiont(const cmdlinet &_cmdline,
               ui_message_handlert &_ui_message_handler)
      : ebmc_baset(_cmdline, _ui_message_handler), ns{symbol_table} {}

  int operator()();

protected:
  namespacet ns;
  int induction_base();
  int induction_step();
};

/*******************************************************************\

Function: do_k_induction

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

int do_k_induction(
  const cmdlinet &cmdline,
  ui_message_handlert &ui_message_handler)
{
  return k_inductiont(cmdline, ui_message_handler)();
}

/*******************************************************************\

Function: k_inductiont::do_k_induction

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

int k_inductiont::operator()()
{
  if(get_bound()) return 1;

  int result=get_model();
  if(result!=-1) return result;

  if(properties.empty())
  {
    error() << "no properties" << eom;
    return 1;
  }

  // do induction base
  result=induction_base();
  if(result!=-1) return result;

  // do induction step
  result=induction_step();
  
  report_results();
  
  return result;
}

/*******************************************************************\

Function: k_inductiont::induction_base

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

int k_inductiont::induction_base()
{
  PRECONDITION(trans_expr.has_value());
  status() << "Induction Base" << eom;

  satcheckt satcheck{*message_handler};
  boolbvt solver(ns, satcheck, *message_handler);

  ::unwind(*trans_expr, *message_handler, solver, bound + 1, ns, true);

  int result=finish_bmc(solver);
  
  if(result!=0 && result!=10)
    return result;
  else
    return -1;
}

/*******************************************************************\

Function: k_inductiont::induction_step

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

int k_inductiont::induction_step()
{
  PRECONDITION(trans_expr.has_value());
  status() << "Induction Step" << eom;

  unsigned no_timeframes=bound+1;

  for(auto &p_it : properties)
  {
    if(p_it.is_disabled() ||
       p_it.is_failure())
      continue;

    satcheckt satcheck{*message_handler};
    boolbvt solver(ns, satcheck, *message_handler);

    // *no* initial state
    unwind(*trans_expr, *message_handler, solver, no_timeframes, ns, false);

    exprt property(p_it.expr);

    if(property.id()!=ID_sva_always &&
       property.id()!=ID_AG)
    {
      error() << "unsupported property - only SVA always or AG implemented" << eom;
      return 1;
    }
    
    assert(property.operands().size()==1);

    const exprt &p=property.op0();

    // assumption: time frames 0,...,k-1
    for(unsigned c=0; c<no_timeframes-1; c++)
    {
      exprt tmp=
        instantiate(p, c, no_timeframes-1, ns);
      solver.set_to_true(tmp);
    }
    
    // property: time frame k
    {
      exprt tmp=
        instantiate(p, no_timeframes-1, no_timeframes, ns);
      solver.set_to_false(tmp);
    }    

    decision_proceduret::resultt dec_result=
      solver.dec_solve();
    
    switch(dec_result)
    {
    case decision_proceduret::resultt::D_SATISFIABLE:
      result() << "SAT: inductive proof failed, k-induction is inconclusive" << eom;
      p_it.make_unknown();
      break;

    case decision_proceduret::resultt::D_UNSATISFIABLE:
      result() << "UNSAT: inductive proof successful, property holds" << eom;
      p_it.make_success();
      break;

    case decision_proceduret::resultt::D_ERROR:
      error() << "Error from decision procedure" << eom;
      return 2;

    default:
      error() << "Unexpected result from decision procedure" << eom;
      return 1;
    }
  }

  // We return '0' if the property holds,
  // and '10' if it is violated.
  return property_failure()?10:0; 
}
