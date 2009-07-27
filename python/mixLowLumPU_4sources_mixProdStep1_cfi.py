# The following comments couldn't be translated into the new config version:

# E33 cm-2s-1
# mb
import FWCore.ParameterSet.Config as cms

# this is the configuration to model pileup in the low-luminosity phase
# here we have an example with 4 input sources
# but you are free to put only those you need
# or you can replace the type by "none" for a source you dont want
# please note that the names of the input sources are fixed: 'input', 'cosmics', 'beamhalo_minus', 'beamhalo_plus'
#
from SimGeneral.MixingModule.mixObjects_cfi import *
mix = cms.EDProducer("MixingModule",
    LabelPlayback = cms.string(''),
    maxBunch = cms.int32(3),
    minBunch = cms.int32(-5), ## in units of 25 nsec

    bunchspace = cms.int32(25), ## nsec
    checktof = cms.bool(False),
    mixProdStep1 = cms.bool(True),
    mixProdStep2 = cms.bool(False),

    playback = cms.untracked.bool(False),
    useCurrentProcessOnly = cms.bool(False),
    input = cms.SecSource("PoolSource",
        nbPileupEvents = cms.PSet(
            sigmaInel = cms.double(80.0),
            Lumi = cms.double(2.8)
        ),
        seed = cms.int32(1234567),
        type = cms.string('poisson'),
        fileNames = cms.untracked.vstring('/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/FA4BC00A-946B-DE11-9AE4-000423D9939C.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/706FCB9B-906B-DE11-959D-000423D991F0.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/64060CE2-926B-DE11-90E5-000423D99A8E.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/426F0F2B-8C6B-DE11-9CA6-000423D991F0.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/3C9F6B26-D86B-DE11-AAB2-001D09F2432B.root')
    ),
    cosmics = cms.SecSource("PoolSource",
        nbPileupEvents = cms.PSet(
            averageNumber = cms.double(1.6625e-05)
        ),
        seed = cms.int32(2345678),
        type = cms.string('poisson'),
        fileNames = cms.untracked.vstring(
	'/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/FA4BC00A-946B-DE11-9AE4-000423D9939C.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/706FCB9B-906B-DE11-959D-000423D991F0.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/64060CE2-926B-DE11-90E5-000423D99A8E.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/426F0F2B-8C6B-DE11-9CA6-000423D991F0.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/3C9F6B26-D86B-DE11-AAB2-001D09F2432B.root'	)
    ),
    beamhalo_minus = cms.SecSource("PoolSource",
        nbPileupEvents = cms.PSet(
            averageNumber = cms.double(0.00040503)
        ),
        seed = cms.int32(3456789),
        type = cms.string('poisson'),
        fileNames = cms.untracked.vstring(
	'/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/FA4BC00A-946B-DE11-9AE4-000423D9939C.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/706FCB9B-906B-DE11-959D-000423D991F0.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/64060CE2-926B-DE11-90E5-000423D99A8E.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/426F0F2B-8C6B-DE11-9CA6-000423D991F0.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/3C9F6B26-D86B-DE11-AAB2-001D09F2432B.root')
    ),
    beamhalo_plus = cms.SecSource("PoolSource",
        nbPileupEvents = cms.PSet(
            averageNumber = cms.double(0.00040503)
        ),
        seed = cms.int32(3456789),
        type = cms.string('poisson'),
        fileNames = cms.untracked.vstring(
	'/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/FA4BC00A-946B-DE11-9AE4-000423D9939C.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/706FCB9B-906B-DE11-959D-000423D991F0.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/64060CE2-926B-DE11-90E5-000423D99A8E.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/426F0F2B-8C6B-DE11-9CA6-000423D991F0.root',
        '/store/relval/CMSSW_3_1_1/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V2-v1/0002/3C9F6B26-D86B-DE11-AAB2-001D09F2432B.root')
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


