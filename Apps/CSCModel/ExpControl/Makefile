prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: ExpControl 

ExpControl: ExpControl.c Gui.o GuiExpControl.o ../../../Library/Misc/Misc.o ../../../Library/Messages/Gui2ExpCtrl.o ExpControlRtTask.o ../../../Library/RtTaskStats/RtTaskStats.o HandleGui2ExpCtrlMsgs.o ../../../Library/Status/ExpStatus.o ../../../Library/Messages/ExpCtrlDur2ExpCtrl.o ../../../Library/Messages/ExpCtrl2ExpCtrlDur.o HandleExpCtrlDur2ExpCtrlMsgs.o HandleExpCtrl2ExpCtrlDurMsgs.o HandleDioCtrl2ExpCtrlMsgs.o HandleProstheticCtrl2ExpCtrlMsgs.o ../../../Library/Messages/DioCtrl2ExpCtrl.o ../../../Library/Messages/ProstheticCtrl2ExpCtrl.o ../../../Library/Messages/ExpCtrl2ProstheticCtrl.o ../../../Library/Messages/ExpCtrl2DioCtrl.o ../../../Library/Status/ExpDurStatus.o ../../../Library/Misc/Randn.o HandleExpCtrlDur.o ../../../Library/Messages/ExpCtrl2NeuralNet.o ../../../Library/Messages/NeuralNet2ExpCtrl.o ExpHistory.o DataHandling/DataHandling.o DataHandling/v0/DataFormat_v0.o ../../../Library/Messages/ExpCtrl2Gui.o ../../../Library/Status/ExpStatusHistory.o ../../../Library/Misc/Averaging.o
	$(CC) -o $@ $< Gui.o GuiExpControl.o ../../../Library/Misc/Misc.o ../../../Library/Messages/Gui2ExpCtrl.o ExpControlRtTask.o ../../../Library/RtTaskStats/RtTaskStats.o HandleGui2ExpCtrlMsgs.o ../../../Library/Status/ExpStatus.o ../../../Library/Messages/ExpCtrlDur2ExpCtrl.o ../../../Library/Messages/ExpCtrl2ExpCtrlDur.o HandleExpCtrlDur2ExpCtrlMsgs.o HandleExpCtrl2ExpCtrlDurMsgs.o HandleDioCtrl2ExpCtrlMsgs.o HandleProstheticCtrl2ExpCtrlMsgs.o ../../../Library/Messages/DioCtrl2ExpCtrl.o ../../../Library/Messages/ProstheticCtrl2ExpCtrl.o ../../../Library/Messages/ExpCtrl2ProstheticCtrl.o ../../../Library/Messages/ExpCtrl2DioCtrl.o ../../../Library/Status/ExpDurStatus.o ../../../Library/Misc/Randn.o HandleExpCtrlDur.o ../../../Library/Messages/ExpCtrl2NeuralNet.o ../../../Library/Messages/NeuralNet2ExpCtrl.o ExpHistory.o DataHandling/DataHandling.o DataHandling/v0/DataFormat_v0.o ../../../Library/Messages/ExpCtrl2Gui.o ../../../Library/Status/ExpStatusHistory.o ../../../Library/Misc/Averaging.o $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) ### ExpControl

Gui.o: Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### Gui

GuiExpControl.o: GuiExpControl.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### GuiExpControl

ExpControlRtTask.o: ExpControlRtTask.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpControlRtTask

HandleGui2ExpCtrlMsgs.o: HandleGui2ExpCtrlMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleGui2ExpCtrlMsgs

HandleExpCtrlDur2ExpCtrlMsgs.o: HandleExpCtrlDur2ExpCtrlMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleExpCtrlDur2ExpCtrlMsgs

HandleExpCtrlDur.o: HandleExpCtrlDur.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleExpCtrlDur

HandleExpCtrl2ExpCtrlDurMsgs.o: HandleExpCtrl2ExpCtrlDurMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleExpCtrl2ExpCtrlDurMsgs

HandleDioCtrl2ExpCtrlMsgs.o: HandleDioCtrl2ExpCtrlMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleDioCtrl2ExpCtrlMsgs

HandleProstheticCtrl2ExpCtrlMsgs.o: HandleProstheticCtrl2ExpCtrlMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleProstheticCtrl2ExpCtrlMsgs

../../../Library/Misc/Misc.o: ../../../Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Misc/Misc

../../../Library/Misc/Averaging.o: ../../../Library/Misc/Averaging.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Misc/Averaging

../../../Library/Misc/Randn.o: ../../../Library/Misc/Randn.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Misc/Randn

../../../Library/Messages/Gui2ExpCtrl.o: ../../../Library/Messages/Gui2ExpCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/Gui2ExpCtrl

../../../Library/Messages/ExpCtrl2Gui.o: ../../../Library/Messages/ExpCtrl2Gui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ExpCtrl2Gui

../../../Library/Messages/ExpCtrlDur2ExpCtrl.o: ../../../Library/Messages/ExpCtrlDur2ExpCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ExpCtrlDur2ExpCtrl

../../../Library/Messages/DioCtrl2ExpCtrl.o: ../../../Library/Messages/DioCtrl2ExpCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/DioCtrl2ExpCtrl

../../../Library/Messages/ProstheticCtrl2ExpCtrl.o: ../../../Library/Messages/ProstheticCtrl2ExpCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ProstheticCtrl2ExpCtrl

../../../Library/Messages/ExpCtrl2ProstheticCtrl.o: ../../../Library/Messages/ExpCtrl2ProstheticCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ExpCtrl2ProstheticCtrl

../../../Library/Messages/ExpCtrl2ExpCtrlDur.o: ../../../Library/Messages/ExpCtrl2ExpCtrlDur.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ExpCtrl2ExpCtrlDur

../../../Library/Messages/ExpCtrl2NeuralNet.o: ../../../Library/Messages/ExpCtrl2NeuralNet.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ExpCtrl2NeuralNet

../../../Library/Messages/NeuralNet2ExpCtrl.o: ../../../Library/Messages/NeuralNet2ExpCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/NeuralNet2ExpCtrl

../../../Library/Status/ExpStatus.o: ../../../Library/Status/ExpStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/ExpStatus.o

../../../Library/Status/ExpStatusHistory.o: ../../../Library/Status/ExpStatusHistory.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/ExpStatusHistory.o

../../../Library/Status/ExpDurStatus.o: ../../../Library/Status/ExpDurStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/ExpDurStatus.o

../../../Library/RtTaskStats/RtTaskStats.o: ../../../Library/RtTaskStats/RtTaskStats.c	
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/RtTaskStats/RtTaskStats.o

ExpCtrlParadigm.o: ExpCtrlParadigm.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpCtrlParadigm

ExpHistory.o: ExpHistory.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpHistory

DataHandling/DataHandling.o: DataHandling/DataHandling.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataHandling/DataHandling

DataHandling/v0/DataFormat_v0.o: DataHandling/v0/DataFormat_v0.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataHandling/v0/DataFormat_v0

../../../Library/Messages/ExpCtrl2DioCtrl.o: ../../../Library/Messages/ExpCtrl2DioCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ExpCtrl2DioCtrl

clean:
	rm -f ExpControl *.o ../../../Library/Misc/*.o ../../../Library/Messages/*.o ../../../Library/ExpsData/*.o ../../../Library/Combos/*.o ../../../Library/RtTaskStats/*.o ../../../Library/Status/*.o ../../../Library/Thresholding/*.o ../../../Library/LogBuffer/*.o ../../../Library/Coordinate/*.o DataHandling/*.o DataHandling/v0/*.o 

.PHONY: clean
