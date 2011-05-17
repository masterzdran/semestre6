.PHONY: clean All

All:
	@echo ----------Building project:[ workplace - Debug ]----------
	@"$(MAKE)" -f "workplace.mk"
clean:
	@echo ----------Cleaning project:[ workplace - Debug ]----------
	@"$(MAKE)" -f "workplace.mk" clean
