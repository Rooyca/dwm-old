/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int splitstatus        = 1;        /* 1 for split status items */
static const char *splitdelim        = ";";       /* Character used for separating status */
static const char *fonts[]          = { "monospace:size=9" };
static const char dmenufont[]       = "monospace:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#31748f";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *tagsel[][2] = {
   /*   fg         bg    */
  { col_gray3, col_gray1 }, /* norm */
  { col_gray4, col_cyan  }, /* sel */
  { col_cyan,  col_gray1 }, /* occ but not sel */
  { col_cyan,  col_gray3 }, /* has pinned tag */
};
/* tagging */
static const char *tags[] = { "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "firefox",  NULL,       NULL,       1 << 0,       0,           -1 },
	{ "Subl",     NULL,       NULL,       1 << 1,       0,           -1 },
	{ "obsidian", NULL,       NULL,       1 << 3,       0,           -1 },
/*	{ "st",       NULL,       NULL,       0 << 0,       1,           -1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle }, /* first entry is default */
	{ "[]=",      tile },    
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define PrintScreenDWM 0x0000ff61
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
//static const char *tmuxcmd[]  = { "st", "tmux", "a", NULL };
static const char *filecmd[]  = { "pcmanfm", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *sublcmd[]  = { "subl", NULL };
static const char *volup[]  = { "amixer", "set", "Master", "5%+", NULL };
static const char *voldown[]  = { "amixer", "set", "Master", "5%-", NULL };
static const char *volmute[]  = { "amixer", "set", "Master", "toggle", NULL };
static const char *brightup[]  = { "brightnessctl", "s", "+10%", NULL };
static const char *brightdown[]  = { "brightnessctl", "s", "10%-", NULL };
static const char *powercmd[] = {"/home/rooyca/.local/bin/pmanager", NULL};
static const char *lockcmd[] = {"physlock", "-s", "-p", " == Who is you ==", NULL};
static const char *cmdprintscreen[]  = { "scrot", "-d3", "/home/rooyca/screenshots/%Y-%m-%d-%s_$wx$h.jpg", NULL };

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,		      		 PrintScreenDWM,      spawn,          {.v = cmdprintscreen } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = sublcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockcmd } },
	//{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = tmuxcmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = powercmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_v,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_9,      quit,           {0} },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volup } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldown } },
	{ 0,                            XF86XK_AudioMute, spawn, {.v = volmute } },
	{ 0,                            XF86XK_MonBrightnessUp, spawn, {.v = brightup } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn, {.v = brightdown } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
