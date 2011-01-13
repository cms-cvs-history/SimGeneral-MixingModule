import FWCore.ParameterSet.Config as cms

# configuration to model pileup for initial physics phase
from SimGeneral.MixingModule.mixObjects_cfi import *
mix = cms.EDProducer("MixingModule",
    LabelPlayback = cms.string(''),
    maxBunch = cms.int32(-3),
    minBunch = cms.int32(2), ## in terms of 25 nsec

    bunchspace = cms.int32(50), ##ns
    mixProdStep1 = cms.bool(False),
    mixProdStep2 = cms.bool(False),

    playback = cms.untracked.bool(False),
    useCurrentProcessOnly = cms.bool(False),
                   
    input = cms.SecSource("PoolSource",
        seed = cms.int32(1234567),
        type = cms.string('probFunction'),
        nbPileupEvents = cms.PSet(
          probFunctionVariable = cms.vint32(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24),
          probValue = cms.vdouble(0.00130001,0.00728453,0.0224114,0.0458138,0.0721875,0.09741,0.114875,0.120895,0.11885,0.10471,0.0878654,0.0681808,0.0497561,0.0345137,0.0230669,0.0137068,0.00810676,0.00446449,0.00229114,0.00119335,0.000606673,0.000271114,0.000146668,6.66674e-05,2.6667e-05),
          histoFileName = cms.untracked.string('histProbFunction.root'),
          seed = cms.untracked.int32(54321)
        ),
	sequential = cms.untracked.bool(False),
        fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_3_8_5/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START38_V12-v1/0040/C4C6B18F-B6D2-DF11-80A7-002618943870.root',
                '/store/relval/CMSSW_3_8_5/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START38_V12-v1/0039/6AFB33BC-E7D1-DF11-84D3-001A928116F8.root')
    ),
    mixObjects = cms.PSet(
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



