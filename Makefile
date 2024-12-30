



LOCAL_MODULE_DEPENDS += init
LOCAL_MODULE_DEPENDS += libs




##################################################################################
# DO NOT EDIT THIS FILE IF YOU DON'T KNOW WHAT YOU DO
##################################################################################

PROJECT_PATH += demo/bme280
LOCAL_MODULE_DEPENDS += ${PROJECT_PATH}

CFG_FILE = ${SOFT_WORKDIR}/${PROJECT_PATH}/config.mk
IS_CFG_FILE_EXIST = $(shell if [ -f $(CFG_FILE) ]; then echo "exist"; else echo "notexist"; fi;)
ifeq "${strip ${IS_CFG_FILE_EXIST}}" "exist"
	include ${CFG_FILE}
endif


include module_list.mk
#do not edit anything about the description above, if you don not know what you are doing

##################################################################################
#you can add you module here like the following comment
#LOCAL_MODULE_DEPENDS += project/module 
#this comment will add a module name project/module in project/module path
##################################################################################


# Set this to any non-null string to signal a module which
# generates a binary (must contain a "main" entry point). 
# If left null, only a library will be generated.
IS_ENTRY_POINT := yes

# Assembly / C source code
S_SRC := 
C_SRC := 

include ${SOFT_WORKDIR}/platform/compilation/cust_rules.mk
