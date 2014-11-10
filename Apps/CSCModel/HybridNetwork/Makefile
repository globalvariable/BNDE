prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm -lmeschach
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: HybridNetwork

HybridNetwork: HybridNetwork.c Gui.o ../../../Library/Misc/Misc.o DataAcquisition/ConfigDaq/ConfigDaqGui.o DataAcquisition/ConfigDaq/FileHandler.o DataAcquisition/ConfigDaq/FileHandler_v0.o DataAcquisition/ConfigDaq/DaqMwaMap.o DataAcquisition/DaqRtTask.o ../../../Library/RtTaskStats/RtTaskStats.o DataAcquisition/ConfigDaq/DaqCard.o HybridNetworkRtTask.o DataAcquisition/RecordingData.o DataAcquisition/ButterFilter.o DataAcquisition/CubicInterpolation.o DataAcquisition/SpikeSorting.o DataAcquisition/TemplateMatching.o DataAcquisition/SpikeViewer/SpikeViewerGui.o DataAcquisition/SpikeViewer/FileHandler.o DataAcquisition/SpikeViewer/FileHandler_v0.o DataAcquisition/SpikeSorter/SpikeSorterGui.o DataAcquisition/SpikeSorter/FileHandler.o DataAcquisition/SpikeSorter/FileHandler_v0.o SNN/NetworkView/NetworkView.o SNN/SnnData.o SNN/SnnRtTask.o ../../../Library/Izlib/Neuron/NeuronTypes.o ../../../Library/Izlib/Neuron/Neuron.o ../../../Library/Izlib/Network/Network.o ../../../Library/Izlib/Combos/LayerNrnGrpNeuronCombo.o ../../../Library/Izlib/Combos/LayerNrnGrpNrnSynapseCombo.o ../../../Library/Izlib/Combos/NeuronDynamicsCombo.o ../../../Library/Izlib/NeuronDynamicsData/NeuronDynamicsData.o ../../../Library/Izlib/SpikeData/SpikeData.o SNN/BufferViewHandler/BufferViewHandler.o SNN/SnnFunctions/SnnFunctions.o ../../../Library/Messages/NeuralNet2Gui.o ../../../Library/Izlib/Synapse/Synapse.o ../../../Library/Izlib/Eligibility/Eligibility.o ../../../Library/Izlib/STDP/STDP.o ../../../Library/Izlib/ParkerSochacki/ParkerSochacki.o ../../../Library/Izlib/ParkerSochacki/PSBinaryPrePostElig.o SNN/NeuronDynamicsView/NeuronDynamicsView.o ../../../Library/Messages/ExpCtrl2NeuralNet.o ../../../Library/Messages/ProstheticCtrl2NeuralNet.o ../../../Library/Status/ExpStatus.o ../../../Library/Izlib/Axon/Axon.o  ../../../Library/Izlib/Event/Event.o SNN/BlueSpikeSpikePatternView/BlueSpikeSpikePatternView.o SNN/InSilicoSpikePatternView/InSilicoSpikePatternView.o SNN/WeightHistoryView/WeightHistoryView.o SNN/AxonToLayerWeightView/AxonToLayerWeightView.o ../../../Library/Izlib/Graphs/SpikePatternGraph.o ../../../Library/Izlib/Graphs/NeuronDynamicsGraph.o ../../../Library/Izlib/Graphs/STDPGraph.o ../../../Library/Izlib/Graphs/EligibilityGraph.o ../../../Library/Misc/Randn.o ../../../Library/Izlib/Combos/STDPCombo.o ../../../Library/Izlib/Graphs/SynapticWeightHistGraph.o ../../../Library/Izlib/Graphs/StatusMarker.o DataAcquisition/BlueSpikeData.o SNN/DataHandling/DataHandling.o SNN/DataHandling/v0/DataFormat_v0.o ../../../Library/Messages/NeuralNet2ProstheticCtrl.o ../../../Library/Messages/NeuralNet2ExpCtrl.o
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< Gui.o ../../../Library/Misc/Misc.o DataAcquisition/ConfigDaq/ConfigDaqGui.o DataAcquisition/ConfigDaq/FileHandler.o DataAcquisition/ConfigDaq/FileHandler_v0.o DataAcquisition/ConfigDaq/DaqMwaMap.o DataAcquisition/DaqRtTask.o	../../../Library/RtTaskStats/RtTaskStats.o DataAcquisition/ConfigDaq/DaqCard.o  HybridNetworkRtTask.o DataAcquisition/RecordingData.o DataAcquisition/ButterFilter.o DataAcquisition/CubicInterpolation.o  DataAcquisition/SpikeSorting.o DataAcquisition/TemplateMatching.o DataAcquisition/SpikeViewer/SpikeViewerGui.o DataAcquisition/SpikeViewer/FileHandler.o DataAcquisition/SpikeViewer/FileHandler_v0.o DataAcquisition/SpikeSorter/SpikeSorterGui.o DataAcquisition/SpikeSorter/FileHandler.o DataAcquisition/SpikeSorter/FileHandler_v0.o SNN/NetworkView/NetworkView.o SNN/SnnData.o SNN/SnnRtTask.o ../../../Library/Izlib/Neuron/NeuronTypes.o ../../../Library/Izlib/Neuron/Neuron.o ../../../Library/Izlib/Network/Network.o ../../../Library/Izlib/Combos/LayerNrnGrpNeuronCombo.o ../../../Library/Izlib/Combos/LayerNrnGrpNrnSynapseCombo.o  ../../../Library/Izlib/Combos/NeuronDynamicsCombo.o ../../../Library/Izlib/NeuronDynamicsData/NeuronDynamicsData.o ../../../Library/Izlib/SpikeData/SpikeData.o SNN/BufferViewHandler/BufferViewHandler.o SNN/SnnFunctions/SnnFunctions.o ../../../Library/Messages/NeuralNet2Gui.o ../../../Library/Izlib/Synapse/Synapse.o ../../../Library/Izlib/Eligibility/Eligibility.o ../../../Library/Izlib/STDP/STDP.o ../../../Library/Izlib/ParkerSochacki/ParkerSochacki.o ../../../Library/Izlib/ParkerSochacki/PSBinaryPrePostElig.o SNN/NeuronDynamicsView/NeuronDynamicsView.o ../../../Library/Messages/ExpCtrl2NeuralNet.o ../../../Library/Messages/ProstheticCtrl2NeuralNet.o ../../../Library/Status/ExpStatus.o ../../../Library/Izlib/Axon/Axon.o ../../../Library/Izlib/Event/Event.o SNN/BlueSpikeSpikePatternView/BlueSpikeSpikePatternView.o SNN/InSilicoSpikePatternView/InSilicoSpikePatternView.o SNN/WeightHistoryView/WeightHistoryView.o SNN/AxonToLayerWeightView/AxonToLayerWeightView.o  ../../../Library/Izlib/Graphs/SpikePatternGraph.o ../../../Library/Izlib/Graphs/NeuronDynamicsGraph.o  ../../../Library/Izlib/Graphs/STDPGraph.o ../../../Library/Izlib/Graphs/EligibilityGraph.o ../../../Library/Misc/Randn.o ../../../Library/Izlib/Combos/STDPCombo.o ../../../Library/Izlib/Graphs/SynapticWeightHistGraph.o ../../../Library/Izlib/Graphs/StatusMarker.o DataAcquisition/BlueSpikeData.o SNN/DataHandling/DataHandling.o SNN/DataHandling/v0/DataFormat_v0.o ../../../Library/Messages/NeuralNet2ProstheticCtrl.o ../../../Library/Messages/NeuralNet2ExpCtrl.o

Gui.o: Gui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### Gui

HybridNetworkRtTask.o: HybridNetworkRtTask.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HybridNetworkRtTask


#################  DataAcquisition  ###########################

DataAcquisition/DaqRtTask.o: DataAcquisition/DaqRtTask.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/DaqRtTask

DataAcquisition/RecordingData.o: DataAcquisition/RecordingData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/RecordingData

DataAcquisition/ButterFilter.o: DataAcquisition/ButterFilter.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/ButterFilter

DataAcquisition/CubicInterpolation.o: DataAcquisition/CubicInterpolation.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/CubicInterpolation

DataAcquisition/SpikeSorting.o: DataAcquisition/SpikeSorting.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/SpikeSorting

DataAcquisition/TemplateMatching.o: DataAcquisition/TemplateMatching.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/TemplateMatching

DataAcquisition/BlueSpikeData.o: DataAcquisition/BlueSpikeData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/BlueSpikeData

#################  DataAcquisition/ConfigDaq  ###########################

DataAcquisition/ConfigDaq/ConfigDaqGui.o: DataAcquisition/ConfigDaq/ConfigDaqGui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ConfigDaq/ConfigDaqGui

DataAcquisition/ConfigDaq/FileHandler.o: DataAcquisition/ConfigDaq/FileHandler.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ConfigDaq/FileHandler

DataAcquisition/ConfigDaq/FileHandler_v0.o: DataAcquisition/ConfigDaq/FileHandler_v0.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ConfigDaq/FileHandler_v0

DataAcquisition/ConfigDaq/DaqMwaMap.o: DataAcquisition/ConfigDaq/DaqMwaMap.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ConfigDaq/DaqMwaMap

DataAcquisition/ConfigDaq/DaqCard.o: DataAcquisition/ConfigDaq/DaqCard.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ConfigDaq/DaqCard

#################  DataAcquisition/SpikeViewer  ###########################

DataAcquisition/SpikeViewer/SpikeViewerGui.o: DataAcquisition/SpikeViewer/SpikeViewerGui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/SpikeViewer/SpikeViewerGui

DataAcquisition/SpikeViewer/FileHandler.o: DataAcquisition/SpikeViewer/FileHandler.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		### DataAcquisition/SpikeViewer/FileHandler

DataAcquisition/SpikeViewer/FileHandler_v0.o: DataAcquisition/SpikeViewer/FileHandler_v0.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		### DataAcquisition/SpikeViewer/FileHandler_v0

#################  DataAcquisition/SpikeSorter  ############################

DataAcquisition/SpikeSorter/SpikeSorterGui.o: DataAcquisition/SpikeSorter/SpikeSorterGui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/SpikeSorter/SpikeSorterGui

DataAcquisition/SpikeSorter/FileHandler.o: DataAcquisition/SpikeSorter/FileHandler.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/SpikeSorter/FileHandler

DataAcquisition/SpikeSorter/FileHandler_v0.o: DataAcquisition/SpikeSorter/FileHandler_v0.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### DataAcquisition/SpikeSorter/FileHandler_v0


#################  SNN  ###################################

SNN/SnnData.o: SNN/SnnData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### SNN/SnnData

SNN/SnnRtTask.o: SNN/SnnRtTask.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### SNN/SnnRtTask

SNN/NetworkView/NetworkView.o: SNN/NetworkView/NetworkView.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### SNN/NetworkView/NetworkView

SNN/NeuronDynamicsView/NeuronDynamicsView.o: SNN/NeuronDynamicsView/NeuronDynamicsView.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### SNN/NeuronDynamicsView/NeuronDynamicsView

SNN/BlueSpikeSpikePatternView/BlueSpikeSpikePatternView.o: SNN/BlueSpikeSpikePatternView/BlueSpikeSpikePatternView.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### BlueSpikeSpikePatternView

SNN/InSilicoSpikePatternView/InSilicoSpikePatternView.o: SNN/InSilicoSpikePatternView/InSilicoSpikePatternView.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### BlueSpikeSpikePatternView

SNN/WeightHistoryView/WeightHistoryView.o: SNN/WeightHistoryView/WeightHistoryView.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### WeightHistoryView

SNN/AxonToLayerWeightView/AxonToLayerWeightView.o: SNN/AxonToLayerWeightView/AxonToLayerWeightView.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### AxonToLayerWeightView

SNN/BufferViewHandler/BufferViewHandler.o: SNN/BufferViewHandler/BufferViewHandler.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### SNN/BufferViewHandler/BufferViewHandler

SNN/SnnFunctions/SnnFunctions.o: SNN/SnnFunctions/SnnFunctions.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### SNN/SnnFunctions/SnnFunctions

SNN/DataHandling/DataHandling.o: SNN/DataHandling/DataHandling.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### SNN/DataHandling/DataHandling

SNN/DataHandling/v0/DataFormat_v0.o: SNN/DataHandling/v0/DataFormat_v0.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### SNN/DataHandling/DataHandling/v0/DataFormat_v0
##########################################################

../../../Library/Misc/Misc.o: ../../../Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../../BlueSpikeLibrary/Misc/Misc

../../../Library/Misc/Randn.o: ../../../Library/Misc/Randn.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../../BlueSpikeLibrary/Misc/Randn

../../../Library/RtTaskStats/RtTaskStats.o: ../../../Library/RtTaskStats/RtTaskStats.c	
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/RtTaskStats/RtTaskStats.o

../../../Library/Izlib/Neuron/NeuronTypes.o: ../../../Library/Izlib/Neuron/NeuronTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Neuron/NeuronTypes

../../../Library/Izlib/Neuron/Neuron.o: ../../../Library/Izlib/Neuron/Neuron.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Neuron/Neuron

../../../Library/Izlib/Network/Network.o: ../../../Library/Izlib/Network/Network.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Network/Network

../../../Library/Izlib/Combos/LayerNrnGrpNeuronCombo.o: ../../../Library/Izlib/Combos/LayerNrnGrpNeuronCombo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Combos/LayerNrnGrpNeuronCombo

../../../Library/Izlib/Combos/LayerNrnGrpNrnSynapseCombo.o: ../../../Library/Izlib/Combos/LayerNrnGrpNrnSynapseCombo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Combos/LayerNrnGrpNrnSynapseCombo

../../../Library/Izlib/Combos/NeuronDynamicsCombo.o: ../../../Library/Izlib/Combos/NeuronDynamicsCombo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Izlib/Combos/NeuronDynamicsCombo

../../../Library/Izlib/NeuronDynamicsData/NeuronDynamicsData.o: ../../../Library/Izlib/NeuronDynamicsData/NeuronDynamicsData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/NeuronDynamicsData/NeuronDynamicsData

../../../Library/Izlib/SpikeData/SpikeData.o: ../../../Library/Izlib/SpikeData/SpikeData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Izlib/SpikeData/SpikeData

../../../Library/Izlib/Synapse/Synapse.o: ../../../Library/Izlib/Synapse/Synapse.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			###../../../Library/Izlib/Synapse/Synapse

../../../Library/Izlib/Eligibility/Eligibility.o: ../../../Library/Izlib/Eligibility/Eligibility.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Eligibility/Eligibility

../../../Library/Izlib/STDP/STDP.o: ../../../Library/Izlib/STDP/STDP.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/STDP/STDP

../../../Library/Izlib/ParkerSochacki/ParkerSochacki.o: ../../../Library/Izlib/ParkerSochacki/ParkerSochacki.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/ParkerSochacki/ParkerSochacki

../../../Library/Izlib/ParkerSochacki/PSBinaryPrePostElig.o: ../../../Library/Izlib/ParkerSochacki/PSBinaryPrePostElig.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/ParkerSochacki/PSBinaryPrePostElig

../../../Library/Status/ExpStatus.o: ../../../Library/Status/ExpStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/ExpStatus

../../../Library/Izlib/Axon/Axon.o: ../../../Library/Izlib/Axon/Axon.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Axon/Axon

../../../Library/Izlib/Event/Event.o: ../../../Library/Izlib/Event/Event.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Event/Event

../../../Library/Izlib/Graphs/SpikePatternGraph.o: ../../../Library/Izlib/Graphs/SpikePatternGraph.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)  		###	../../../Library/Izlib/Graphs/SpikePatternGraph

../../../Library/Izlib/Graphs/NeuronDynamicsGraph.o: ../../../Library/Izlib/Graphs/NeuronDynamicsGraph.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Graphs/NeuronDynamicsGraph

../../../Library/Izlib/Graphs/STDPGraph.o: ../../../Library/Izlib/Graphs/STDPGraph.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Graphs/STDPGraph

../../../Library/Izlib/Graphs/EligibilityGraph.o: ../../../Library/Izlib/Graphs/EligibilityGraph.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Graphs/EligibilityGraph

../../../Library/Izlib/Combos/STDPCombo.o: ../../../Library/Izlib/Combos/STDPCombo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Combos/STDPCombo

../../../Library/Izlib/Graphs/SynapticWeightHistGraph.o: ../../../Library/Izlib/Graphs/SynapticWeightHistGraph.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Graphs/SynapticWeightHistGraph

../../../Library/Izlib/Graphs/StatusMarker.o: ../../../Library/Izlib/Graphs/StatusMarker.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)		###	../../../Library/Izlib/Graphs/StatusMarker

##################### Messages #######################

../../../Library/Messages/NeuralNet2Gui.o: ../../../Library/Messages/NeuralNet2Gui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/NeuralNet2Gui

../../../Library/Messages/ExpCtrl2NeuralNet.o: ../../../Library/Messages/ExpCtrl2NeuralNet.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ExpCtrl2NeuralNet

../../../Library/Messages/NeuralNet2ExpCtrl.o: ../../../Library/Messages/NeuralNet2ExpCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/NeuralNet2ExpCtrl

../../../Library/Messages/ProstheticCtrl2NeuralNet.o: ../../../Library/Messages/ProstheticCtrl2NeuralNet.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/ProstheticCtrl2NeuralNet

../../../Library/Messages/NeuralNet2ProstheticCtrl.o: ../../../Library/Messages/NeuralNet2ProstheticCtrl.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Messages/NeuralNet2ProstheticCtrl

clean:
	rm -f HybridNetwork *.o DataAcquisition/*.o DataAcquisition/ConfigDaq/*.o DataAcquisition/SpikeViewer/*.o  DataAcquisition/SpikeSorter/*.o DataAcquisition/NeuRecHandler/*.o SNN/*.o SNN/AxonToLayerWeightView/*.o SNN/BlueSpikeSpikePatternView/*.o SNN/BufferViewHandler/*.o SNN/DataHandling/*.o SNN/DataHandling/v0/*.o SNN/EligibilityView/*.o SNN/InSilicoSpikePatternView/*.o SNN/NetworkView/*.o  SNN/NeuronDynamicsView/*.o  SNN/SnnFunctions/*.o  SNN/StdpView/*.o  SNN/WeightHistoryView/*.o ../../../Library/Misc/*.o  ../../../Library/Misc/*.o  DataAcquisition/*.o ../../../Library/Izlib/Neuron/*.o ../../../Library/Izlib/Network/*.o ../../../Library/RtTaskStats/*.o ../../../Library/Izlib/Combos/*.o ../../../Library/Izlib/NeuronDynamicsData/*.o  ../../../Library/Izlib/SpikeData/SpikeData.o SNN/BufferViewHandler/*.o SNN/SnnFunctions/*.o ../../../Library/Messages/*.o ../../../Library/Izlib/Synapse/*.o ../../../Library/Izlib/Eligibility/*.o ../../../Library/Izlib/STDP/*.o ../../../Library/Izlib/ParkerSochacki/*.o SNN/NeuronDynamicsView/*.o ../../../Library/Status/*.o ../../../Library/Izlib/Axon/*.o ../../../Library/Izlib/Event/*.o SNN/StdpView/*.o SNN/EligibilityView/*.o SNN/BlueSpikeSpikePatternView/*.o SNN/InSilicoSpikePatternView/*.o SNN/WeightHistoryView/*.o SNN/AxonToLayerWeightView/*.o ../../../Library/Izlib/Graphs/*.o 

.PHONY: clean



