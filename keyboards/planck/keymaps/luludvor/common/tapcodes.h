// sdothum - 2016 (c) wtfpl

// tap dance keys
enum tap_dance {
    _ASTR = 0,
    _COMM,
    _DOT
#ifdef HASKELL
    ,
    _COLN,
    _GT,
    _LT
#endif
    ,
    _PASTE,
    _PRIV,
    _PUB,
    _XPASTE,
    _CHA,
    _CHE,
    _CHO,
    _CHU,
    _CHC
};

// tap dance macros
#define TD_CHA TD(_CHA)
#define TD_CHE TD(_CHE)
#define TD_CHO TD(_CHO)
#define TD_CHU TD(_CHU)
#define TD_CHC TD(_CHC)
#define TD_ASTR TD(_ASTR)
#define TD_COMM TD(_COMM)
#define TD_DOT TD(_DOT)
#ifdef HASKELL
#    define TD_COLN TD(_COLN)
#    define TD_GT TD(_GT)
#    define TD_LT TD(_LT)
#endif
#define TD_PASTE TD(_PASTE)
#define TD_PRIV TD(_PRIV)  // compile time macro string, provided in private_string.h
#define TD_PUB TD(_PUB)    // config.h defined macro string
#define TD_XPASTE TD(_XPASTE)
