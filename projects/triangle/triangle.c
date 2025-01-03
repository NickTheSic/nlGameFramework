#include "nl_lib.h"
#include "private/nl_gl.h"

void app_specific_init(void)
{

}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    guLookAt(view, &camera,	&up, &look);
	GX_SetViewport(0,0,screenMode->fbWidth,screenMode->efbHeight,0,1);
	GX_InvVtxCache();
	GX_InvalidateTexAll();
	update_screen(view);
	PAD_Read(pads);
}

void app_specific_cleanup(void)
{
    
}

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>

static vu8	readyForCopy;

short	vertices[] ATTRIBUTE_ALIGN(32) = {
	0, 15, 0,
	-15, -15, 0,
	15,	-15, 0};

unsigned char colors[]	ATTRIBUTE_ALIGN(32)	= {
	255, 0,	0, 255,		// red
	0, 255,	0, 255,		// green
	0, 0, 255, 255};	// blue

void update_screen(Mtx viewMatrix);
static void	copy_buffers(u32 unused);

int	local_main(void)
{
	Mtx	view;
	Mtx44	projection;
	PADStatus pads[4];

	VIDEO_SetPostRetraceCallback(copy_buffers);

	guVector camera =	{0.0F, 0.0F, 0.0F};
	guVector up =	{0.0F, 1.0F, 0.0F};
	guVector look	= {0.0F, 0.0F, -1.0F};

	guPerspective(projection, 60, 1.33F, 10.0F,	300.0F);
	GX_LoadProjectionMtx(projection, GX_PERSPECTIVE);

	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_INDEX8);
	GX_SetVtxDesc(GX_VA_CLR0, GX_INDEX8);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS,	GX_POS_XYZ,	GX_S16,	0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8,	0);
	GX_SetArray(GX_VA_POS, vertices, 3*sizeof(s16));
	GX_SetArray(GX_VA_CLR0,	colors,	4*sizeof(u8));
	GX_SetNumChans(1);
	GX_SetNumTexGens(0);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}

void update_screen(	Mtx	viewMatrix )
{
	Mtx	modelView;
	
	guMtxIdentity(modelView);
	guMtxTransApply(modelView, modelView, 0.0F,	0.0F, -50.0F);
	guMtxConcat(viewMatrix,modelView,modelView);
	
	GX_LoadPosMtxImm(modelView,	GX_PNMTX0);

	GX_Begin(GX_TRIANGLES, GX_VTXFMT0, 3);

	GX_Position1x8(0);
	GX_Color1x8(0);
	GX_Position1x8(1);
	GX_Color1x8(1);
	GX_Position1x8(2);
	GX_Color1x8(2);
	
	GX_End();
	GX_DrawDone();
	readyForCopy = GX_TRUE;

	VIDEO_WaitVSync();
	return;
}

static void	copy_buffers(u32 count __attribute__ ((unused)))
{
	if (readyForCopy==GX_TRUE) {
		GX_SetZMode(GX_TRUE, GX_LEQUAL,	GX_TRUE);
		GX_SetColorUpdate(GX_TRUE);
		GX_CopyDisp(frameBuffer,GX_TRUE);
		GX_Flush();
		readyForCopy = GX_FALSE;
	}
}
