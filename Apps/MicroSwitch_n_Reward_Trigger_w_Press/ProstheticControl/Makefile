prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: ProstheticControl 

ProstheticControl: ProstheticControl.c Gui.o ../../../Library/Messages/Gui2ProstheticCtrl.o ../../../Library/Misc/Misc.o ProstheticControlRtTask.o ../../../Library/RtTaskStats/RtTaskStats.o GuiProstheticControl.o ../../../Library/Messages/ExpCtrl2ProstheticCtrl.o ../../../Library/Messages/ProstheticCtrlDurHand2ProstheticCtrl.o ../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand.o HandleProstheticCtrl2ProstheticCtrlDurHandMsgs.o ../../../Library/Messages/ProstheticCtrl2ExpCtrl.o HandleProstheticCtrlDurHand2ProstheticCtrlMsgs.o HandleExpCtrl2ProstheticCtrlMsgs.o HandleGui2ProstheticCtrlMsgs.o ../../../Library/ProstheticCtrlData/ProstheticCtrlComponentTypes.o ../../../Library/ProstheticCtrlData/ProstheticCtrlData.o ../../../Library/Status/ProstheticCtrlStatus.o ../../../Library/Status/ProstheticCtrlDurStatus.o ../../../Library/Messages/ProstheticCtrl2NeuralNet.o ../../../Library/Messages/NeuralNet2ProstheticCtrl.o HandleNeuralNet2ProstheticCtrlMsgs.o ../../../Library/Izlib/SpikeData/SpikeData.o HandleSpikeDataBuff.o ../../../Library/Messages/ProstheticCtrl2Gui.o ../../../Library/Servo/Servo.o ../../../Library/Robot/ThreeDofRobot.o ../../../Library/RS232/RS232Handler.o ../../../Library/LogBuffer/MessageLogBuffer.o HandleRS232Buffers.o HandleRobotPosition.o ../../../Library/Thresholding/Thresholding.o ProstheticCtrlParadigm.o ../../../Library/Coordinate/Cartesian.o DataHandling/DataHandling.o DataHandling/v0/DataFormat_v0.o ../../../Library/Status/ProstheticCtrlStatusHistory.o ../../../Library/Robot/ThreeDofRobotHistory.o 
	$(CC) -o $@ $< Gui.o ../../../Library/Messages/Gui2ProstheticCtrl.o ../../../Library/Misc/Misc.o ProstheticControlRtTask.o ../../../Library/RtTaskStats/RtTaskStats.o GuiProstheticControl.o ../../../Library/Messages/ExpCtrl2ProstheticCtrl.o ../../../Library/Messages/ProstheticCtrlDurHand2ProstheticCtrl.o ../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand.o HandleProstheticCtrl2ProstheticCtrlDurHandMsgs.o ../../../Library/Messages/ProstheticCtrl2ExpCtrl.o HandleProstheticCtrlDurHand2ProstheticCtrlMsgs.o HandleExpCtrl2ProstheticCtrlMsgs.o HandleGui2ProstheticCtrlMsgs.o ../../../Library/ProstheticCtrlData/ProstheticCtrlComponentTypes.o ../../../Library/ProstheticCtrlData/ProstheticCtrlData.o ../../../Library/Status/ProstheticCtrlStatus.o ../../../Library/Status/ProstheticCtrlDurStatus.o ../../../Library/Messages/ProstheticCtrl2NeuralNet.o ../../../Library/Messages/NeuralNet2ProstheticCtrl.o HandleNeuralNet2ProstheticCtrlMsgs.o ../../../Library/Izlib/SpikeData/SpikeData.o HandleSpikeDataBuff.o ../../../Library/Messages/ProstheticCtrl2Gui.o ../../../Library/Servo/Servo.o ../../../Library/Robot/ThreeDofRobot.o ../../../Library/RS232/RS232Handler.o ../../../Library/LogBuffer/MessageLogBuffer.o HandleRS232Buffers.o HandleRobotPosition.o ../../../Library/Thresholding/Thresholding.o ProstheticCtrlParadigm.o ../../../Library/Coordinate/Cartesian.o DataHandling/DataHandling.o DataHandling/v0/DataFormat_v0.o ../../../Library/Status/ProstheticCtrlStatusHistory.o ../../../Library/Robot/ThreeDofRobotHistory.o $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) ### ProstheticControl

Gui.o: Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### Gui

ProstheticControlRtTask.o: ProstheticControlRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ProstheticControlRtTask

GuiProstheticControl.o: GuiProstheticControl.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### GuiProstheticControl

HandleProstheticCtrl2ProstheticCtrlDurHandMsgs.o: HandleProstheticCtrl2ProstheticCtrlDurHandMsgs.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleProstheticCtrl2ProstheticCtrlDurHandMsgs

HandleProstheticCtrlDurHand2ProstheticCtrlMsgs.o: HandleProstheticCtrlDurHand2ProstheticCtrlMsgs.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleProstheticCtrlDurHand2ProstheticCtrlMsgs

HandleExpCtrl2ProstheticCtrlMsgs.o: HandleExpCtrl2ProstheticCtrlMsgs.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleExpCtrl2ProstheticCtrlMsgs

HandleGui2ProstheticCtrlMsgs.o: HandleGui2ProstheticCtrlMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleGui2ProstheticCtrlMsgs

HandleNeuralNet2ProstheticCtrlMsgs.o: HandleNeuralNet2ProstheticCtrlMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleNeuralNet2ProstheticCtrlMsgs.o

HandleSpikeDataBuff.o: HandleSpikeDataBuff.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleSpikeDataBuff.o

HandleRS232Buffers.o: HandleRS232Buffers.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleRS232Buffers

HandleRobotPosition.o: HandleRobotPosition.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleRobotPosition

../../../Library/Messages/Gui2ProstheticCtrl.o: ../../../Library/Messages/Gui2ProstheticCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/Gui2ProstheticCtrl

../../../Library/Messages/ProstheticCtrl2Gui.o: ../../../Library/Messages/ProstheticCtrl2Gui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ProstheticCtrl2Gui

../../../Library/Messages/ExpCtrl2ProstheticCtrl.o: ../../../Library/Messages/ExpCtrl2ProstheticCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ExpCtrl2ProstheticCtrl

../../../Library/Messages/ProstheticCtrlDurHand2ProstheticCtrl.o: ../../../Library/Messages/ProstheticCtrlDurHand2ProstheticCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ProstheticCtrlDurHand2ProstheticCtrl

../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand.o: ../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand

../../../Library/Messages/ProstheticCtrl2NeuralNet.o: ../../../Library/Messages/ProstheticCtrl2NeuralNet.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ProstheticCtrl2NeuralNet

../../../Library/Messages/NeuralNet2ProstheticCtrl.o: ../../../Library/Messages/NeuralNet2ProstheticCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/NeuralNet2ProstheticCtrl

../../../Library/ProstheticCtrlData/ProstheticCtrlComponentTypes.o: ../../../Library/ProstheticCtrlData/ProstheticCtrlComponentTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/ProstheticCtrlData/ProstheticCtrlComponentTypes

../../../Library/ProstheticCtrlData/ProstheticCtrlData.o: ../../../Library/ProstheticCtrlData/ProstheticCtrlData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/ProstheticCtrlData/ProstheticCtrlData

../../../Library/ProstheticCtrlData/ProstheticCtrlDirectionTypes.o: ../../../Library/ProstheticCtrlData/ProstheticCtrlDirectionTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/ProstheticCtrlData/ProstheticCtrlDirectionTypes

../../../Library/Status/ProstheticCtrlStatus.o: ../../../Library/Status/ProstheticCtrlStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/ProstheticCtrlStatus

../../../Library/Status/ProstheticCtrlStatusHistory.o: ../../../Library/Status/ProstheticCtrlStatusHistory.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/ProstheticCtrlStatusHistory.o

../../../Library/Status/ProstheticCtrlDurStatus.o: ../../../Library/Status/ProstheticCtrlDurStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/ProstheticCtrlDurStatus

../../../Library/Izlib/SpikeData/SpikeData.o: ../../../Library/Izlib/SpikeData/SpikeData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Izlib/SpikeData/SpikeData

../../../Library/Servo/Servo.o: ../../../Library/Servo/Servo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Servo/Servo

../../../Library/Robot/ThreeDofRobot.o: ../../../Library/Robot/ThreeDofRobot.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Robot/ThreeDofRobot

../../../Library/Robot/ThreeDofRobotHistory.o: ../../../Library/Robot/ThreeDofRobotHistory.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Robot/ThreeDofRobotHistory

../../../Library/Coordinate/Cartesian.o: ../../../Library/Coordinate/Cartesian.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Coordinate/Cartesian

../../../Library/LogBuffer/MessageLogBuffer.o: ../../../Library/LogBuffer/MessageLogBuffer.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/LogBuffer/MessageLogBuffer

../../../Library/Thresholding/Thresholding.o: ../../../Library/Thresholding/Thresholding.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Thresholding/Thresholding

ProstheticCtrlParadigm.o: ProstheticCtrlParadigm.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ProstheticCtrlParadigm

DataHandling/DataHandling.o: DataHandling/DataHandling.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataHandling/DataHandling

DataHandling/v0/DataFormat_v0.o: DataHandling/v0/DataFormat_v0.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataHandling/v0/DataFormat_v0

../../../Library/Messages/ProstheticCtrl2ExpCtrl.o: ../../../Library/Messages/ProstheticCtrl2ExpCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ProstheticCtrl2ExpCtrl

../../../Library/Misc/Misc.o: ../../../Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../../BlueSpikeLibrary/Misc/Misc

../../../Library/RtTaskStats/RtTaskStats.o: ../../../Library/RtTaskStats/RtTaskStats.c	
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/RtTaskStats/RtTaskStats.o

../../../Library/RS232/RS232Handler.o: ../../../Library/RS232/RS232Handler.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/RS232/RS232Handler

clean:
	rm -f ProstheticControl *.o ../../../Library/Misc/*.o ../../../Library/Messages/*.o ../../../Library/ExpsData/*.o ../../../Library/Combos/*.o ../../../Library/RtTaskStats/*.o ../../../Library/Status/*.o ../../../Library/RS232/*.o ../../../Library/ProstheticCtrlData/*.o ../../../Library/Izlib/SpikeData/*.o ../../../Library/Servo/*.o ../../../Library/Robot/*.o ../../../Library/Thresholding/*.o ../../../Library/LogBuffer/*.o ../../../Library/Coordinate/*.o DataHandling/*.o DataHandling/v0/*.o 

.PHONY: clean
