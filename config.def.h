/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int gappx     = 5;                 /* gaps between windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char statussep	    = ';';	/* separator for statusbar */
static const char *fonts[]          = { "JetBrains Mono:size=10" };
static const char dmenufont[]       = "JetBrains Mono:size=10";
static const char col_red[]       = "#c03030";
static const char col_white[]       = "#a0a0a0";
static const char col_black[]       = "#202020";
static const char col_bg[]       = "#282828";
static const char col_fg[]        = "#e0e0e0";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg, col_black },
	[SchemeSel]  = { col_fg, col_red,  col_red  },
};

static const char *const autostart[] = {
	"dunst", NULL,
	"redshift", NULL,
	"picom", "-b", NULL,
	"dwm-status", NULL,
	"musicpd", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "\ueef0", "\uefab", "\ueca2", "\uef07", "\uef28", "\uefb3", "\uef58", "\uef12", "\uec44" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Thunderbird",  NULL,   NULL,       1 << 7,       0,           -1 },
	{ NULL,       NULL,     "rtorrent",   1 << 3,       0,           -1 },
	{ NULL,       NULL,     "ncmpcpp",    1 << 2,       0,           -1 },
	{ NULL,       NULL,     "newsboat",   1 << 7,       0,           -1 },
	{ "Gimp",     NULL,       NULL,       1 << 5,       0,           -1 },
	{ "KeePassXC", NULL,      NULL,       1 << 6,       0,           -1 },
	{ "Mpv",      NULL,       NULL,       1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },

};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *screencmd[] = {"screen", NULL};
static const char *wallcmd[] = {"wallpaper", NULL};
static const char *mixercmd[] = {"st", "-e", "mixertui", NULL};
static const char *volupcmd[] = {"mixer", "vol", "+3", NULL};
static const char *voldowncmd[] = {"mixer", "vol", "-3", NULL};
static const char *rsscmd[] = {"st", "-e", "newsboat", NULL};
static const char *webcmd[] = {"firefox", NULL};
static const char *torrentcmd[] = {"st", "-e", "rtorrent", NULL};
static const char *lockcmd[] = {"slock", NULL};
static const char *passcmd[] = {"keepassxc", NULL};
static const char *musiccmd[] = {"st", "-e", "ncmpcpp", NULL};
static const char *filecmd[] = {"st", "-e", "nnn", NULL};
static const char *launchercmd[] = {"tekiyou", NULL};
static const char *printscreencmd[] = {"scrot", NULL};

#include "mpdcontrol.c"

static Key keys[] = {
/* modifier                     chain key   key        function        argument */
	{ MODKEY,                       -1,         XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       -1,         XK_a,      spawn,          {.v = launchercmd } },
	{ MODKEY,                       -1,         XK_b,      togglebar,      {0} },
	{ MODKEY,                       -1,         XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       -1,         XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       -1,         XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       -1,         XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       -1,         XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       -1,         XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       -1,         XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       -1,         XK_Return, zoom,           {0} },
	{ MODKEY,                       -1,         XK_s,      spawn,          {.v = screencmd } },
	{ MODKEY,                       -1,         XK_space,  setlayout,      {0} },
	{ MODKEY,                       -1,         XK_Tab,    view,           {0} },
	{ MODKEY,                       -1,         XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       -1,         XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       -1,	    XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       -1,	    XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY,                       XK_r,       XK_Print,  spawn,          {.v = printscreencmd } },
	{ MODKEY,                       XK_r,       XK_r,      spawn,          {.v = rsscmd } },
	{ MODKEY,                       XK_r,       XK_b,      spawn,          {.v = wallcmd } },
	{ MODKEY,                       XK_r,       XK_m,      spawn,          {.v = mixercmd } },
	{ MODKEY,                       XK_r,       XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_r,       XK_w,      spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_r,       XK_t,      spawn,          {.v = torrentcmd } },
	{ MODKEY,                       XK_r,       XK_p,      spawn,          {.v = passcmd } },
	{ MODKEY,                       XK_r,       XK_u,      spawn,          {.v = musiccmd } },
	{ MODKEY,                       XK_r,       XK_f,      spawn,          {.v = filecmd } },
	{ MODKEY|ShiftMask,             -1,         XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             -1,         XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             -1,         XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             -1,         XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             -1,         XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             -1,         XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,	    XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ControlMask,           -1,         XK_Up,  spawn,          {.v = voldowncmd } },
	{ MODKEY|ControlMask,           -1,         XK_Down,  spawn,          {.v = volupcmd } },
	{ MODKEY|ControlMask,           XK_l,       XK_1,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_l,       XK_2,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_l,       XK_3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_l,       XK_4,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_l,       XK_5,      setlayout,      {.v = &layouts[4]} },
    	{ MODKEY|ControlMask,           XK_l,       XK_6,      setlayout,      {.v = &layouts[5]} },
   	{ MODKEY|ControlMask,           XK_l,       XK_7,      setlayout,      {.v = &layouts[6]} },
	TAGKEYS(                        -1,         XK_1,                      0)
	TAGKEYS(                        -1,         XK_2,                      1)
	TAGKEYS(                        -1,         XK_3,                      2)
	TAGKEYS(                        -1,         XK_4,                      3)
	TAGKEYS(                        -1,         XK_5,                      4)
	TAGKEYS(                        -1,         XK_6,                      5)
	TAGKEYS(                        -1,         XK_7,                      6)
	TAGKEYS(                        -1,         XK_8,                      7)
	TAGKEYS(                        -1,         XK_9,                      8)
	{ MODKEY|ShiftMask,             -1,         XK_q,      quit,           {0} },

	{ MODKEY,                       -1,         XK_F1,     mpdchange,      {.i = -1} },
	{ MODKEY,                       -1,         XK_F2,     mpdchange,      {.i = +1} },
	{ MODKEY,                       -1,         XK_Escape, mpdcontrol,     {0} },

	{ MODKEY,                       -1,         XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       -1,         XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       -1,         XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       -1,         XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             -1,         XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             -1,         XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             -1,         XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             -1,         XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           -1,         XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           -1,         XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           -1,         XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           -1,         XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, -1,         XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, -1,         XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, -1,         XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, -1,         XK_Right,  moveresizeedge, {.v = "R"} },

	{ MODKEY,                       -1,         XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       -1,         XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       -1,         XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       -1,         XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             -1,         XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             -1,         XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             -1,         XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             -1,         XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           -1,         XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           -1,         XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           -1,         XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           -1,         XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, -1,         XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, -1,         XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, -1,         XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, -1,         XK_Right,  moveresizeedge, {.v = "R"} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
