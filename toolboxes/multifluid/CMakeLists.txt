
feelpp_add_application( application_multifluid_2d SRCS main_mf.cpp
  LINK_LIBRARIES
  feelpp_model_multifluid_2dP2P1G1_2dP1G1
  feelpp_model_multifluid_2dP2P1G1_2dP2G1
  DEFS FEELPP_DIM=2 FEELPP_GEO_ORDER=1
)

feelpp_add_application( application_multifluid_3d SRCS main_mf.cpp
  LINK_LIBRARIES
  feelpp_model_multifluid_3dP2P1G1_3dP1G1
  feelpp_model_multifluid_3dP2P1G1_3dP2G1
  DEFS FEELPP_DIM=3 FEELPP_GEO_ORDER=1
)

feelpp_add_testcase(square PREFIX feelpp_multifluid CATEGORY multifluid)
feelpp_add_testcase(drop PREFIX feelpp_multifluid CATEGORY multifluid)
feelpp_add_testcase(vesicle_rest PREFIX feelpp_multifluid CATEGORY multifluid)
feelpp_add_testcase(vesicle_shear PREFIX feelpp_multifluid CATEGORY multifluid)

#feelpp_add_application( application_fm_2d SRCS main_fm.cpp LINK_LIBRARIES feelpp_model_fluidmechanics )

#install(TARGETS feelpp_application_fluid_2d feelpp_application_fluid_3d 
        #RUNTIME DESTINATION bin/ 
        #COMPONENT ModelApplications)
