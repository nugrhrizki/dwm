/* appearance */
static const unsigned int borderpx = 2;
static const Gap default_gap       = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap     = 32;
static const unsigned int systraypinning = 0;
static const unsigned int systrayonleft  = 1;
static const unsigned int systrayspacing = 3;
static const int systraypinningfailfirst = 1;
static const int showsystray   = 1;
static const int showbar       = 1;
static const int topbar        = 1;
static const char *fonts[]     = {
	"JetBrainsMono Nerd Font:pixelsize=10:antialias=true:autohint=true",
	"JoyPixels:pixelsize=8:antialias=true:autohint=true"
};
static const char dmenufont[]  = "JetBrainsMono Nerd Font:pixelsize=12";
static const char col_gray1[]  = "#3a3a3a";
static const char col_gray2[]  = "#e4e4e4";
static const char col_gray3[]  = "#626262";
static const char col_gray4[]  = "#d0d0d0";
static const char col_accent[] = "#875f5f";
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray3 },
	[SchemeSel]  = { col_gray2, col_accent,  col_gray1  },
};

typedef struct { const char *name; const void *cmd; } Sp;

const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "120x34", "-e", "lf", NULL };
const char *spcmd3[] = {"st", "-n", "spnotes", "-g", "120x34", "-e", "notetaking", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",        spcmd2},
	{"spnotes",     spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* class      instance    title   tags mask  isfloating   monitor */
	{ "Gimp",     NULL,       NULL,   0,         1,           -1 },
	{ "Firefox",  NULL,       NULL,   1 << 8,    0,           -1 },
	{ NULL,       "spterm",   NULL,   SPTAG(0),  1,           -1 },
	{ NULL,       "spfm",     NULL,   SPTAG(1),  1,           -1 },
	{ NULL,       "spnotes",  NULL,   SPTAG(2),  1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5;
static const int nmaster     = 1;
static const int resizehints = 1;

static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "[]=",    tile },
	{ "><>",    NULL },
	{ "[M]",    monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", "5" ,"-i", "-p", " ", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent, "-sf", col_gray4, NULL };
static const char *clipmenucmd[] = { "clipmenu", "-c", "-l", "5" ,"-i", "-p", " ", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *flashfocus[]  = { "flashfocus", NULL };


static Key keys[] = {
	/* modifier              key        function        argument */
	{ MODKEY,                XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,      XK_p,      spawn,          {.v = clipmenucmd } },
	{ MODKEY,                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                XK_b,      togglebar,      {0} },
	{ MODKEY,                XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,      XK_Return, zoom,           {0} },
	{ MODKEY,                XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,      XK_c,      killclient,     {0} },
	{ MODKEY,                XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,      XK_space,  togglefloating, {0} },
	{ MODKEY,                XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,      XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,      XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,      XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                XK_s,      togglescratch,  {.ui = 0 } },
	{ MODKEY,                XK_u,      togglescratch,  {.ui = 1 } },
	{ MODKEY,                XK_n,      togglescratch,  {.ui = 2 } },
	{ MODKEY,                XK_grave,  spawn,          {.v = flashfocus } },
	{ MODKEY,                XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,      XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,      XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                 XK_1,                      0)
	TAGKEYS(                 XK_2,                      1)
	TAGKEYS(                 XK_3,                      2)
	TAGKEYS(                 XK_4,                      3)
	TAGKEYS(                 XK_5,                      4)
	TAGKEYS(                 XK_6,                      5)
	TAGKEYS(                 XK_7,                      6)
	TAGKEYS(                 XK_8,                      7)
	TAGKEYS(                 XK_9,                      8)
	{ MODKEY|ShiftMask,      XK_q,      quit,           {0} },
};

/* button definitions */
static Button buttons[] = {
	/* click         event mask  button   function        argument */
	{ ClkLtSymbol,   0,          Button1, setlayout,      {0} },
	{ ClkLtSymbol,   0,          Button3, setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,   0,          Button2, zoom,           {0} },
	{ ClkStatusText, 0,          Button2, spawn,          {.v = termcmd } },
	{ ClkClientWin,  MODKEY,     Button1, movemouse,      {0} },
	{ ClkClientWin,  MODKEY,     Button2, togglefloating, {0} },
	{ ClkClientWin,  MODKEY,     Button3, resizemouse,    {0} },
	{ ClkTagBar,     0,          Button1, view,           {0} },
	{ ClkTagBar,     0,          Button3, toggleview,     {0} },
	{ ClkTagBar,     MODKEY,     Button1, tag,            {0} },
	{ ClkTagBar,     MODKEY,     Button3, toggletag,      {0} },
};

