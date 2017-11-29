#ifndef CG1_SCREEN_H_INCLUDED
#define CG1_SCREEN_H_INCLUDED
typedef unsigned short ScreenId;
typedef struct screen_state_s
{
    ScreenId    (*id) (void); // not sure about this one
    void        (*Init)(void);
    ScreenId    (*Update) (void);
    boolean     (*Handle) (SDL_Event *event);
    void        (*Draw) (void);
    void        (*DeInit)(void);
} screen_state_t;



#endif // CG1_SCREEN_H_INCLUDED
