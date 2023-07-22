/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_VHDL_LANGUAGE_H
#define CPROVER_VHDL_LANGUAGE_H

#include <util/make_unique.h>
#include <util/options.h>

#include <langapi/language.h>

#include "vhdl_parse_tree.h"

class vhdl_languaget:public languaget
{
public:
  bool preprocess(
    std::istream &instream,
    const std::string &path,
    std::ostream &outstream) override;

  bool parse(
    std::istream &instream,
    const std::string &path) override;
             
  void dependencies(
    const std::string &module,
    std::set<std::string> &module_set) override;
                            
  void modules_provided(
    std::set<std::string> &module_set) override;

  bool interfaces(
    symbol_tablet &symbol_table) override;

  bool typecheck(
    symbol_tablet &symbol_table,
    const std::string &module) override;
  
  void show_parse(std::ostream &out) override;
  
  ~vhdl_languaget() override { }
  
  bool from_expr(
    const exprt &expr, std::string &code,
    const namespacet &ns) override;

  bool from_type(
    const typet &type, std::string &code,
    const namespacet &ns) override;

  bool to_expr(
    const std::string &code,
    const std::string &module,
    exprt &expr,
    const namespacet &ns) override;

  bool generate_support_functions(symbol_tablet &) override
  {
    return false;
  }

  std::unique_ptr<languaget> new_language() override
  { return util_make_unique<vhdl_languaget>(); }
   
  std::string id() const override { return "VHDL"; }
  std::string description() const override { return "VHDL"; }

  std::set<std::string> extensions() const override
  { 
    return { "vhd", "vhdl" };
  }

  vhdl_parse_treet &get_parse_tree()
  {
    return parse_tree;
  }
  
  optionst options;
  
  vhdl_languaget()
  {
    options.set_option("flatten_hierarchy", true);
  }

protected:
  vhdl_parse_treet parse_tree;
};
 
std::unique_ptr<languaget> new_vhdl_language();

#endif
