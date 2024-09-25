PY?=python3
PROXY?=
BLUE=\033[0;34m
NC=\033[0m # No Color
SPHINX_BUILD_OPTIONS = html dirhtml singlehtml epub latex htmlhelp qthelp devhelp applehelp man texinfo text gettext doctest linkcheck xml pseudoxml
DIR_PREFIX_MAP = \
	c_:c \
	cp_:cplusplus \
	cs_:csharp \
	fr_:fortran \
	ja_:java \
	js_:javascript \
	lu_:lua \
	py_:python \
	rs_:rust

.PHONY: help
help: LICENSE
	@echo "This project has a number of recipes that are delegated to other Makefiles. The following jobs are available with no prefix"
	@echo "  $(BLUE)clean$(NC)	Cleans up any stray files"
	@$(foreach option,$(SPHINX_BUILD_OPTIONS), \
		echo "  $(BLUE)$(option)$(NC)	Forwarded to sphinx in the docs dir"; \
	)
	@echo "All other inputs are redirected to the all_ prefix, which will run it for each language. Note that this may error if the target is not found in all languages"
	@echo
	@echo "The following jobs are available under the docs_ prefix"
	@$(MAKE) docs_help $(MFLAGS) --no-print-directory
	@echo
	@$(foreach mapping,$(DIR_PREFIX_MAP), \
		echo "The following jobs are available under the $(word 1,$(subst :, ,$(mapping))) prefix"; \
		$(MAKE) $(word 1,$(subst :, ,$(mapping)))help $(MFLAGS) --no-print-directory; \
		echo; \
	)

.PHONY: $(SPHINX_BUILD_OPTIONS)
$(SPHINX_BUILD_OPTIONS): LICENSE
	@$(MAKE) docs_$@ $(MFLAGS) --no-print-directory

.PHONY: clean
clean:
	@$(MAKE) all_clean docs_clean -j --no-print-directory $(MFLAGS)

# This definition generates our prefix rules
define make_prefix_rule
.PHONY: $(1)%
$(1)%: LICENSE
	@$(MAKE) -C $(2) $$* $(MFLAGS) --no-print-directory
endef

# Generate rules for each directory in the mapping
$(eval $(call make_prefix_rule,docs_,docs))
$(foreach mapping,$(DIR_PREFIX_MAP),$(eval $(call make_prefix_rule,$(word 1,$(subst :, ,$(mapping))),$(word 2,$(subst :, ,$(mapping))))))

.PHONY: all_%
all_%:
	@$(MAKE) $(foreach mapping,$(DIR_PREFIX_MAP),$(word 1,$(subst :, ,$(mapping)))$*) $(MFLAGS) --no-print-directory

%:
	@$(MAKE) all_$* $(MFLAGS) --no-print-directory
