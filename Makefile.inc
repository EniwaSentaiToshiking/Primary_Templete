APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
RunManager.o \
TailController.o \
SonarAlert.o \
BalancerCpp.o \
BalancingWalker.o \
CourceMonitor.o \
PIDController.o \
TouchController.o \
BTTask.o \
LotManager.o \
Lot.o \
PID.o \
Measure.o \
UI.o \
Logger.o \
StairScenario.o \

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif
