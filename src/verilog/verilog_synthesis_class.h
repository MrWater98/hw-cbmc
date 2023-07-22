/*******************************************************************\

Module: Verilog Synthesis

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_VERILOG_SYNTHESIS_CLASS_H
#define CPROVER_VERILOG_SYNTHESIS_CLASS_H

#include <cassert>
#include <map>
#include <unordered_set>

#include <util/mathematical_expr.h>
#include <util/mp_arith.h>
#include <util/options.h>
#include <util/std_expr.h>
#include <util/string_hash.h>

#include "verilog_typecheck_base.h"
#include "verilog_symbol_table.h"

/*******************************************************************\

   Class: verilog_synthesist

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

class verilog_synthesist:
  public verilog_typecheck_baset,
  public verilog_symbol_tablet
{
public:
  verilog_synthesist(
    symbol_tablet &_symbol_table,
    const irep_idt &_module,
    const optionst &_options,
    message_handlert &_message_handler):
    verilog_typecheck_baset(ns, _message_handler),
    verilog_symbol_tablet(_symbol_table),
    ns(_symbol_table),
    options(_options),
    value_map(NULL),
    module(_module),
    temporary_counter(0)
  {
  }

  virtual void typecheck();

protected:
  const namespacet ns;
  const optionst &options;
 
  enum class event_guardt { NONE, CLOCK, COMBINATIONAL };
  
  inline std::string as_string(event_guardt g)
  {
    return g==event_guardt::CLOCK?"clocked":
           g==event_guardt::COMBINATIONAL?"combinational":
           "";
  }
  
  // list of vector-indices or array indices
  typedef std::list<mp_integer> membert;

  typedef std::list<membert> member_listt;
  
  static bool disjoint(const membert &a, const membert &b);
  
  // global assignment map
  class assignmentt
  {
  public:
    struct datat
    {
      exprt value;

      // array/bv indices that are already assigned to
      member_listt assigned_previous, assigned_current;
      
      datat():value(nil_exprt()) { }
      
      void move_assignments()
      {
        assigned_previous.splice(
          assigned_previous.end(),
          assigned_current);
      }
      
    } init, next;

    // only relevant for 'next'
    event_guardt type;

    assignmentt():type(event_guardt::NONE)
    {
    }
  };
   
  typedef std::map<irep_idt, assignmentt> assignmentst;
  assignmentst assignments;
  
  // for assumes
  typedef std::list<exprt> invarst;
  invarst invars;

  enum class constructt { INITIAL, ALWAYS, OTHER };
  enum class symbol_statet { NONE, SYMBOL, CURRENT, FINAL };
  constructt construct;
  event_guardt event_guard;
 
  // current value map
  class value_mapt
  {
  public:
    class mapt
    {
    public:
      typedef std::map<irep_idt, exprt> symbol_mapt;
      symbol_mapt symbol_map;

      std::set<irep_idt> changed;
      
      void assign(const irep_idt &symbol, const exprt &rhs)
      {
        changed.insert(symbol);
        symbol_map[symbol]=rhs;
      }

    } current, final;

    void clear_changed()
    {
      current.changed.clear();
      final.changed.clear();
    }
  };
   
  exprt current_value(
    const value_mapt::mapt &map,
    const symbolt &symbol,
    bool use_previous_assignments);
  
  inline exprt current_value(const symbolt &symbol)
  {
    assert(value_map!=NULL);
    return current_value(value_map->current, symbol, false);
  }

  inline exprt final_value(const symbolt &symbol)
  {
    assert(value_map!=NULL);
    return current_value(value_map->final, symbol, true);
  }

  value_mapt *value_map;
   
  void merge(
    const exprt &guard,
    const value_mapt::mapt &true_map,
    const value_mapt::mapt &false_map,
    bool use_previous_assignments,
    value_mapt::mapt &dest);
                                             
  const irep_idt &module;

  typedef std::unordered_set<irep_idt, irep_id_hash> local_symbolst;
  local_symbolst local_symbols, new_wires;

  void assignment(
    const exprt &lhs,
    const exprt &rhs,
    bool blocking);

  void assignment_rec(
    const exprt &lhs,
    exprt &rhs,
    exprt &new_value);

  const symbolt &assignment_symbol(const exprt &lhs);

  void assignment_member_rec(
    const exprt &lhs,
    membert &member,
    assignmentt::datat &data);

  void add_assignment_member(
    const exprt &lhs,
    const membert &member,
    assignmentt::datat &data);

  // module items
  virtual void convert_module_items(symbolt &);
  void synth_module_item(const class verilog_module_itemt &, transt &);
  void synth_always(const class verilog_alwayst &);
  void synth_initial(const class verilog_initialt &);
  void synth_assert_module_item(const class verilog_module_itemt &);
  void synth_assume_module_item(const class verilog_module_itemt &);
  void synth_continuous_assign(const class verilog_continuous_assignt &);
  void synth_force_rec(exprt &lhs, exprt &rhs, transt &);
  void synth_module_instance(const class verilog_instt &, transt &);
  void synth_module_instance_builtin(const class verilog_inst_builtint &, transt &);

  // statements
  void synth_statement(const class verilog_statementt &);
  void synth_decl(const class verilog_declt &);
  void synth_block(const class verilog_blockt &);
  void synth_case(const class verilog_statementt &);
  void synth_if(const class verilog_ift &);
  void synth_event_guard(const class verilog_event_guardt &);
  void synth_delay(const class verilog_delayt &);
  void synth_for(const class verilog_fort &);
  void synth_force(const class verilog_forcet &);
  void synth_force_rec(const exprt &lhs, const exprt &rhs);
  void synth_forever(const class verilog_forevert &);
  void synth_while(const class verilog_whilet &);
  void synth_repeat(const class verilog_repeatt &);
  void synth_function_call_or_task_enable(const class verilog_function_callt &);
  void synth_expr(exprt &expr, symbol_statet symbol_state);
  void synth_assign(const exprt &, bool blocking);
  void synth_assert(const class verilog_assertt &);
  void synth_assume(const class verilog_assumet &);
  void synth_prepostincdec(const class verilog_statementt &);
  void synth_assignments(transt &);

  void post_process_initial(exprt &constraints);
  void post_process_wire(const irep_idt &identifier, exprt &expr);
  
  exprt case_comparison(const exprt &case_operand, const exprt &pattern);
  
  typedef enum { CURRENT, NEXT } curr_or_nextt;

  exprt symbol_expr(
    const symbolt &symbol,
    curr_or_nextt curr_or_next);

  void extract_expr(exprt &dest, unsigned bit);

  void synth_assignments(
    const symbolt &symbol,
    curr_or_nextt curr_or_next,
    exprt &new_value,
    exprt &constraints);

  exprt synth_case_values(
    const exprt &values,
    const exprt &case_operand);

  void expand_module_instance(
    const symbolt &symbol,
    const exprt &op,
    transt &trans);

  void expand_hierarchical_identifier(
    class hierarchical_identifier_exprt &expr,
    symbol_statet symbol_state);

  void expand_function_call(class function_call_exprt &call);
  
  typedef std::map<irep_idt, exprt> replace_mapt;

  void instantiate_ports(
    const irep_idt &instance,
    const exprt &inst,
    const symbolt &symbol,
    const replace_mapt &replace_map,
    transt &trans);

  bool replace_symbols(const replace_mapt &what, exprt &dest);
  void replace_symbols(const irep_idt &target, exprt &dest);
  
  void instantiate_port(
    const exprt &symbol_expr,
    const exprt &value,
    const replace_mapt &replace_map,
    transt &trans);

  void replace_by_wire(exprt &expr, const symbolt &base);
    
  // This map contains the values of all variables
  // fixed to a constant during synthesis.
  typedef std::map<irep_idt, mp_integer> valuest;
  valuest values;
  
  unsigned temporary_counter;
};

#endif
