# The following comments couldn't be translated into the new config version:

# E33 cm-2s-1
# mb


import FWCore.ParameterSet.Config as cms

# this is the configuration to model pileup in the low-luminosity phase
from SimGeneral.MixingModule.mixObjects_cfi import *
mix = cms.EDProducer("MixingModule",
    LabelPlayback = cms.string(''),
    maxBunch = cms.int32(0),
    minBunch = cms.int32(0), ## in terms of 25 ns

    bunchspace = cms.int32(25), ## nsec
    checktof = cms.bool(False),
    mixProdStep1 = cms.bool(False),
    mixProdStep2 = cms.bool(True),
    
    playback = cms.untracked.bool(False),
    useCurrentProcessOnly = cms.bool(False),
                   		   
    input = cms.SecSource("PoolSource",	
	type = cms.string('fixed'),
	nbPileupEvents = cms.PSet(
        averageNumber = cms.double(1.0)
    	),
	
       fileNames = cms.untracked.vstring('file:/tmp/ebecheva/PCFwriterNew.root')
    ),
    
    mixObjects = cms.PSet(
        # Objects to mix
	mixPCFCH = cms.PSet(
            mixPCFCaloHits
        ),
        mixPCFTracks = cms.PSet(
            mixPCFSimTracks
        ),
        mixPCFVertices = cms.PSet(
            mixPCFSimVertices
        ),
        mixPCFSH = cms.PSet(
            mixPCFSimHits
        ),
        mixPCFHepMC = cms.PSet(
            mixPCFHepMCProducts#
        ),
	#add for Step2
	mixCH = cms.PSet(
            mixCaloHits
        ),
        mixTracks = cms.PSet(
            mixSimTracks
        ),
        mixVertices = cms.PSet(
            mixSimVertices
        ),
        mixSH = cms.PSet(
            mixSimHits
        ),
        mixHepMC = cms.PSet(
            mixHepMCProducts
        )
    )
)


