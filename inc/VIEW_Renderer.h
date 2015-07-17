#ifndef VIEW_RENDER_H
#define  VIEW_RENDER_H

/* Include */
/* Macro */
/* Typedef */
enum enum_view{
 	VIEW_SELF,
	VIEW_RECV,
	VIEW_MESSAGE,
	VIEW_ERROR
};
typedef enum enum_view view_t;

struct view_ascii_s {
	uint8_t min[2];
	uint8_t sec[2];
	uint8_t sec100[2];
	uint8_t adc[3];
} ;
typedef struct view_ascii_s VIEW_ascii_t;

/* Public Function Prototype */
void VIEW_Render(view_t view_code, const void *p);
void VIEW_Init(void);
void VIEW_Clear(void);
/* Private Function Prototype */
#endif
/* End of File */
