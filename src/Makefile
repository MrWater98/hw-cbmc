DIRS = ebmc hw-cbmc trans-word-level trans-netlist verilog vhdl smvlang ic3 aiger

EBMC_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
CPROVER_DIR = $(EBMC_DIR)/../lib/cbmc/src
export CPROVER_DIR
export EBMC_DIR

.PHONY: cclean all  hw-cbmc.dir ebmc.dir

all: hw-cbmc.dir ebmc.dir

cclean: clean-verilog clean-vhdl clean-smvlang

clean-verilog:
	@echo "Cleaning up verilog directory..."
	$(MAKE) clean -C verilog

clean-vhdl:
	@echo "Cleaning up vhdl directory..."
	$(MAKE) clean -C vhdl

clean-smvlang:
	@echo "Cleaning up smvlang directory..."
	$(MAKE) clean -C smvlang



$(patsubst %, %.dir, $(DIRS)):
	## Entering $(basename $@)
	$(MAKE) $(MAKEARGS) -C $(basename $@)

# Dependencies

ebmc.dir: trans-word-level.dir trans-netlist.dir verilog.dir vhdl.dir \
      smvlang.dir ic3.dir aiger.dir cprover.dir

hw-cbmc.dir: trans-word-level.dir trans-netlist.dir verilog.dir \
         vhdl.dir smvlang.dir cprover.dir

# ebmc.dir: trans-word-level.dir trans-netlist.dir \
#      ic3.dir aiger.dir cprover.dir

# hw-cbmc.dir: trans-word-level.dir trans-netlist.dir \
#     	cprover.dir

# building cbmc proper
.PHONY: cprover.dir
cprover.dir:
	$(MAKE) $(MAKEARGS) -C $(CPROVER_DIR) \
  CP_EXTRA_CXXFLAGS='-D"LOCAL_IREP_IDS=<$(EBMC_DIR)/hw_cbmc_irep_ids.h>"'

clean: $(patsubst %, %_clean, $(SUBDIRS))


$(patsubst %, %_clean, $(SUBDIRS)):
	if [ -e $(patsubst %_clean, %, $@)/. ] ; then \
	        $(MAKE) $(MAKEARGS) -C $(patsubst %_clean, %, $@) clean ; \
	fi

