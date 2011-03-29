.PHONY: clean All

All:
	@echo ----------Building project:[ workplace - Debug ]----------
	@cd "../../../ISEL/semestre6/SE2/workplace" && "$(MAKE)" -f "workplace.mk"
clean:
	@echo ----------Cleaning project:[ workplace - Debug ]----------
	@cd "../../../ISEL/semestre6/SE2/workplace" && "$(MAKE)" -f "workplace.mk" clean
