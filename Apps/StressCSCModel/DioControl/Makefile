prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: DioControl 

DioControl: DioControl.c Gui.o ../../../Library/Messages/Gui2DioCtrl.o ../../../Library/Misc/Misc.o DioControlRtTask.o ../../../Library/RtTaskStats/RtTaskStats.o GuiDioControl.o ../../../Library/Messages/ExpCtrl2DioCtrl.o ../../../Library/Messages/DioCtrlDurHand2DioCtrl.o DioCtrlDurationHandlerRtTask.o HandleDioCtrl2DioCtrlDurHandMsgs.o ../../../Library/Messages/DioCtrl2DioCtrlDurHand.o ../../../Library/Messages/DioCtrl2ExpCtrl.o ../../../Library/DioCtrlData/DioCtrlComponentTypes.o ../../../Library/DioCtrlData/DioCtrlData.o HandleGui2DioCtrlMsgs.o HandleDioCtrlDurHand2DioCtrlMsgs.o HandleExpCtrl2DioCtrlMsgs.o HandleDioCtrlDur.o ../../../Library/Status/DioCtrlStatus.o ../../../Library/Status/DioCtrlDurStatus.o ../../../Library/DioCtrlData/DioCtrlEvaluate.o ../../../Library/Status/DioCtrlComponentStatus.o HandleRS232Buffers.o ../../../Library/RS232/RS232Handler.o ../../../Library/Messages/DioCtrl2Gui.o DataHandling/DataHandling.o DataHandling/v0/DataFormat_v0.o ../../../Library/Status/DioCtrlComponentStatusHistory.o 
	$(CC) -o $@ $< Gui.o ../../../Library/Messages/Gui2DioCtrl.o ../../../Library/Misc/Misc.o DioControlRtTask.o ../../../Library/RtTaskStats/RtTaskStats.o GuiDioControl.o ../../../Library/Messages/ExpCtrl2DioCtrl.o ../../../Library/Messages/DioCtrlDurHand2DioCtrl.o DioCtrlDurationHandlerRtTask.o HandleDioCtrl2DioCtrlDurHandMsgs.o ../../../Library/Messages/DioCtrl2DioCtrlDurHand.o ../../../Library/Messages/DioCtrl2ExpCtrl.o ../../../Library/DioCtrlData/DioCtrlComponentTypes.o ../../../Library/DioCtrlData/DioCtrlData.o HandleGui2DioCtrlMsgs.o HandleDioCtrlDurHand2DioCtrlMsgs.o HandleExpCtrl2DioCtrlMsgs.o HandleDioCtrlDur.o ../../../Library/Status/DioCtrlStatus.o ../../../Library/Status/DioCtrlDurStatus.o ../../../Library/DioCtrlData/DioCtrlEvaluate.o ../../../Library/Status/DioCtrlComponentStatus.o HandleRS232Buffers.o ../../../Library/RS232/RS232Handler.o ../../../Library/Messages/DioCtrl2Gui.o DataHandling/DataHandling.o DataHandling/v0/DataFormat_v0.o ../../../Library/Status/DioCtrlComponentStatusHistory.o $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS)  ### DioControl

Gui.o: Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### Gui

GuiDioControl.o: GuiDioControl.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### GuiDioControl

DioControlRtTask.o: DioControlRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DioControlRtTask

DioCtrlDurationHandlerRtTask.o: DioCtrlDurationHandlerRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DioCtrlDurationHandlerRtTask

HandleGui2DioCtrlMsgs.o: HandleGui2DioCtrlMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleGui2DioCtrlMsgs

HandleDioCtrlDurHand2DioCtrlMsgs.o: HandleDioCtrlDurHand2DioCtrlMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleDioCtrlDurHand2DioCtrlMsgs

HandleExpCtrl2DioCtrlMsgs.o: HandleExpCtrl2DioCtrlMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleExpCtrl2DioCtrlMsgs

HandleDioCtrl2DioCtrlDurHandMsgs.o: HandleDioCtrl2DioCtrlDurHandMsgs.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleDioCtrl2DioCtrlDurHandMsgs

HandleDioCtrlDur.o: HandleDioCtrlDur.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleDioCtrlDur

HandleRS232Buffers.o: HandleRS232Buffers.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleRS232Buffers

../../../Library/Messages/Gui2DioCtrl.o: ../../../Library/Messages/Gui2DioCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/Gui2DioCtrl

../../../Library/Messages/DioCtrl2Gui.o: ../../../Library/Messages/DioCtrl2Gui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/DioCtrl2Gui

../../../Library/Messages/ExpCtrl2DioCtrl.o: ../../../Library/Messages/ExpCtrl2DioCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ExpCtrl2DioCtrl

../../../Library/Messages/DioCtrlDurHand2DioCtrl.o: ../../../Library/Messages/DioCtrlDurHand2DioCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/DioCtrlDurHand2DioCtrl

../../../Library/Messages/DioCtrl2DioCtrlDurHand.o: ../../../Library/Messages/DioCtrl2DioCtrlDurHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/DioCtrl2DioCtrlDurHand

../../../Library/DioCtrlData/DioCtrlComponentTypes.o: ../../../Library/DioCtrlData/DioCtrlComponentTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/DioCtrlData/DioCtrlComponentTypes

../../../Library/DioCtrlData/DioCtrlData.o: ../../../Library/DioCtrlData/DioCtrlData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/DioCtrlData/DioCtrlData

../../../Library/DioCtrlData/DioCtrlEvaluate.o: ../../../Library/DioCtrlData/DioCtrlEvaluate.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/DioCtrlData/DioCtrlEvaluate

../../../Library/Status/DioCtrlComponentStatusHistory.o: ../../../Library/Status/DioCtrlComponentStatusHistory.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/DioCtrlComponentStatusHistory

../../../Library/Status/DioCtrlStatus.o: ../../../Library/Status/DioCtrlStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/DioCtrlStatus

../../../Library/Status/DioCtrlDurStatus.o: ../../../Library/Status/DioCtrlDurStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/DioCtrlDurStatus

../../../Library/Status/DioCtrlComponentStatus.o: ../../../Library/Status/DioCtrlComponentStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/DioCtrlComponentStatus

../../../Library/RS232/RS232Handler.o: ../../../Library/RS232/RS232Handler.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/RS232/RS232Handler

DataHandling/DataHandling.o: DataHandling/DataHandling.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataHandling/DataHandling

DataHandling/v0/DataFormat_v0.o: DataHandling/v0/DataFormat_v0.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataHandling/v0/DataFormat_v0

../../../Library/Misc/Misc.o: ../../../Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../../BlueSpikeLibrary/Misc/Misc

../../../Library/RtTaskStats/RtTaskStats.o: ../../../Library/RtTaskStats/RtTaskStats.c	
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/RtTaskStats/RtTaskStats.o

../../../Library/Messages/DioCtrl2ExpCtrl.o: ../../../Library/Messages/DioCtrl2ExpCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/DioCtrl2ExpCtrl

clean:
	rm -f DioControl *.o ../../../Library/Misc/*.o ../../../Library/Messages/*.o ../../../Library/ExpsData/*.o ../../../Library/Combos/*.o ../../../Library/RtTaskStats/*.o ../../../Library/Status/*.o ../../../Library/RS232/*.o ../../../Library/DioCtrlData/*.o ../../../Library/ProstheticCtrlData/*.o ../../../IzNeuronSimulators/Library/SpikeData/*.o ../../../Library/Servo/*.o ../../../Library/Robot/*.o ../../../Library/Thresholding/*.o ../../../Library/Coordinate/*.o DataHandling/*.o DataHandling/v0/*.o 

.PHONY: clean
