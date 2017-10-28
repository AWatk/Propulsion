/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Rocket_SM_V2_sfun.h"
#include "c3_Rocket_SM_V2.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Rocket_SM_V2_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c3_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c3_IN_GuideRail                ((uint8_T)1U)
#define c3_IN_Landed                   ((uint8_T)2U)
#define c3_IN_PreLaunch                ((uint8_T)3U)
#define c3_IN_Unconstrained            ((uint8_T)4U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c3_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_b_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_d_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_e_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_f_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_g_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_h_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_i_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_j_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_k_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_l_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static boolean_T c3_dataWrittenToVector[10];

/* Function Declarations */
static void initialize_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance);
static void initialize_params_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance);
static void enable_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance);
static void disable_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance);
static void c3_update_debugger_state_c3_Rocket_SM_V2
  (SFc3_Rocket_SM_V2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_Rocket_SM_V2
  (SFc3_Rocket_SM_V2InstanceStruct *chartInstance);
static void set_sim_state_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_st);
static void c3_set_sim_state_side_effects_c3_Rocket_SM_V2
  (SFc3_Rocket_SM_V2InstanceStruct *chartInstance);
static void finalize_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance);
static void sf_gateway_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance);
static void c3_chartstep_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance);
static void initSimStructsc3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static real_T c3_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  const mxArray *c3_nargout, const char_T *c3_identifier);
static real_T c3_b_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static boolean_T c3_c_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_GuideRailFlight(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  real_T c3_T, real_T c3_T_L, real_T c3_dryMass, real_T c3_Cd, real_T c3_Area,
  real_T c3_vel[2], real_T c3_pos[2], real_T c3_p[2], real_T c3_v[2], real_T
  c3_a[2]);
static void c3_UnconstrainedFlight(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, real_T c3_T, real_T c3_T_L, real_T c3_dryMass, real_T c3_Cd,
  real_T c3_Area, real_T c3_w0, real_T c3_z0, real_T c3_vel[2], real_T c3_pos[2],
  real_T c3_p[2], real_T c3_v[2], real_T c3_a[2]);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_d_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static uint8_T c3_e_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_b_tp_PreLaunch, const char_T *c3_identifier);
static uint8_T c3_f_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_g_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  const mxArray *c3_position, const char_T *c3_identifier, real_T c3_y[2]);
static void c3_h_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2]);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_i_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2]);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_j_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_b_setSimStateSideEffectsInfo, const char_T
  *c3_identifier);
static const mxArray *c3_k_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_updateDataWrittenToVector(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, uint32_T c3_vectorIndex);
static void c3_errorIfDataNotWrittenToFcn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, uint32_T c3_vectorIndex, uint32_T c3_dataNumber);
static void init_dsm_address_info(SFc3_Rocket_SM_V2InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_doSetSimStateSideEffects = 0U;
  chartInstance->c3_setSimStateSideEffectsInfo = NULL;
  chartInstance->c3_tp_GuideRail = 0U;
  chartInstance->c3_tp_Landed = 0U;
  chartInstance->c3_tp_PreLaunch = 0U;
  chartInstance->c3_tp_Unconstrained = 0U;
  chartInstance->c3_is_active_c3_Rocket_SM_V2 = 0U;
  chartInstance->c3_is_c3_Rocket_SM_V2 = c3_IN_NO_ACTIVE_CHILD;
}

static void initialize_params_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_GuideRail) {
    sf_call_output_fcn_enable(chartInstance->S, 0, "GuideRailFlight", 0);
  }

  if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_Unconstrained) {
    sf_call_output_fcn_enable(chartInstance->S, 1, "UnconstrainedFlight", 0);
  }
}

static void disable_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_GuideRail) {
    sf_call_output_fcn_disable(chartInstance->S, 0, "GuideRailFlight", 0);
  }

  if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_Unconstrained) {
    sf_call_output_fcn_disable(chartInstance->S, 1, "UnconstrainedFlight", 0);
  }
}

static void c3_update_debugger_state_c3_Rocket_SM_V2
  (SFc3_Rocket_SM_V2InstanceStruct *chartInstance)
{
  uint32_T c3_prevAniVal;
  c3_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c3_is_active_c3_Rocket_SM_V2 == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, chartInstance->c3_sfEvent);
  }

  if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_PreLaunch) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c3_sfEvent);
  }

  if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_GuideRail) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c3_sfEvent);
  }

  if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_Unconstrained) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c3_sfEvent);
  }

  if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_Landed) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c3_sfEvent);
  }

  _SFD_SET_ANIMATION(c3_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c3_Rocket_SM_V2
  (SFc3_Rocket_SM_V2InstanceStruct *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int32_T c3_i0;
  real_T c3_u[2];
  const mxArray *c3_b_y = NULL;
  int32_T c3_i1;
  real_T c3_b_u[2];
  const mxArray *c3_c_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  int32_T c3_i2;
  real_T c3_d_u[2];
  const mxArray *c3_e_y = NULL;
  uint8_T c3_b_hoistedGlobal;
  uint8_T c3_e_u;
  const mxArray *c3_f_y = NULL;
  uint8_T c3_c_hoistedGlobal;
  uint8_T c3_f_u;
  const mxArray *c3_g_y = NULL;
  real_T *c3_stop;
  real_T (*c3_velocity)[2];
  real_T (*c3_position)[2];
  real_T (*c3_acceleration)[2];
  c3_stop = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_acceleration = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_velocity = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_position = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(6, 1), false);
  for (c3_i0 = 0; c3_i0 < 2; c3_i0++) {
    c3_u[c3_i0] = (*c3_acceleration)[c3_i0];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i1 = 0; c3_i1 < 2; c3_i1++) {
    c3_b_u[c3_i1] = (*c3_position)[c3_i1];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_hoistedGlobal = *c3_stop;
  c3_c_u = c3_hoistedGlobal;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 2, c3_d_y);
  for (c3_i2 = 0; c3_i2 < 2; c3_i2++) {
    c3_d_u[c3_i2] = (*c3_velocity)[c3_i2];
  }

  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_d_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c3_y, 3, c3_e_y);
  c3_b_hoistedGlobal = chartInstance->c3_is_active_c3_Rocket_SM_V2;
  c3_e_u = c3_b_hoistedGlobal;
  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 4, c3_f_y);
  c3_c_hoistedGlobal = chartInstance->c3_is_c3_Rocket_SM_V2;
  c3_f_u = c3_c_hoistedGlobal;
  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y", &c3_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 5, c3_g_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv0[2];
  int32_T c3_i3;
  real_T c3_dv1[2];
  int32_T c3_i4;
  real_T c3_dv2[2];
  int32_T c3_i5;
  real_T *c3_stop;
  real_T (*c3_acceleration)[2];
  real_T (*c3_position)[2];
  real_T (*c3_velocity)[2];
  c3_stop = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_acceleration = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_velocity = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_position = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_u = sf_mex_dup(c3_st);
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                        "acceleration", c3_dv0);
  for (c3_i3 = 0; c3_i3 < 2; c3_i3++) {
    (*c3_acceleration)[c3_i3] = c3_dv0[c3_i3];
  }

  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
                        "position", c3_dv1);
  for (c3_i4 = 0; c3_i4 < 2; c3_i4++) {
    (*c3_position)[c3_i4] = c3_dv1[c3_i4];
  }

  *c3_stop = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u,
    2)), "stop");
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 3)),
                        "velocity", c3_dv2);
  for (c3_i5 = 0; c3_i5 < 2; c3_i5++) {
    (*c3_velocity)[c3_i5] = c3_dv2[c3_i5];
  }

  chartInstance->c3_is_active_c3_Rocket_SM_V2 = c3_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 4)),
     "is_active_c3_Rocket_SM_V2");
  chartInstance->c3_is_c3_Rocket_SM_V2 = c3_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 5)), "is_c3_Rocket_SM_V2");
  sf_mex_assign(&chartInstance->c3_setSimStateSideEffectsInfo,
                c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c3_u, 6)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c3_u);
  chartInstance->c3_doSetSimStateSideEffects = 1U;
  c3_update_debugger_state_c3_Rocket_SM_V2(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void c3_set_sim_state_side_effects_c3_Rocket_SM_V2
  (SFc3_Rocket_SM_V2InstanceStruct *chartInstance)
{
  if (chartInstance->c3_doSetSimStateSideEffects != 0) {
    if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_GuideRail) {
      chartInstance->c3_tp_GuideRail = 1U;
      if (sf_mex_sub(chartInstance->c3_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 2) == 0.0) {
        sf_call_output_fcn_enable(chartInstance->S, 0, "GuideRailFlight", 0);
      }
    } else {
      chartInstance->c3_tp_GuideRail = 0U;
      if (sf_mex_sub(chartInstance->c3_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 2) > 0.0) {
        sf_call_output_fcn_disable(chartInstance->S, 0, "GuideRailFlight", 0);
      }
    }

    if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_Landed) {
      chartInstance->c3_tp_Landed = 1U;
    } else {
      chartInstance->c3_tp_Landed = 0U;
    }

    if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_PreLaunch) {
      chartInstance->c3_tp_PreLaunch = 1U;
    } else {
      chartInstance->c3_tp_PreLaunch = 0U;
    }

    if (chartInstance->c3_is_c3_Rocket_SM_V2 == c3_IN_Unconstrained) {
      chartInstance->c3_tp_Unconstrained = 1U;
      if (sf_mex_sub(chartInstance->c3_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 5) == 0.0) {
        sf_call_output_fcn_enable(chartInstance->S, 1, "UnconstrainedFlight", 0);
      }
    } else {
      chartInstance->c3_tp_Unconstrained = 0U;
      if (sf_mex_sub(chartInstance->c3_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 5) > 0.0) {
        sf_call_output_fcn_disable(chartInstance->S, 1, "UnconstrainedFlight", 0);
      }
    }

    chartInstance->c3_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c3_setSimStateSideEffectsInfo);
}

static void sf_gateway_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance)
{
  int32_T c3_i6;
  int32_T c3_i7;
  int32_T c3_i8;
  real_T *c3_Cd;
  real_T *c3_dryMass;
  real_T *c3_T_Launch;
  real_T *c3_z0;
  real_T *c3_w0;
  real_T *c3_Area;
  real_T *c3_Time;
  real_T *c3_stop;
  real_T (*c3_acceleration)[2];
  real_T (*c3_velocity)[2];
  real_T (*c3_position)[2];
  c3_stop = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_Time = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c3_Area = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c3_w0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c3_z0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c3_T_Launch = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c3_dryMass = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c3_Cd = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c3_acceleration = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_velocity = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_position = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_set_sim_state_side_effects_c3_Rocket_SM_V2(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
  for (c3_i6 = 0; c3_i6 < 2; c3_i6++) {
    _SFD_DATA_RANGE_CHECK((*c3_position)[c3_i6], 0U);
  }

  for (c3_i7 = 0; c3_i7 < 2; c3_i7++) {
    _SFD_DATA_RANGE_CHECK((*c3_velocity)[c3_i7], 1U);
  }

  for (c3_i8 = 0; c3_i8 < 2; c3_i8++) {
    _SFD_DATA_RANGE_CHECK((*c3_acceleration)[c3_i8], 2U);
  }

  _SFD_DATA_RANGE_CHECK(*c3_Cd, 3U);
  _SFD_DATA_RANGE_CHECK(*c3_dryMass, 4U);
  _SFD_DATA_RANGE_CHECK(*c3_T_Launch, 5U);
  _SFD_DATA_RANGE_CHECK(*c3_z0, 6U);
  _SFD_DATA_RANGE_CHECK(*c3_w0, 7U);
  _SFD_DATA_RANGE_CHECK(*c3_Area, 8U);
  _SFD_DATA_RANGE_CHECK(*c3_Time, 9U);
  _SFD_DATA_RANGE_CHECK(*c3_stop, 10U);
  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_Rocket_SM_V2(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Rocket_SM_V2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c3_chartstep_c3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance)
{
  uint32_T c3_debug_family_var_map[2];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 0.0;
  int32_T c3_i9;
  int32_T c3_i10;
  int32_T c3_i11;
  int32_T c3_i12;
  int32_T c3_i13;
  int32_T c3_i14;
  uint32_T c3_b_debug_family_var_map[3];
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 1.0;
  boolean_T c3_out;
  real_T c3_c_nargin = 0.0;
  real_T c3_c_nargout = 0.0;
  int32_T c3_i15;
  real_T c3_dv3[2];
  int32_T c3_i16;
  real_T c3_dv4[2];
  real_T c3_acceleration[2];
  real_T c3_velocity[2];
  real_T c3_position[2];
  int32_T c3_i17;
  int32_T c3_i18;
  int32_T c3_i19;
  int32_T c3_i20;
  int32_T c3_i21;
  int32_T c3_i22;
  real_T c3_d_nargin = 0.0;
  real_T c3_d_nargout = 0.0;
  int32_T c3_i23;
  real_T c3_dv5[2];
  int32_T c3_i24;
  real_T c3_dv6[2];
  int32_T c3_i25;
  int32_T c3_i26;
  int32_T c3_i27;
  int32_T c3_i28;
  int32_T c3_i29;
  int32_T c3_i30;
  real_T c3_e_nargin = 0.0;
  real_T c3_e_nargout = 1.0;
  boolean_T c3_b_out;
  real_T c3_f_nargin = 0.0;
  real_T c3_f_nargout = 0.0;
  int32_T c3_i31;
  real_T c3_dv7[2];
  int32_T c3_i32;
  real_T c3_dv8[2];
  int32_T c3_i33;
  int32_T c3_i34;
  int32_T c3_i35;
  int32_T c3_i36;
  int32_T c3_i37;
  int32_T c3_i38;
  int32_T c3_i39;
  real_T c3_u[2];
  const mxArray *c3_y = NULL;
  int32_T c3_i40;
  real_T c3_b_u[2];
  const mxArray *c3_b_y = NULL;
  int32_T c3_i41;
  real_T c3_c_u[2];
  const mxArray *c3_c_y = NULL;
  real_T c3_g_nargin = 0.0;
  real_T c3_g_nargout = 1.0;
  boolean_T c3_c_out;
  real_T c3_h_nargin = 0.0;
  real_T c3_h_nargout = 0.0;
  real_T c3_i_nargin = 0.0;
  real_T c3_i_nargout = 0.0;
  int32_T c3_i42;
  real_T c3_dv9[2];
  int32_T c3_i43;
  real_T c3_dv10[2];
  int32_T c3_i44;
  int32_T c3_i45;
  int32_T c3_i46;
  int32_T c3_i47;
  int32_T c3_i48;
  int32_T c3_i49;
  real_T *c3_Time;
  real_T *c3_T_Launch;
  real_T *c3_dryMass;
  real_T *c3_Cd;
  real_T *c3_Area;
  real_T *c3_w0;
  real_T *c3_z0;
  real_T *c3_stop;
  real_T (*c3_b_position)[2];
  real_T (*c3_b_velocity)[2];
  real_T (*c3_b_acceleration)[2];
  c3_stop = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_Time = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c3_Area = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c3_w0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c3_z0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c3_T_Launch = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c3_dryMass = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c3_Cd = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c3_b_acceleration = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_b_velocity = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_position = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
  if (chartInstance->c3_is_active_c3_Rocket_SM_V2 == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
    chartInstance->c3_is_active_c3_Rocket_SM_V2 = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_f_debug_family_names,
      c3_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    for (c3_i9 = 0; c3_i9 < 2; c3_i9++) {
      (*c3_b_acceleration)[c3_i9] = 0.0;
    }

    c3_updateDataWrittenToVector(chartInstance, 2U);
    for (c3_i10 = 0; c3_i10 < 2; c3_i10++) {
      _SFD_DATA_RANGE_CHECK((*c3_b_acceleration)[c3_i10], 2U);
    }

    for (c3_i11 = 0; c3_i11 < 2; c3_i11++) {
      (*c3_b_velocity)[c3_i11] = 0.0;
    }

    c3_updateDataWrittenToVector(chartInstance, 1U);
    for (c3_i12 = 0; c3_i12 < 2; c3_i12++) {
      _SFD_DATA_RANGE_CHECK((*c3_b_velocity)[c3_i12], 1U);
    }

    for (c3_i13 = 0; c3_i13 < 2; c3_i13++) {
      (*c3_b_position)[c3_i13] = 0.0;
    }

    c3_updateDataWrittenToVector(chartInstance, 0U);
    for (c3_i14 = 0; c3_i14 < 2; c3_i14++) {
      _SFD_DATA_RANGE_CHECK((*c3_b_position)[c3_i14], 0U);
    }

    _SFD_SYMBOL_SCOPE_POP();
    chartInstance->c3_is_c3_Rocket_SM_V2 = c3_IN_PreLaunch;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c3_sfEvent);
    chartInstance->c3_tp_PreLaunch = 1U;
  } else {
    switch (chartInstance->c3_is_c3_Rocket_SM_V2) {
     case c3_IN_GuideRail:
      CV_CHART_EVAL(0, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                   chartInstance->c3_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_h_debug_family_names,
        c3_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
        c3_b_sf_marshallIn);
      c3_errorIfDataNotWrittenToFcn(chartInstance, 0U, 0U);
      c3_out = CV_EML_IF(3, 0, 0, (*c3_b_position)[1] >= 5.0);
      _SFD_SYMBOL_SCOPE_POP();
      if (c3_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c3_sfEvent);
        chartInstance->c3_tp_GuideRail = 0U;
        _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 0U,
                     chartInstance->c3_sfEvent);
        sf_call_output_fcn_disable(chartInstance->S, 0, "GuideRailFlight", 0);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c3_sfEvent);
        chartInstance->c3_is_c3_Rocket_SM_V2 = c3_IN_Unconstrained;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c3_sfEvent);
        chartInstance->c3_tp_Unconstrained = 1U;
        sf_call_output_fcn_enable(chartInstance->S, 1, "UnconstrainedFlight", 0);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_c_debug_family_names,
          c3_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 1U, 1U);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 0U, 0U);
        for (c3_i15 = 0; c3_i15 < 2; c3_i15++) {
          c3_dv3[c3_i15] = (*c3_b_velocity)[c3_i15];
        }

        for (c3_i16 = 0; c3_i16 < 2; c3_i16++) {
          c3_dv4[c3_i16] = (*c3_b_position)[c3_i16];
        }

        c3_UnconstrainedFlight(chartInstance, *c3_Time, *c3_T_Launch,
          *c3_dryMass, *c3_Cd, *c3_Area, *c3_w0, *c3_z0, c3_dv3, c3_dv4,
          c3_position, c3_velocity, c3_acceleration);
        for (c3_i17 = 0; c3_i17 < 2; c3_i17++) {
          (*c3_b_position)[c3_i17] = c3_position[c3_i17];
        }

        c3_updateDataWrittenToVector(chartInstance, 0U);
        for (c3_i18 = 0; c3_i18 < 2; c3_i18++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_position)[c3_i18], 0U);
        }

        for (c3_i19 = 0; c3_i19 < 2; c3_i19++) {
          (*c3_b_velocity)[c3_i19] = c3_velocity[c3_i19];
        }

        c3_updateDataWrittenToVector(chartInstance, 1U);
        for (c3_i20 = 0; c3_i20 < 2; c3_i20++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_velocity)[c3_i20], 1U);
        }

        for (c3_i21 = 0; c3_i21 < 2; c3_i21++) {
          (*c3_b_acceleration)[c3_i21] = c3_acceleration[c3_i21];
        }

        c3_updateDataWrittenToVector(chartInstance, 2U);
        for (c3_i22 = 0; c3_i22 < 2; c3_i22++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_acceleration)[c3_i22], 2U);
        }

        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                     chartInstance->c3_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_b_debug_family_names,
          c3_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 1U, 1U);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 0U, 0U);
        for (c3_i23 = 0; c3_i23 < 2; c3_i23++) {
          c3_dv5[c3_i23] = (*c3_b_velocity)[c3_i23];
        }

        for (c3_i24 = 0; c3_i24 < 2; c3_i24++) {
          c3_dv6[c3_i24] = (*c3_b_position)[c3_i24];
        }

        c3_GuideRailFlight(chartInstance, *c3_Time, *c3_T_Launch, *c3_dryMass,
                           *c3_Cd, *c3_Area, c3_dv5, c3_dv6, c3_position,
                           c3_velocity, c3_acceleration);
        for (c3_i25 = 0; c3_i25 < 2; c3_i25++) {
          (*c3_b_position)[c3_i25] = c3_position[c3_i25];
        }

        c3_updateDataWrittenToVector(chartInstance, 0U);
        for (c3_i26 = 0; c3_i26 < 2; c3_i26++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_position)[c3_i26], 0U);
        }

        for (c3_i27 = 0; c3_i27 < 2; c3_i27++) {
          (*c3_b_velocity)[c3_i27] = c3_velocity[c3_i27];
        }

        c3_updateDataWrittenToVector(chartInstance, 1U);
        for (c3_i28 = 0; c3_i28 < 2; c3_i28++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_velocity)[c3_i28], 1U);
        }

        for (c3_i29 = 0; c3_i29 < 2; c3_i29++) {
          (*c3_b_acceleration)[c3_i29] = c3_acceleration[c3_i29];
        }

        c3_updateDataWrittenToVector(chartInstance, 2U);
        for (c3_i30 = 0; c3_i30 < 2; c3_i30++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_acceleration)[c3_i30], 2U);
        }

        _SFD_SYMBOL_SCOPE_POP();
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
      break;

     case c3_IN_Landed:
      CV_CHART_EVAL(0, 0, 2);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                   chartInstance->c3_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
      break;

     case c3_IN_PreLaunch:
      CV_CHART_EVAL(0, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   chartInstance->c3_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_g_debug_family_names,
        c3_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_e_nargin, 0U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_e_nargout, 1U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_out, 2U, c3_b_sf_marshallOut,
        c3_b_sf_marshallIn);
      c3_b_out = CV_EML_IF(1, 0, 0, *c3_Time >= *c3_T_Launch);
      _SFD_SYMBOL_SCOPE_POP();
      if (c3_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c3_sfEvent);
        chartInstance->c3_tp_PreLaunch = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c3_sfEvent);
        chartInstance->c3_is_c3_Rocket_SM_V2 = c3_IN_GuideRail;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c3_sfEvent);
        chartInstance->c3_tp_GuideRail = 1U;
        sf_call_output_fcn_enable(chartInstance->S, 0, "GuideRailFlight", 0);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_debug_family_names,
          c3_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_f_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_f_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 1U, 1U);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 0U, 0U);
        for (c3_i31 = 0; c3_i31 < 2; c3_i31++) {
          c3_dv7[c3_i31] = (*c3_b_velocity)[c3_i31];
        }

        for (c3_i32 = 0; c3_i32 < 2; c3_i32++) {
          c3_dv8[c3_i32] = (*c3_b_position)[c3_i32];
        }

        c3_GuideRailFlight(chartInstance, *c3_Time, *c3_T_Launch, *c3_dryMass,
                           *c3_Cd, *c3_Area, c3_dv7, c3_dv8, c3_position,
                           c3_velocity, c3_acceleration);
        for (c3_i33 = 0; c3_i33 < 2; c3_i33++) {
          (*c3_b_position)[c3_i33] = c3_position[c3_i33];
        }

        c3_updateDataWrittenToVector(chartInstance, 0U);
        for (c3_i34 = 0; c3_i34 < 2; c3_i34++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_position)[c3_i34], 0U);
        }

        for (c3_i35 = 0; c3_i35 < 2; c3_i35++) {
          (*c3_b_velocity)[c3_i35] = c3_velocity[c3_i35];
        }

        c3_updateDataWrittenToVector(chartInstance, 1U);
        for (c3_i36 = 0; c3_i36 < 2; c3_i36++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_velocity)[c3_i36], 1U);
        }

        for (c3_i37 = 0; c3_i37 < 2; c3_i37++) {
          (*c3_b_acceleration)[c3_i37] = c3_acceleration[c3_i37];
        }

        c3_updateDataWrittenToVector(chartInstance, 2U);
        for (c3_i38 = 0; c3_i38 < 2; c3_i38++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_acceleration)[c3_i38], 2U);
        }

        c3_errorIfDataNotWrittenToFcn(chartInstance, 0U, 0U);
        sf_mex_printf("%s =\\n", "position");
        for (c3_i39 = 0; c3_i39 < 2; c3_i39++) {
          c3_u[c3_i39] = (*c3_b_position)[c3_i39];
        }

        c3_y = NULL;
        sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 2),
                      false);
        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c3_y);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 1U, 1U);
        sf_mex_printf("%s =\\n", "velocity");
        for (c3_i40 = 0; c3_i40 < 2; c3_i40++) {
          c3_b_u[c3_i40] = (*c3_b_velocity)[c3_i40];
        }

        c3_b_y = NULL;
        sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 0, 0U, 1U, 0U, 1, 2),
                      false);
        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14,
                          c3_b_y);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 2U, 2U);
        sf_mex_printf("%s =\\n", "acceleration");
        for (c3_i41 = 0; c3_i41 < 2; c3_i41++) {
          c3_c_u[c3_i41] = (*c3_b_acceleration)[c3_i41];
        }

        c3_c_y = NULL;
        sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 2),
                      false);
        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14,
                          c3_c_y);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                     chartInstance->c3_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c3_sfEvent);
      break;

     case c3_IN_Unconstrained:
      CV_CHART_EVAL(0, 0, 4);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   chartInstance->c3_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_i_debug_family_names,
        c3_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_g_nargin, 0U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_g_nargout, 1U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_out, 2U, c3_b_sf_marshallOut,
        c3_b_sf_marshallIn);
      c3_errorIfDataNotWrittenToFcn(chartInstance, 0U, 0U);
      c3_c_out = CV_EML_IF(2, 0, 0, (*c3_b_position)[1] <= 0.0);
      _SFD_SYMBOL_SCOPE_POP();
      if (c3_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c3_sfEvent);
        chartInstance->c3_tp_Unconstrained = 0U;
        _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 4U,
                     chartInstance->c3_sfEvent);
        sf_call_output_fcn_disable(chartInstance->S, 1, "UnconstrainedFlight", 0);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c3_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c3_sfEvent);
        chartInstance->c3_is_c3_Rocket_SM_V2 = c3_IN_Landed;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c3_sfEvent);
        chartInstance->c3_tp_Landed = 1U;
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_e_debug_family_names,
          c3_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_h_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_h_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        *c3_stop = 1.0;
        c3_updateDataWrittenToVector(chartInstance, 3U);
        _SFD_DATA_RANGE_CHECK(*c3_stop, 10U);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                     chartInstance->c3_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_d_debug_family_names,
          c3_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_i_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_i_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 1U, 1U);
        c3_errorIfDataNotWrittenToFcn(chartInstance, 0U, 0U);
        for (c3_i42 = 0; c3_i42 < 2; c3_i42++) {
          c3_dv9[c3_i42] = (*c3_b_velocity)[c3_i42];
        }

        for (c3_i43 = 0; c3_i43 < 2; c3_i43++) {
          c3_dv10[c3_i43] = (*c3_b_position)[c3_i43];
        }

        c3_UnconstrainedFlight(chartInstance, *c3_Time, *c3_T_Launch,
          *c3_dryMass, *c3_Cd, *c3_Area, *c3_w0, *c3_z0, c3_dv9, c3_dv10,
          c3_position, c3_velocity, c3_acceleration);
        for (c3_i44 = 0; c3_i44 < 2; c3_i44++) {
          (*c3_b_position)[c3_i44] = c3_position[c3_i44];
        }

        c3_updateDataWrittenToVector(chartInstance, 0U);
        for (c3_i45 = 0; c3_i45 < 2; c3_i45++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_position)[c3_i45], 0U);
        }

        for (c3_i46 = 0; c3_i46 < 2; c3_i46++) {
          (*c3_b_velocity)[c3_i46] = c3_velocity[c3_i46];
        }

        c3_updateDataWrittenToVector(chartInstance, 1U);
        for (c3_i47 = 0; c3_i47 < 2; c3_i47++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_velocity)[c3_i47], 1U);
        }

        for (c3_i48 = 0; c3_i48 < 2; c3_i48++) {
          (*c3_b_acceleration)[c3_i48] = c3_acceleration[c3_i48];
        }

        c3_updateDataWrittenToVector(chartInstance, 2U);
        for (c3_i49 = 0; c3_i49 < 2; c3_i49++) {
          _SFD_DATA_RANGE_CHECK((*c3_b_acceleration)[c3_i49], 2U);
        }

        _SFD_SYMBOL_SCOPE_POP();
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c3_sfEvent);
      break;

     default:
      CV_CHART_EVAL(0, 0, 0);
      chartInstance->c3_is_c3_Rocket_SM_V2 = c3_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c3_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_Rocket_SM_V2(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)c3_machineNumber;
  (void)c3_chartNumber;
  (void)c3_instanceNumber;
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static real_T c3_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  const mxArray *c3_nargout, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  return c3_y;
}

static real_T c3_b_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  boolean_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(boolean_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static boolean_T c3_c_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b0, 1, 11, 0U, 0, 0U, 0);
  c3_y = c3_b0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_sf_internal_predicateOutput;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_sf_internal_predicateOutput = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_sf_internal_predicateOutput), &c3_thisId);
  sf_mex_destroy(&c3_sf_internal_predicateOutput);
  *(boolean_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_Rocket_SM_V2_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c3_nameCaptureInfo;
}

static void c3_GuideRailFlight(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  real_T c3_T, real_T c3_T_L, real_T c3_dryMass, real_T c3_Cd, real_T c3_Area,
  real_T c3_vel[2], real_T c3_pos[2], real_T c3_p[2], real_T c3_v[2], real_T
  c3_a[2])
{
  int32_T c3_i50;
  int32_T c3_i51;
  int32_T c3_i52;
  int32_T c3_i53;
  int32_T c3_i54;
  int32_T c3_i55;
  int32_T c3_i56;
  int32_T c3_i57;
  int32_T c3_i58;
  int32_T c3_i59;
  int32_T c3_i60;
  int32_T c3_i61;
  real_T *c3_b_T;
  real_T *c3_b_T_L;
  real_T *c3_b_dryMass;
  real_T *c3_b_Cd;
  real_T *c3_b_Area;
  real_T (*c3_b_pos)[2];
  real_T (*c3_b_vel)[2];
  real_T (*c3_b_a)[2];
  real_T (*c3_b_v)[2];
  real_T (*c3_b_p)[2];
  c3_b_a = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 9);
  c3_b_v = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 8);
  c3_b_p = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 7);
  c3_b_pos = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 11);
  c3_b_vel = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 10);
  c3_b_Area = (real_T *)ssGetOutputPortSignal(chartInstance->S, 9);
  c3_b_Cd = (real_T *)ssGetOutputPortSignal(chartInstance->S, 8);
  c3_b_dryMass = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c3_b_T_L = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c3_b_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  _SFD_DATA_RANGE_CHECK(c3_T, 11U);
  _SFD_DATA_RANGE_CHECK(c3_T_L, 12U);
  _SFD_DATA_RANGE_CHECK(c3_dryMass, 13U);
  _SFD_DATA_RANGE_CHECK(c3_Cd, 14U);
  _SFD_DATA_RANGE_CHECK(c3_Area, 15U);
  for (c3_i50 = 0; c3_i50 < 2; c3_i50++) {
    _SFD_DATA_RANGE_CHECK(c3_vel[c3_i50], 16U);
  }

  for (c3_i51 = 0; c3_i51 < 2; c3_i51++) {
    _SFD_DATA_RANGE_CHECK(c3_pos[c3_i51], 17U);
  }

  _SFD_SET_DATA_VALUE_PTR(20U, c3_a);
  _SFD_SET_DATA_VALUE_PTR(19U, c3_v);
  _SFD_SET_DATA_VALUE_PTR(18U, c3_p);
  _SFD_SET_DATA_VALUE_PTR(17U, c3_pos);
  _SFD_SET_DATA_VALUE_PTR(16U, c3_vel);
  _SFD_SET_DATA_VALUE_PTR(15U, &c3_Area);
  _SFD_SET_DATA_VALUE_PTR(14U, &c3_Cd);
  _SFD_SET_DATA_VALUE_PTR(13U, &c3_dryMass);
  _SFD_SET_DATA_VALUE_PTR(12U, &c3_T_L);
  _SFD_SET_DATA_VALUE_PTR(11U, &c3_T);
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 1U, chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH(10U, 0U);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("T", &c3_T, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("T_L", &c3_T_L, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("dryMass", &c3_dryMass, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("Cd", &c3_Cd, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("Area", &c3_Area, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("vel", c3_vel, c3_f_sf_marshallOut,
    c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("pos", c3_pos, c3_f_sf_marshallOut,
    c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("p", c3_p, c3_f_sf_marshallOut,
    c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("v", c3_v, c3_f_sf_marshallOut,
    c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("a", c3_a, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  *c3_b_T = c3_T;
  _SFD_DATA_RANGE_CHECK(*c3_b_T, 11U);
  *c3_b_T_L = c3_T_L;
  _SFD_DATA_RANGE_CHECK(*c3_b_T_L, 12U);
  *c3_b_dryMass = c3_dryMass;
  _SFD_DATA_RANGE_CHECK(*c3_b_dryMass, 13U);
  *c3_b_Cd = c3_Cd;
  _SFD_DATA_RANGE_CHECK(*c3_b_Cd, 14U);
  *c3_b_Area = c3_Area;
  _SFD_DATA_RANGE_CHECK(*c3_b_Area, 15U);
  for (c3_i52 = 0; c3_i52 < 2; c3_i52++) {
    (*c3_b_vel)[c3_i52] = c3_vel[c3_i52];
  }

  for (c3_i53 = 0; c3_i53 < 2; c3_i53++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_vel)[c3_i53], 16U);
  }

  for (c3_i54 = 0; c3_i54 < 2; c3_i54++) {
    (*c3_b_pos)[c3_i54] = c3_pos[c3_i54];
  }

  for (c3_i55 = 0; c3_i55 < 2; c3_i55++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_pos)[c3_i55], 17U);
  }

  sf_call_output_fcn_call(chartInstance->S, 0, "GuideRailFlight", 0);
  for (c3_i56 = 0; c3_i56 < 2; c3_i56++) {
    c3_p[c3_i56] = (*c3_b_p)[c3_i56];
  }

  c3_updateDataWrittenToVector(chartInstance, 4U);
  for (c3_i57 = 0; c3_i57 < 2; c3_i57++) {
    _SFD_DATA_RANGE_CHECK(c3_p[c3_i57], 18U);
  }

  for (c3_i58 = 0; c3_i58 < 2; c3_i58++) {
    c3_v[c3_i58] = (*c3_b_v)[c3_i58];
  }

  c3_updateDataWrittenToVector(chartInstance, 5U);
  for (c3_i59 = 0; c3_i59 < 2; c3_i59++) {
    _SFD_DATA_RANGE_CHECK(c3_v[c3_i59], 19U);
  }

  for (c3_i60 = 0; c3_i60 < 2; c3_i60++) {
    c3_a[c3_i60] = (*c3_b_a)[c3_i60];
  }

  c3_updateDataWrittenToVector(chartInstance, 6U);
  for (c3_i61 = 0; c3_i61 < 2; c3_i61++) {
    _SFD_DATA_RANGE_CHECK(c3_a[c3_i61], 20U);
  }

  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 1U, chartInstance->c3_sfEvent);
  _SFD_UNSET_DATA_VALUE_PTR(20U);
  _SFD_UNSET_DATA_VALUE_PTR(19U);
  _SFD_UNSET_DATA_VALUE_PTR(18U);
  _SFD_UNSET_DATA_VALUE_PTR(17U);
  _SFD_UNSET_DATA_VALUE_PTR(16U);
  _SFD_UNSET_DATA_VALUE_PTR(15U);
  _SFD_UNSET_DATA_VALUE_PTR(14U);
  _SFD_UNSET_DATA_VALUE_PTR(13U);
  _SFD_UNSET_DATA_VALUE_PTR(12U);
  _SFD_UNSET_DATA_VALUE_PTR(11U);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
}

static void c3_UnconstrainedFlight(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, real_T c3_T, real_T c3_T_L, real_T c3_dryMass, real_T c3_Cd,
  real_T c3_Area, real_T c3_w0, real_T c3_z0, real_T c3_vel[2], real_T c3_pos[2],
  real_T c3_p[2], real_T c3_v[2], real_T c3_a[2])
{
  int32_T c3_i62;
  int32_T c3_i63;
  int32_T c3_i64;
  int32_T c3_i65;
  int32_T c3_i66;
  int32_T c3_i67;
  int32_T c3_i68;
  int32_T c3_i69;
  int32_T c3_i70;
  int32_T c3_i71;
  int32_T c3_i72;
  int32_T c3_i73;
  real_T *c3_b_T;
  real_T *c3_b_T_L;
  real_T *c3_b_dryMass;
  real_T *c3_b_Cd;
  real_T *c3_b_Area;
  real_T *c3_b_w0;
  real_T *c3_b_z0;
  real_T (*c3_b_pos)[2];
  real_T (*c3_b_vel)[2];
  real_T (*c3_b_a)[2];
  real_T (*c3_b_v)[2];
  real_T (*c3_b_p)[2];
  c3_b_a = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 12);
  c3_b_v = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 11);
  c3_b_p = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 10);
  c3_b_pos = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 20);
  c3_b_vel = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 19);
  c3_b_z0 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 18);
  c3_b_w0 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 17);
  c3_b_Area = (real_T *)ssGetOutputPortSignal(chartInstance->S, 16);
  c3_b_Cd = (real_T *)ssGetOutputPortSignal(chartInstance->S, 15);
  c3_b_dryMass = (real_T *)ssGetOutputPortSignal(chartInstance->S, 14);
  c3_b_T_L = (real_T *)ssGetOutputPortSignal(chartInstance->S, 13);
  c3_b_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 12);
  _SFD_DATA_RANGE_CHECK(c3_T, 21U);
  _SFD_DATA_RANGE_CHECK(c3_T_L, 22U);
  _SFD_DATA_RANGE_CHECK(c3_dryMass, 23U);
  _SFD_DATA_RANGE_CHECK(c3_Cd, 24U);
  _SFD_DATA_RANGE_CHECK(c3_Area, 25U);
  _SFD_DATA_RANGE_CHECK(c3_w0, 26U);
  _SFD_DATA_RANGE_CHECK(c3_z0, 27U);
  for (c3_i62 = 0; c3_i62 < 2; c3_i62++) {
    _SFD_DATA_RANGE_CHECK(c3_vel[c3_i62], 28U);
  }

  for (c3_i63 = 0; c3_i63 < 2; c3_i63++) {
    _SFD_DATA_RANGE_CHECK(c3_pos[c3_i63], 29U);
  }

  _SFD_SET_DATA_VALUE_PTR(32U, c3_a);
  _SFD_SET_DATA_VALUE_PTR(31U, c3_v);
  _SFD_SET_DATA_VALUE_PTR(30U, c3_p);
  _SFD_SET_DATA_VALUE_PTR(29U, c3_pos);
  _SFD_SET_DATA_VALUE_PTR(28U, c3_vel);
  _SFD_SET_DATA_VALUE_PTR(27U, &c3_z0);
  _SFD_SET_DATA_VALUE_PTR(26U, &c3_w0);
  _SFD_SET_DATA_VALUE_PTR(25U, &c3_Area);
  _SFD_SET_DATA_VALUE_PTR(24U, &c3_Cd);
  _SFD_SET_DATA_VALUE_PTR(23U, &c3_dryMass);
  _SFD_SET_DATA_VALUE_PTR(22U, &c3_T_L);
  _SFD_SET_DATA_VALUE_PTR(21U, &c3_T);
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 5U, chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH(12U, 0U);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("T", &c3_T, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("T_L", &c3_T_L, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("dryMass", &c3_dryMass, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("Cd", &c3_Cd, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("Area", &c3_Area, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("w0", &c3_w0, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("z0", &c3_z0, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("vel", c3_vel, c3_f_sf_marshallOut,
    c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("pos", c3_pos, c3_f_sf_marshallOut,
    c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("p", c3_p, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("v", c3_v, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("a", c3_a, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c3_sfEvent);
  *c3_b_T = c3_T;
  _SFD_DATA_RANGE_CHECK(*c3_b_T, 21U);
  *c3_b_T_L = c3_T_L;
  _SFD_DATA_RANGE_CHECK(*c3_b_T_L, 22U);
  *c3_b_dryMass = c3_dryMass;
  _SFD_DATA_RANGE_CHECK(*c3_b_dryMass, 23U);
  *c3_b_Cd = c3_Cd;
  _SFD_DATA_RANGE_CHECK(*c3_b_Cd, 24U);
  *c3_b_Area = c3_Area;
  _SFD_DATA_RANGE_CHECK(*c3_b_Area, 25U);
  *c3_b_w0 = c3_w0;
  _SFD_DATA_RANGE_CHECK(*c3_b_w0, 26U);
  *c3_b_z0 = c3_z0;
  _SFD_DATA_RANGE_CHECK(*c3_b_z0, 27U);
  for (c3_i64 = 0; c3_i64 < 2; c3_i64++) {
    (*c3_b_vel)[c3_i64] = c3_vel[c3_i64];
  }

  for (c3_i65 = 0; c3_i65 < 2; c3_i65++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_vel)[c3_i65], 28U);
  }

  for (c3_i66 = 0; c3_i66 < 2; c3_i66++) {
    (*c3_b_pos)[c3_i66] = c3_pos[c3_i66];
  }

  for (c3_i67 = 0; c3_i67 < 2; c3_i67++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_pos)[c3_i67], 29U);
  }

  sf_call_output_fcn_call(chartInstance->S, 1, "UnconstrainedFlight", 0);
  for (c3_i68 = 0; c3_i68 < 2; c3_i68++) {
    c3_p[c3_i68] = (*c3_b_p)[c3_i68];
  }

  c3_updateDataWrittenToVector(chartInstance, 7U);
  for (c3_i69 = 0; c3_i69 < 2; c3_i69++) {
    _SFD_DATA_RANGE_CHECK(c3_p[c3_i69], 30U);
  }

  for (c3_i70 = 0; c3_i70 < 2; c3_i70++) {
    c3_v[c3_i70] = (*c3_b_v)[c3_i70];
  }

  c3_updateDataWrittenToVector(chartInstance, 8U);
  for (c3_i71 = 0; c3_i71 < 2; c3_i71++) {
    _SFD_DATA_RANGE_CHECK(c3_v[c3_i71], 31U);
  }

  for (c3_i72 = 0; c3_i72 < 2; c3_i72++) {
    c3_a[c3_i72] = (*c3_b_a)[c3_i72];
  }

  c3_updateDataWrittenToVector(chartInstance, 9U);
  for (c3_i73 = 0; c3_i73 < 2; c3_i73++) {
    _SFD_DATA_RANGE_CHECK(c3_a[c3_i73], 32U);
  }

  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 5U, chartInstance->c3_sfEvent);
  _SFD_UNSET_DATA_VALUE_PTR(32U);
  _SFD_UNSET_DATA_VALUE_PTR(31U);
  _SFD_UNSET_DATA_VALUE_PTR(30U);
  _SFD_UNSET_DATA_VALUE_PTR(29U);
  _SFD_UNSET_DATA_VALUE_PTR(28U);
  _SFD_UNSET_DATA_VALUE_PTR(27U);
  _SFD_UNSET_DATA_VALUE_PTR(26U);
  _SFD_UNSET_DATA_VALUE_PTR(25U);
  _SFD_UNSET_DATA_VALUE_PTR(24U);
  _SFD_UNSET_DATA_VALUE_PTR(23U);
  _SFD_UNSET_DATA_VALUE_PTR(22U);
  _SFD_UNSET_DATA_VALUE_PTR(21U);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c3_sfEvent);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_d_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i74;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i74, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i74;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  uint8_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(uint8_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static uint8_T c3_e_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_b_tp_PreLaunch, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_tp_PreLaunch),
    &c3_thisId);
  sf_mex_destroy(&c3_b_tp_PreLaunch);
  return c3_y;
}

static uint8_T c3_f_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_tp_PreLaunch;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_b_tp_PreLaunch = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_tp_PreLaunch),
    &c3_thisId);
  sf_mex_destroy(&c3_b_tp_PreLaunch);
  *(uint8_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i75;
  real_T c3_b_inData[2];
  int32_T c3_i76;
  real_T c3_u[2];
  const mxArray *c3_y = NULL;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i75 = 0; c3_i75 < 2; c3_i75++) {
    c3_b_inData[c3_i75] = (*(real_T (*)[2])c3_inData)[c3_i75];
  }

  for (c3_i76 = 0; c3_i76 < 2; c3_i76++) {
    c3_u[c3_i76] = c3_b_inData[c3_i76];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_g_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  const mxArray *c3_position, const char_T *c3_identifier, real_T c3_y[2])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_position), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_position);
}

static void c3_h_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2])
{
  real_T c3_dv11[2];
  int32_T c3_i77;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv11, 1, 0, 0U, 1, 0U, 1, 2);
  for (c3_i77 = 0; c3_i77 < 2; c3_i77++) {
    c3_y[c3_i77] = c3_dv11[c3_i77];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_position;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[2];
  int32_T c3_i78;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_position = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_position), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_position);
  for (c3_i78 = 0; c3_i78 < 2; c3_i78++) {
    (*(real_T (*)[2])c3_outData)[c3_i78] = c3_y[c3_i78];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i79;
  real_T c3_b_inData[2];
  int32_T c3_i80;
  real_T c3_u[2];
  const mxArray *c3_y = NULL;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i79 = 0; c3_i79 < 2; c3_i79++) {
    c3_b_inData[c3_i79] = (*(real_T (*)[2])c3_inData)[c3_i79];
  }

  for (c3_i80 = 0; c3_i80 < 2; c3_i80++) {
    c3_u[c3_i80] = c3_b_inData[c3_i80];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 2, 1), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_i_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2])
{
  real_T c3_dv12[2];
  int32_T c3_i81;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv12, 1, 0, 0U, 1, 0U, 2, 2, 1);
  for (c3_i81 = 0; c3_i81 < 2; c3_i81++) {
    c3_y[c3_i81] = c3_dv12[c3_i81];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_vel;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[2];
  int32_T c3_i82;
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)chartInstanceVoid;
  c3_vel = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_vel), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_vel);
  for (c3_i82 = 0; c3_i82 < 2; c3_i82++) {
    (*(real_T (*)[2])c3_outData)[c3_i82] = c3_y[c3_i82];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_j_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_b_setSimStateSideEffectsInfo, const char_T
  *c3_identifier)
{
  const mxArray *c3_y = NULL;
  emlrtMsgIdentifier c3_thisId;
  c3_y = NULL;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  sf_mex_assign(&c3_y, c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_setSimStateSideEffectsInfo), &c3_thisId), false);
  sf_mex_destroy(&c3_b_setSimStateSideEffectsInfo);
  return c3_y;
}

static const mxArray *c3_k_emlrt_marshallIn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  const mxArray *c3_y = NULL;
  (void)chartInstance;
  (void)c3_parentId;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_duplicatearraysafe(&c3_u), false);
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_updateDataWrittenToVector(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, uint32_T c3_vectorIndex)
{
  (void)chartInstance;
  c3_dataWrittenToVector[(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK(0, (int32_T)
    c3_vectorIndex, 0, 9, 1, 0)] = true;
}

static void c3_errorIfDataNotWrittenToFcn(SFc3_Rocket_SM_V2InstanceStruct
  *chartInstance, uint32_T c3_vectorIndex, uint32_T c3_dataNumber)
{
  (void)chartInstance;
  _SFD_DATA_READ_BEFORE_WRITE_CHECK(c3_dataNumber, c3_dataWrittenToVector
    [(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK(0, (int32_T)c3_vectorIndex, 0, 9, 1,
    0)]);
}

static void init_dsm_address_info(SFc3_Rocket_SM_V2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c3_Rocket_SM_V2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3869122816U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3310134957U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2848663379U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(909158228U);
}

mxArray *sf_c3_Rocket_SM_V2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("Eh6LvXoSdGxUQQxh67fGHB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_Rocket_SM_V2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_Rocket_SM_V2_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c3_Rocket_SM_V2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[44],T\"acceleration\",},{M[1],M[42],T\"position\",},{M[1],M[52],T\"stop\",},{M[1],M[43],T\"velocity\",},{M[8],M[0],T\"is_active_c3_Rocket_SM_V2\",},{M[9],M[0],T\"is_c3_Rocket_SM_V2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_Rocket_SM_V2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Rocket_SM_V2MachineNumber_,
           3,
           6,
           4,
           0,
           33,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_Rocket_SM_V2MachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_Rocket_SM_V2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _Rocket_SM_V2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"position");
          _SFD_SET_DATA_PROPS(1,2,0,1,"velocity");
          _SFD_SET_DATA_PROPS(2,2,0,1,"acceleration");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Cd");
          _SFD_SET_DATA_PROPS(4,1,1,0,"dryMass");
          _SFD_SET_DATA_PROPS(5,1,1,0,"T_Launch");
          _SFD_SET_DATA_PROPS(6,1,1,0,"z0");
          _SFD_SET_DATA_PROPS(7,1,1,0,"w0");
          _SFD_SET_DATA_PROPS(8,1,1,0,"Area");
          _SFD_SET_DATA_PROPS(9,1,1,0,"Time");
          _SFD_SET_DATA_PROPS(10,2,0,1,"stop");
          _SFD_SET_DATA_PROPS(11,8,0,0,"");
          _SFD_SET_DATA_PROPS(12,8,0,0,"");
          _SFD_SET_DATA_PROPS(13,8,0,0,"");
          _SFD_SET_DATA_PROPS(14,8,0,0,"");
          _SFD_SET_DATA_PROPS(15,8,0,0,"");
          _SFD_SET_DATA_PROPS(16,8,0,0,"");
          _SFD_SET_DATA_PROPS(17,8,0,0,"");
          _SFD_SET_DATA_PROPS(18,9,0,0,"");
          _SFD_SET_DATA_PROPS(19,9,0,0,"");
          _SFD_SET_DATA_PROPS(20,9,0,0,"");
          _SFD_SET_DATA_PROPS(21,8,0,0,"");
          _SFD_SET_DATA_PROPS(22,8,0,0,"");
          _SFD_SET_DATA_PROPS(23,8,0,0,"");
          _SFD_SET_DATA_PROPS(24,8,0,0,"");
          _SFD_SET_DATA_PROPS(25,8,0,0,"");
          _SFD_SET_DATA_PROPS(26,8,0,0,"");
          _SFD_SET_DATA_PROPS(27,8,0,0,"");
          _SFD_SET_DATA_PROPS(28,8,0,0,"");
          _SFD_SET_DATA_PROPS(29,8,0,0,"");
          _SFD_SET_DATA_PROPS(30,9,0,0,"");
          _SFD_SET_DATA_PROPS(31,9,0,0,"");
          _SFD_SET_DATA_PROPS(32,9,0,0,"");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(1,0,2);
          _SFD_STATE_INFO(5,0,2);
          _SFD_CH_SUBSTATE_COUNT(4);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,2);
          _SFD_CH_SUBSTATE_INDEX(2,3);
          _SFD_CH_SUBSTATE_INDEX(3,4);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
        }

        _SFD_CV_INIT_CHART(4,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(4,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(1,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(1,0,0,1,16,1,16);
        _SFD_CV_INIT_EML(3,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(3,0,0,1,15,1,15);
        _SFD_CV_INIT_EML(2,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(2,0,0,1,15,1,15);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(21,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(28,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(29,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(30,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(31,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(32,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        _SFD_SET_DATA_VALUE_PTR(11,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(12,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(13,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(14,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(15,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(16,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(17,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(18,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(19,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(20,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(21,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(22,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(23,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(24,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(25,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(26,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(27,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(28,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(29,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(30,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(31,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(32,(void *)(NULL));

        {
          real_T *c3_Cd;
          real_T *c3_dryMass;
          real_T *c3_T_Launch;
          real_T *c3_z0;
          real_T *c3_w0;
          real_T *c3_Area;
          real_T *c3_Time;
          real_T *c3_stop;
          real_T (*c3_position)[2];
          real_T (*c3_velocity)[2];
          real_T (*c3_acceleration)[2];
          c3_stop = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c3_Time = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c3_Area = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c3_w0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c3_z0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c3_T_Launch = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c3_dryMass = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c3_Cd = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          c3_acceleration = (real_T (*)[2])ssGetOutputPortSignal
            (chartInstance->S, 3);
          c3_velocity = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
          c3_position = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_position);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_velocity);
          _SFD_SET_DATA_VALUE_PTR(2U, *c3_acceleration);
          _SFD_SET_DATA_VALUE_PTR(3U, c3_Cd);
          _SFD_SET_DATA_VALUE_PTR(4U, c3_dryMass);
          _SFD_SET_DATA_VALUE_PTR(5U, c3_T_Launch);
          _SFD_SET_DATA_VALUE_PTR(6U, c3_z0);
          _SFD_SET_DATA_VALUE_PTR(7U, c3_w0);
          _SFD_SET_DATA_VALUE_PTR(8U, c3_Area);
          _SFD_SET_DATA_VALUE_PTR(9U, c3_Time);
          _SFD_SET_DATA_VALUE_PTR(10U, c3_stop);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _Rocket_SM_V2MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "bSUus0teaElR3xqKaslNw";
}

static void sf_opaque_initialize_c3_Rocket_SM_V2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_Rocket_SM_V2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_Rocket_SM_V2((SFc3_Rocket_SM_V2InstanceStruct*)
    chartInstanceVar);
  initialize_c3_Rocket_SM_V2((SFc3_Rocket_SM_V2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_Rocket_SM_V2(void *chartInstanceVar)
{
  enable_c3_Rocket_SM_V2((SFc3_Rocket_SM_V2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_Rocket_SM_V2(void *chartInstanceVar)
{
  disable_c3_Rocket_SM_V2((SFc3_Rocket_SM_V2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_Rocket_SM_V2(void *chartInstanceVar)
{
  sf_gateway_c3_Rocket_SM_V2((SFc3_Rocket_SM_V2InstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_Rocket_SM_V2(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_Rocket_SM_V2
    ((SFc3_Rocket_SM_V2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_Rocket_SM_V2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c3_Rocket_SM_V2(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c3_Rocket_SM_V2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_Rocket_SM_V2((SFc3_Rocket_SM_V2InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_Rocket_SM_V2(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_Rocket_SM_V2(S);
}

static void sf_opaque_set_sim_state_c3_Rocket_SM_V2(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c3_Rocket_SM_V2(S, st);
}

static void sf_opaque_terminate_c3_Rocket_SM_V2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_Rocket_SM_V2InstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Rocket_SM_V2_optimization_info();
    }

    finalize_c3_Rocket_SM_V2((SFc3_Rocket_SM_V2InstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_Rocket_SM_V2((SFc3_Rocket_SM_V2InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_Rocket_SM_V2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c3_Rocket_SM_V2((SFc3_Rocket_SM_V2InstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_Rocket_SM_V2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Rocket_SM_V2_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,3);
    sf_mark_output_events_with_multiple_callers(S,sf_get_instance_specialization
      (),infoStruct,3,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,7);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,20);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=20; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 13; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(204409742U));
  ssSetChecksum1(S,(1008064231U));
  ssSetChecksum2(S,(298158584U));
  ssSetChecksum3(S,(2435699854U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_Rocket_SM_V2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c3_Rocket_SM_V2(SimStruct *S)
{
  SFc3_Rocket_SM_V2InstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc3_Rocket_SM_V2InstanceStruct *)utMalloc(sizeof
    (SFc3_Rocket_SM_V2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_Rocket_SM_V2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_Rocket_SM_V2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_Rocket_SM_V2;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_Rocket_SM_V2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_Rocket_SM_V2;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_Rocket_SM_V2;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_Rocket_SM_V2;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_Rocket_SM_V2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_Rocket_SM_V2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_Rocket_SM_V2;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_Rocket_SM_V2;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_Rocket_SM_V2;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c3_Rocket_SM_V2_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_Rocket_SM_V2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_Rocket_SM_V2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_Rocket_SM_V2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_Rocket_SM_V2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
