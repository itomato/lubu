#ifdef __cplusplus
extern "C" {
#endif
#include <DPS/dpsfriends.h>
/* include/PSopenstep.h generated from src/PSopenstep.psw
   by unix pswrap V1.009  Wed Apr 19 17:50:24 PDT 1989
 */

#ifndef PSOPENSTEP_H
#define PSOPENSTEP_H

extern void PSWait( void );

extern void PScomposite(float x, float y, float w, float h, int gstateNum, float dx, float dy, int op);

extern void DPScomposite(DPSContext ctxt, float x, float y, float w, float h, int gstateNum, float dx, float dy, int op);

extern void PScompositerect(float x, float y, float w, float h, int op);

extern void DPScompositerect(DPSContext ctxt, float x, float y, float w, float h, int op);

extern void PSdissolve(float x, float y, float w, float h, int gstateNum, float dx, float dy, float delta);

extern void DPSdissolve(DPSContext ctxt, float x, float y, float w, float h, int gstateNum, float dx, float dy, float delta);

extern void PSsetalpha(float a);

extern void DPSsetalpha(DPSContext ctxt, float a);

extern void PScurrentalpha(float *alpha);

extern void DPScurrentalpha(DPSContext ctxt, float *alpha);

#endif /* PSOPENSTEP_H */
#ifdef __cplusplus
}
#endif
