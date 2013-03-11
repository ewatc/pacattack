.PHONY: clean All

All:
	@echo "----------Building project:[ pacattack - Debug ]----------"
	@$(MAKE) -f  "pacattack.mk"
clean:
	@echo "----------Cleaning project:[ pacattack - Debug ]----------"
	@$(MAKE) -f  "pacattack.mk" clean
