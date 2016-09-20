// Source MD5: 9f9832420e4b4eed09989e24e70e3677

#include "modelheader.h"

// DEFS:
#define INITFUN___ _model_housemodel_main__
#define ODEFUN___ _model_housemodel_ode__
#define TABLECODE___ _model_housemodel_table__
#define CONFIGFUN___ _model_housemodel_config__
#define _nEQ 3
#define _nPAR 13
#define N_GUT 1
#define F_GUT _F_[0]
#define ALAG_GUT _ALAG_[0]
#define R_GUT _R_[0]
#define D_GUT _D_[0]
#define GUT _A_[0]
#define CENT _A_[1]
#define RESP _A_[2]
#define GUT_0 _A_0_[0]
#define CENT_0 _A_0_[1]
#define RESP_0 _A_0_[2]
#define dxdt_GUT _DADT_[0]
#define dxdt_CENT _DADT_[1]
#define dxdt_RESP _DADT_[2]
#define CL _THETA_[0]
#define VC _THETA_[1]
#define KA _THETA_[2]
#define F1 _THETA_[3]
#define WT _THETA_[4]
#define SEX _THETA_[5]
#define WTCL _THETA_[6]
#define WTVC _THETA_[7]
#define SEXCL _THETA_[8]
#define SEXVC _THETA_[9]
#define KIN _THETA_[10]
#define KOUT _THETA_[11]
#define IC50 _THETA_[12]
#define ECL _xETA(1)
#define EVC _xETA(2)
#define EKA _xETA(3)
#define EKOUT _xETA(4)
#define EXPO _xEPS(1)

// FIXED:
// No fixed parameters.

// INCLUDES:
// No includes found.

// GLOBAL CODE BLOCK:
// GLOBAL VARS FROM BLOCKS & TYPEDEFS:
typedef double capture;
namespace {
  double CLi;
  double VCi;
  double KAi;
  double KOUTi;
  double DV;
}
typedef double localdouble;
typedef int localint;
typedef bool localbool;

// GLOBAL START USER CODE:
#define CP (CENT/VCi)
#define INH (CP/(IC50+CP))
typedef double localdouble;

// CONFIG CODE BLOCK:
BEGIN_config
END_config

// MAIN CODE BLOCK:
BEGIN_main
F_GUT = F1;
CLi   = exp(log(CL)   + WTCL*log(WT/70) + log(SEXCL)*SEX + ECL);
VCi   = exp(log(VC)   + WTVC*log(WT/70) + log(SEXVC)*SEX + EVC);
KAi   = exp(log(KA)   + EKA);
KOUTi = exp(log(KOUT) + EKOUT);
RESP_0 = KIN/KOUTi;
END_main

// DIFFERENTIAL EQUATIONS:
BEGIN_ode
dxdt_GUT = -KAi*GUT;
dxdt_CENT = KAi*GUT - (CLi/VCi)*CENT;
dxdt_RESP = KIN*(1-INH) - KOUTi*RESP;
END_ode

// TABLE CODE BLOCK:
BEGIN_table
DV = CP*exp(EXPO);
_capture_[0] = DV;
_capture_[1] = CP;
END_table
