################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files/CodeComposerStudio53/ccsv5/tools/compiler/arm_5.0.1/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --define=%OOS_USER% --define=omap3530 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main_daniel.obj: ../main_daniel.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files/CodeComposerStudio53/ccsv5/tools/compiler/arm_5.0.1/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --define=%OOS_USER% --define=omap3530 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="main_daniel.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main_manuel.obj: ../main_manuel.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files/CodeComposerStudio53/ccsv5/tools/compiler/arm_5.0.1/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --define=%OOS_USER% --define=omap3530 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="main_manuel.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main_martin.obj: ../main_martin.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files/CodeComposerStudio53/ccsv5/tools/compiler/arm_5.0.1/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --define=%OOS_USER% --define=omap3530 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="main_martin.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main_matthias.obj: ../main_matthias.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files/CodeComposerStudio53/ccsv5/tools/compiler/arm_5.0.1/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -g --define=%OOS_USER% --define=omap3530 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="main_matthias.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


