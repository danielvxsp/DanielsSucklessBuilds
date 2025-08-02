static unsigned int borderpx  	= 3;  /* border width */
static unsigned int snap      	= 5;  /* snap to edge pixel */
static const unsigned int gappx = 0;  /* window gap pixel */ 
static const int vertpad        = 0;  /* vertical padding of bar */
static const int sidepad        = 0;  /* horizontal padding of bar */
static int showbar            	= 1;   
static int topbar             	= 1; 
static const char *fonts[]      = { "monospace:size=11" };
static char dmenufont[]       	= "monospace:size=11";

/* 
 * This build works with Xresources and therefore pywal 
 * so if you load a wal colorscheme with the custom template 
 * the colors will apply if you press the keybind (MODKEY+r)
 * the colors defined below are fallback colors.
 * In order to apply Xresources when starting x you need to
 * add 'xrdb -merge ~/.Xresources' to .xinitrc
*/

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#005577";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#222222";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};


/* "workspaces" */
static const char *tags[] = { "1", "2", "3", "4" };
static const Rule rules[] = {
	/* class      	instance    	title       tags mask     isfloating     monitor */
	{ "Gimp",     	NULL,       	NULL,       0,            1,             -1 },
	{ "Firefox",  	NULL,       	NULL,       1 << 8,       0,             -1 },
        { "mpv",        NULL,           NULL,       0,            1,             -1 },
};

/* layout(s) */
static float mfact     		= 0.55; /* Master window size */
static int nmaster     		= 1;    /* number of clients in master area */
static int resizehints 		= 0;    /* 1 means respect size hints in tiled resizals */
static int lockfullscreen 	= 0;    /* 1 will force focus on the fullscreen window */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    
	{ "><>",      NULL },   
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,        {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,  {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,         {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,   {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL }; // Change terminal as per use case
static const char *browser[] = { "librewolf", NULL };

/* Xresources preferences to load at startup */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

/* 
 * Brightess and volume keys use brightnessctl and pamixer respectively
 * THis is for laptop so you your keyboard dosent have volume keys 
 * you can use modkey up arrow, down arrow and left to controll volume
*/

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                  key          function         argument */
        { MODKEY,                    XK_w,        spawn,           {.v = browser } },
        { MODKEY|ControlMask,        XK_Up,       spawn,           SHCMD("exec xdotool mousemove_relative -- 0 -15") },
        { MODKEY|ControlMask,        XK_Down,     spawn,           SHCMD("exec xdotool mousemove_relative 0 15") },
        { MODKEY|ControlMask,        XK_Right,    spawn,           SHCMD("exec xdotool mousemove_relative 15 0") },
        { MODKEY|ControlMask,        XK_Left,     spawn,           SHCMD("exec xdotool mousemove_relative -- -15 0") },
        { Mod1Mask,                  XK_F1,       spawn,           SHCMD("exec xdotool click 1") },
	{ Mod1Mask,                  XK_F2,       spawn,           SHCMD("exec xdotool click 3") },
	{ 0,XF86XK_AudioLowerVolume,              spawn,           SHCMD("pamixer --decrease 5 && pkill -RTMIN+1 slstatus") },
	{ 0,XF86XK_AudioRaiseVolume,              spawn,           SHCMD("pamixer --increase 5 && pkill -RTMIN+1 slstatus") },
	{ 0,XF86XK_AudioMute,                     spawn,           SHCMD("pamixer --toggle-mute && pkill -RTMIN+1 slstatus") },
	{ MODKEY,                    XK_Down,     spawn,           SHCMD("pamixer --decrease 5 && pkill -RTMIN+1 slstatus") },
	{ MODKEY,                    XK_Up,       spawn,           SHCMD("pamixer --increase 5 && pkill -RTMIN+1 slstatus") },
	{ MODKEY,                    XK_Left,     spawn,           SHCMD("pamixer --toggle-mute && pkill -RTMIN+1 slstatus") },
    { 0,XF86XK_MonBrightnessUp,               spawn,           SHCMD("brightnessctl set 10%+ && pkill -RTMIN+2 slstatus") },
 	{ 0,XF86XK_MonBrightnessDown,             spawn,           SHCMD("brightnessctl set 10%- && pkill -RTMIN+2 slstatus") },
	{ MODKEY,                    XK_r,        xrdb,            {.v = NULL } },
    { MODKEY,                    XK_minus,    setgaps,         {.i = +3 }, },
    { MODKEY,                    XK_plus,     setgaps,         {.i = -3 }, },
	{ MODKEY,                    XK_d,        spawn,           {.v = dmenucmd } },
	{ MODKEY,                    XK_Return,   spawn,           {.v = termcmd } },
	{ MODKEY,                    XK_b,        togglebar,       {0} },
	{ MODKEY,                    XK_j,        focusstack,      {.i = +1 } },
	{ MODKEY,                    XK_k,        focusstack,      {.i = -1 } },
	{ MODKEY,                    XK_i,        incnmaster,      {.i = +1 } },
	{ MODKEY|ShiftMask,          XK_d,        incnmaster,      {.i = -1 } },
	{ MODKEY,                    XK_h,        setmfact,        {.f = -0.05} },
	{ MODKEY,                    XK_l,        setmfact,        {.f = +0.05} },
	{ MODKEY|ShiftMask,          XK_Return,   zoom,            {0} },
	{ MODKEY,                    XK_Tab,      view,            {0} },
	{ MODKEY,                    XK_q,        killclient,      {0} },
	{ MODKEY,                    XK_t,        setlayout,       {.v = &layouts[0]} },
	{ MODKEY,                    XK_f,        setlayout,       {.v = &layouts[1]} },
	{ MODKEY,                    XK_m,        setlayout,       {.v = &layouts[2]} },
    { MODKEY,                    XK_space,    setlayout,       {0} },
	{ MODKEY|ShiftMask,          XK_space,    togglefloating,  {0} },
	{ MODKEY,                    XK_0,        view,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,          XK_0,        tag,             {.ui = ~0 } },
	{ MODKEY,                    XK_comma,    focusmon,        {.i = -1 } },
	{ MODKEY,                    XK_period,   focusmon,        {.i = +1 } },
	{ MODKEY|ShiftMask,          XK_comma,    tagmon,          {.i = -1 } },
	{ MODKEY|ShiftMask,          XK_period,   tagmon,          {.i = +1 } },
    { MODKEY|ShiftMask,          XK_q,        quit,            {0} },
	TAGKEYS(                     XK_1,                         0)
	TAGKEYS(                     XK_2,                         1)
	TAGKEYS(                     XK_3,                         2)
	TAGKEYS(                     XK_4,                         3)
};

/* button definitions */
static const Button buttons[] = {
	/* click            event mask   button      function        argument */
	{ ClkLtSymbol,      0,           Button1,    setlayout,      {0} },
	{ ClkLtSymbol,      0,           Button3,    setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,      0,           Button2,    zoom,           {0} },
	{ ClkStatusText,    0,           Button2,    spawn,          {.v = termcmd } },
	{ ClkClientWin,     MODKEY,      Button1,    movemouse,      {0} },
	{ ClkClientWin,     MODKEY,      Button2,    togglefloating, {0} },
	{ ClkClientWin,     MODKEY,      Button3,    resizemouse,    {0} },
	{ ClkTagBar,        0,           Button1,    view,           {0} },
	{ ClkTagBar,        0,           Button3,    toggleview,     {0} },
	{ ClkTagBar,        MODKEY,      Button1,    tag,            {0} },
	{ ClkTagBar,        MODKEY,      Button3,    toggletag,      {0} },
};

