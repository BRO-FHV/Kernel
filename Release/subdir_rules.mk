################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
boot.obj: ../boot.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/arm_5.1.1/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="C:/ti/ccsv5/tools/compiler/arm_5.1.1/include" --include_path="C:/Users/GIGI/GitWorkspace/BRO-FHV/Hal" --include_path="C:/Users/GIGI/GitWorkspace/BRO-FHV/Driver" --include_path="C:/Users/GIGI/GitWorkspace/BRO-FHV/Scheduler" --define=am3359 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="boot.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

intvecs.obj: ../intvecs.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/arm_5.1.1/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="C:/ti/ccsv5/tools/compiler/arm_5.1.1/include" --include_path="C:/Users/GIGI/GitWorkspace/BRO-FHV/Hal" --include_path="C:/Users/GIGI/GitWorkspace/BRO-FHV/Driver" --include_path="C:/Users/GIGI/GitWorkspace/BRO-FHV/Scheduler" --define=am3359 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="intvecs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/arm_5.1.1/bin/armcl" -mv7A8 --code_state=32 --abi=eabi -me -O2 --include_path="C:/ti/ccsv5/tools/compiler/arm_5.1.1/include" --include_path="C:/Users/GIGI/GitWorkspace/BRO-FHV/Hal" --include_path="C:/Users/GIGI/GitWorkspace/BRO-FHV/Driver" --include_path="C:/Users/GIGI/GitWorkspace/BRO-FHV/Scheduler" --define=am3359 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


