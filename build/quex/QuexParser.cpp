#include "QuexParser.hpp"
#include <quex/code_base/analyzer/C-adaptions.h>
QUEX_NAMESPACE_MAIN_OPEN
/* Global */QUEX_NAME(Mode)  QUEX_NAME(Program);
/* Global */QUEX_NAME(Mode)  QUEX_NAME(Quotation);
#ifndef __QUEX_INDICATOR_DUMPED_TOKEN_ID_DEFINED
    static QUEX_TYPE_TOKEN_ID    QUEX_NAME_TOKEN(DumpedTokenIdObject);
#endif
#define self  (*(QUEX_TYPE_DERIVED_ANALYZER*)me)
#define __self_result_token_id    QUEX_NAME_TOKEN(DumpedTokenIdObject)

void
QUEX_NAME(Program_on_entry)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* FromMode) {
    (void)me;
    (void)FromMode;
#   ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
    QUEX_NAME(Program).has_entry_from(FromMode);
#   endif

}

void
QUEX_NAME(Program_on_exit)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* ToMode)  {
    (void)me;
    (void)ToMode;
#   ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
    QUEX_NAME(Program).has_exit_to(ToMode);
#   endif

}

#if defined(QUEX_OPTION_INDENTATION_TRIGGER) 
void
QUEX_NAME(Program_on_indentation)(QUEX_TYPE_ANALYZER*    me, 
                                        QUEX_TYPE_INDENTATION  Indentation, 
                                        QUEX_TYPE_CHARACTER*   Begin) {
    (void)me;
    (void)Indentation;
    (void)Begin;

#   if defined(QUEX_OPTION_TOKEN_POLICY_SINGLE)
#      define __QUEX_RETURN return __self_result_token_id
#   else
#      define __QUEX_RETURN return
#   endif
#   define RETURN    __QUEX_RETURN
#   define CONTINUE  __QUEX_RETURN
#   define Lexeme    LexemeBegin
#   define LexemeEnd (me->buffer._input_p)

    QUEX_NAME(IndentationStack)*  stack = &me->counter._indentation_stack;
    QUEX_TYPE_INDENTATION*        start = 0x0;

    __quex_assert((long)Indentation >= 0);

    if( Indentation > *(stack->back) ) {
        ++(stack->back);
        if( stack->back == stack->memory_end ) QUEX_ERROR_EXIT("Indentation stack overflow.");
        *(stack->back) = Indentation;
#   line 70 "src/Parser/QuexParser.qx"
    self_send(TokenBlockBegin);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 65 "QuexParser.cpp"

        __QUEX_RETURN;
    }
    else if( Indentation == *(stack->back) ) {
#   line 72 "src/Parser/QuexParser.qx"
    self_send(TokenStatementSeparator);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 74 "QuexParser.cpp"

    }
    else  {
        start = stack->back;
        --(stack->back);
#       if ! defined(QUEX_OPTION_TOKEN_REPETITION_SUPPORT)
#       define First true
#   line 71 "src/Parser/QuexParser.qx"
    self_send(TokenBlockEnd);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 86 "QuexParser.cpp"

#       undef  First
#       endif
        while( Indentation < *(stack->back) ) {
            --(stack->back);
#           if ! defined(QUEX_OPTION_TOKEN_REPETITION_SUPPORT)
#           define First false
#   line 71 "src/Parser/QuexParser.qx"
    self_send(TokenBlockEnd);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 98 "QuexParser.cpp"

#           undef  First
#           endif
        }

        if( Indentation == *(stack->back) ) { 
            /* 'Landing' must happen on indentation border. */
#           define ClosedN (start - stack->back)

#           undef  ClosedN
        } else { 
#            define IndentationStackSize ((size_t)(1 + start - stack->front))
#            define IndentationStack(I)  (*(stack->front + I))
#            define IndentationUpper     (*(stack->back))
#            define IndentationLower     ((stack->back == stack->front) ? *(stack->front) : *(stack->back - 1))
#            define ClosedN              (start - stack->back)
#   line 92 "src/Parser/QuexParser.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TokenFailure);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 120 "QuexParser.cpp"

#            undef IndentationStackSize 
#            undef IndentationStack  
#            undef IndentationUpper     
#            undef IndentationLower     
#            undef ClosedN
        }
    }
    __QUEX_RETURN;

#   undef Lexeme    
#   undef LexemeEnd 

}
#endif

#ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
bool
QUEX_NAME(Program_has_base)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return false;
}
bool
QUEX_NAME(Program_has_entry_from)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return true; /* default */
}
bool
QUEX_NAME(Program_has_exit_to)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return false;
}
#endif    

void
QUEX_NAME(Quotation_on_entry)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* FromMode) {
    (void)me;
    (void)FromMode;
#   ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
    QUEX_NAME(Quotation).has_entry_from(FromMode);
#   endif

#   line 102 "src/Parser/QuexParser.qx"

		self.quote_depth = 1;
		self_accumulator_clear();
	

#   line 169 "QuexParser.cpp"
}

void
QUEX_NAME(Quotation_on_exit)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* ToMode)  {
    (void)me;
    (void)ToMode;
#   ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
    QUEX_NAME(Quotation).has_exit_to(ToMode);
#   endif

#   line 106 "src/Parser/QuexParser.qx"

		self_accumulator_flush(TokenQuotation);
	

#   line 185 "QuexParser.cpp"

}

#if defined(QUEX_OPTION_INDENTATION_TRIGGER) 
void
QUEX_NAME(Quotation_on_indentation)(QUEX_TYPE_ANALYZER*    me, 
                                        QUEX_TYPE_INDENTATION  Indentation, 
                                        QUEX_TYPE_CHARACTER*   Begin) {
    (void)me;
    (void)Indentation;
    (void)Begin;
    return;
}
#endif

#ifdef QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
bool
QUEX_NAME(Quotation_has_base)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return false;
}
bool
QUEX_NAME(Quotation_has_entry_from)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return true; /* default */
}
bool
QUEX_NAME(Quotation_has_exit_to)(const QUEX_NAME(Mode)* Mode) {
    (void)Mode;
    return false;
}
#endif    
#undef self
#undef __self_result_token_id
QUEX_NAMESPACE_MAIN_CLOSE

/* #include "QuexParser.hpp"*/
QUEX_NAMESPACE_MAIN_OPEN
QUEX_TYPE_CHARACTER  QUEX_LEXEME_NULL_IN_ITS_NAMESPACE = (QUEX_TYPE_CHARACTER)0;
#ifdef      __QUEX_COUNT_VOID
#   undef   __QUEX_COUNT_VOID
#endif
#ifdef      __QUEX_OPTION_COUNTER
#    define __QUEX_COUNT_VOID(ME, BEGIN, END) \
            do {                              \
                QUEX_NAME(Program_counter)((ME), (BEGIN), (END));     \
                __quex_debug_counter();       \
            } while(0)
#else
#    define __QUEX_COUNT_VOID(ME, BEGIN, END) /* empty */
#endif
#ifdef __QUEX_OPTION_COUNTER
static void
QUEX_NAME(Program_counter)(QUEX_TYPE_ANALYZER* me, QUEX_TYPE_CHARACTER* LexemeBegin, QUEX_TYPE_CHARACTER* LexemeEnd)
{
#   define self (*me)
    QUEX_TYPE_CHARACTER* iterator    = LexemeBegin;
#   if defined(QUEX_OPTION_COLUMN_NUMBER_COUNTING)
    const QUEX_TYPE_CHARACTER* reference_p = LexemeBegin;
#   endif
__QUEX_IF_COUNT_COLUMNS(reference_p = iterator);
    __QUEX_IF_COUNT_SHIFT_VALUES();

    __quex_assert(LexemeBegin <= LexemeEnd);
    for(iterator=LexemeBegin; iterator < LexemeEnd; ) {
        if( (*(iterator)) < 0x9 ) {
                            ++(((iterator)));
            continue;/* [\0, '\b'] */

        } else if( (*(iterator)) == 0x9 ) {
                    __QUEX_IF_COUNT_COLUMNS_ADD((size_t)(((iterator) - reference_p)));
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end &= ~ ((size_t)0x3));
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);
        __QUEX_IF_COUNT_COLUMNS(reference_p = (iterator) + 1);
                ++(((iterator)));
            continue;/* '\t' */

        } else if( (*(iterator)) == 0xA ) {
            __QUEX_IF_COUNT_LINES_ADD((size_t)1);
        __QUEX_IF_COUNT_COLUMNS_SET((size_t)1);
        __QUEX_IF_COUNT_COLUMNS(reference_p = (iterator) + 1);
                ++(((iterator)));
            continue;/* '\n' */

        } else {
                            ++(((iterator)));
            continue;/* ['\v', <4294967295>] */

        }

    }
    __quex_assert(iterator == LexemeEnd); /* Otherwise, lexeme violates codec character boundaries. */
__QUEX_IF_COUNT_COLUMNS_ADD((size_t)((iterator - reference_p)));
   return;
#  undef self
}
#endif /* __QUEX_OPTION_COUNTER */
#include <quex/code_base/analyzer/member/basic>
#include <quex/code_base/buffer/Buffer>
#ifdef QUEX_OPTION_TOKEN_POLICY_QUEUE
#   include <quex/code_base/token/TokenQueue>
#endif

#ifdef    CONTINUE
#   undef CONTINUE
#endif
#define   CONTINUE goto __REENTRY_PREPARATION; 

#ifdef    RETURN
#   undef RETURN
#endif

#define RETURN    __QUEX_PURE_RETURN;
#include <quex/code_base/temporary_macros_on>

__QUEX_TYPE_ANALYZER_RETURN_VALUE  
QUEX_NAME(Program_analyzer_function)(QUEX_TYPE_ANALYZER* me) 
{
    /* NOTE: Different modes correspond to different analyzer functions. The 
     *       analyzer functions are all located inside the main class as static
     *       functions. That means, they are something like 'globals'. They 
     *       receive a pointer to the lexical analyzer, since static members do
     *       not have access to the 'this' pointer.                          */
#   if defined(QUEX_OPTION_TOKEN_POLICY_SINGLE)
    register QUEX_TYPE_TOKEN_ID __self_result_token_id 
           = (QUEX_TYPE_TOKEN_ID)__QUEX_SETTING_TOKEN_ID_UNINITIALIZED;
#   endif
#   ifdef     self
#       undef self
#   endif
#   define self (*((QUEX_TYPE_ANALYZER*)me))
    QUEX_TYPE_CHARACTER_POSITION   position[1]                    = { 0};
    const QUEX_TYPE_GOTO_LABEL     (template_479_target_1[2])     = { QUEX_LABEL(479), QUEX_LABEL(485)  };
    const QUEX_TYPE_GOTO_LABEL     (template_479_target_0[2])     = { QUEX_LABEL(497), QUEX_LABEL(479)  };
    QUEX_TYPE_CHARACTER_POSITION   reference_p                    = (QUEX_TYPE_CHARACTER_POSITION)0x0;
    ptrdiff_t                      state_key                      = (ptrdiff_t)0;
    const QUEX_TYPE_GOTO_LABEL     (template_483_target_0[3])     = { QUEX_LABEL(494), QUEX_LABEL(483), QUEX_LABEL(494)  };
    const QUEX_TYPE_GOTO_LABEL     (template_483_target_1[3])     = { QUEX_LABEL(495), QUEX_LABEL(496), QUEX_LABEL(496)  };
    const QUEX_TYPE_GOTO_LABEL     (template_483_target_2[3])     = { QUEX_LABEL(483), QUEX_LABEL(496), QUEX_LABEL(496)  };
    QUEX_TYPE_GOTO_LABEL           target_state_else_index        = QUEX_GOTO_LABEL_VOID;
    const size_t                   PositionRegisterN              = (size_t)1;
    QUEX_TYPE_CHARACTER            input                          = (QUEX_TYPE_CHARACTER)(0x00);
    const QUEX_TYPE_GOTO_LABEL     (template_482_target_3[4])     = { QUEX_LABEL(493), QUEX_LABEL(493), QUEX_LABEL(493), QUEX_LABEL(492)  };
    const QUEX_TYPE_GOTO_LABEL     (template_482_target_2[4])     = { QUEX_LABEL(482), QUEX_LABEL(482), QUEX_LABEL(486), QUEX_LABEL(492)  };
    const QUEX_TYPE_GOTO_LABEL     (template_482_target_1[4])     = { QUEX_LABEL(492), QUEX_LABEL(492), QUEX_LABEL(488), QUEX_LABEL(482)  };
    const QUEX_TYPE_GOTO_LABEL     (template_482_target_0[4])     = { QUEX_LABEL(491), QUEX_LABEL(492), QUEX_LABEL(491), QUEX_LABEL(492)  };
    QUEX_TYPE_GOTO_LABEL           target_state_index             = QUEX_GOTO_LABEL_VOID;
#   ifndef QUEX_OPTION_COMPUTED_GOTOS
#   endif /* QUEX_OPTION_COMPUTED_GOTOS */
#   define Program      (QUEX_NAME(Program))
#   define Quotation    (QUEX_NAME(Quotation))

    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. Post context position's live cycle:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, then it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context), then the post context position is used
     *       to reset the input position.                                              */
#   if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE) \
       || defined(QUEX_OPTION_ASSERTS)
    me->DEBUG_analyzer_function_at_entry = me->current_analyzer_function;
#   endif
__REENTRY:
    me->buffer._lexeme_start_p = me->buffer._input_p;
    QUEX_LEXEME_TERMINATING_ZERO_UNDO(&me->buffer);
    /* BEGIN: STATE MACHINE
     * init-state = 455L
     * 00455 (343, 339), (344, 220), (345, 224), (346, 228), (347, 232), (348, 236), (349, 240), (350, 244), (351, 248), (352, 252), (353, 256), (354, 260), (355, 268), (356, 276), (357, 280), (358, 284)
     *      == '\t', ['\v', '\f'], ' ', ' ', ' ', '᠎', [' ', ' '], ' ', ' ', ' ', '　' ==> 00465
     *      == '\n', '\r', [\28, \30], '', ' ' ==> 00461
     *      == ['!', '''], ['*', '/'], [':', '@'], ['[', '^'], '`', ['{', '~'], ['¡', '§'], '©', ['«', '¬'], '®', ['°', '±'], '¶', '»', '¿', '×', '÷', ['‐', '‛'], ['„', '‧'], ['‰', '‾'], ['⁁', '⁓'], ['⁕', '⁞'], ['←', '↥'], ['↧', '∳'], ['∶', '≓'], ['≕', '⊡'], ['⊣', '⊧'], ['⊩', '⑟'], ['─', '❵'], ['➔', '⯿'], ['⸀', '⹿'], ['、', '〃'], ['〈', '〠'], '〰', ['﴾', '﴿'], ['﹅', '﹆'] ==> 00462
     *      == '(' ==> 00463
     *      == ')' ==> 00467
     *      == ['0', '9'] ==> 00458
     *      == ['A', 'Z'] ==> 00466
     *      == ['a', 'z'], 'ª', 'µ', 'º', ['À', 'Ö'], ['Ø', 'ö'], ['ø', 'ý'], ['Ā', 'ˁ'], ['ˆ', 'ˑ'], ['ˠ', 'ˤ'], 'ˬ', 'ˮ', ['Ͱ', 'ʹ'], ['Ͷ', 'ͷ'], ['ͻ', 'ͽ'], 'Ά', ['Έ', 'Ί'], 'Ό', ['Ύ', 'Ρ'], ['Σ', 'ϵ'], ['Ϸ', 'ҁ'], ['Ҋ', 'ԧ'], ['Ա', 'Ֆ'], 'ՙ', ['ա', 'և'], ['א', 'ת'], ['װ', 'ײ'], ['ؠ', 'ي'], ['ٮ', 'ٯ'], ['ٱ', 'ۓ'], 'ە', ['ۥ', 'ۦ'], ['ۮ', 'ۯ'], ['ۺ', 'ۼ'], 'ۿ', 'ܐ', ['ܒ', 'ܯ'], ['ݍ', 'ޥ'], 'ޱ', ['ߊ', 'ߪ'], ['ߴ', 'ߵ'], 'ߺ', ['ࠀ', 'ࠕ'], 'ࠚ', 'ࠤ', 'ࠨ', ['ࡀ', 'ࡘ'], ['ऄ', 'ह'], 'ऽ', 'ॐ', ['क़', 'ॡ'], ['ॱ', 'ॷ'], ['ॹ', 'ॿ'], ['অ', 'ঌ'], ['এ', 'ঐ'], ['ও', 'ন'], ['প', 'র'], 'ল', ['শ', 'হ'], 'ঽ', 'ৎ', ['ড়', 'ঢ়'], ['য়', 'ৡ'], ['ৰ', 'ৱ'], ['ਅ', 'ਊ'], ['ਏ', 'ਐ'], ['ਓ', 'ਨ'], ['ਪ', 'ਰ'], ['ਲ', 'ਲ਼'], ['ਵ', 'ਸ਼'], ['ਸ', 'ਹ'], ['ਖ਼', 'ੜ'], 'ਫ਼', ['ੲ', 'ੴ'], ['અ', 'ઍ'], ['એ', 'ઑ'], ['ઓ', 'ન'], ['પ', 'ર'], ['લ', 'ળ'], ['વ', 'હ'], 'ઽ', 'ૐ', ['ૠ', 'ૡ'], ['ଅ', 'ଌ'], ['ଏ', 'ଐ'], ['ଓ', 'ନ'], ['ପ', 'ର'], ['ଲ', 'ଳ'], ['ଵ', 'ହ'], 'ଽ', ['ଡ଼', 'ଢ଼'], ['ୟ', 'ୡ'], 'ୱ', 'ஃ', ['அ', 'ஊ'], ['எ', 'ஐ'], ['ஒ', 'க'], ['ங', 'ச'], 'ஜ', ['ஞ', 'ட'], ['ண', 'த'], ['ந', 'ப'], ['ம', 'ஹ'], 'ௐ', ['అ', 'ఌ'], ['ఎ', 'ఐ'], ['ఒ', 'న'], ['ప', 'ళ'], ['వ', 'హ'], 'ఽ', ['ౘ', 'ౙ'], ['ౠ', 'ౡ'], ['ಅ', 'ಌ'], ['ಎ', 'ಐ'], ['ಒ', 'ನ'], ['ಪ', 'ಳ'], ['ವ', 'ಹ'], 'ಽ', 'ೞ', ['ೠ', 'ೡ'], ['ೱ', 'ೲ'], ['അ', 'ഌ'], ['എ', 'ഐ'], ['ഒ', 'ഺ'], 'ഽ', 'ൎ', ['ൠ', 'ൡ'], ['ൺ', 'ൿ'], ['අ', 'ඖ'], ['ක', 'න'], ['ඳ', 'ර'], 'ල', ['ව', 'ෆ'], ['ก', 'ะ'], 'า', ['เ', 'ๆ'], ['ກ', 'ຂ'], 'ຄ', ['ງ', 'ຈ'], 'ຊ', 'ຍ', ['ດ', 'ທ'], ['ນ', 'ຟ'], ['ມ', 'ຣ'], 'ລ', 'ວ', ['ສ', 'ຫ'], ['ອ', 'ະ'], 'າ', 'ຽ', ['ເ', 'ໄ'], 'ໆ', ['ໜ', 'ໝ'], 'ༀ', ['ཀ', 'ཇ'], ['ཉ', 'ཬ'], ['ྈ', 'ྌ'], ['က', 'ဪ'], 'ဿ', ['ၐ', 'ၕ'], ['ၚ', 'ၝ'], 'ၡ', ['ၥ', 'ၦ'], ['ၮ', 'ၰ'], ['ၵ', 'ႁ'], 'ႎ', ['Ⴀ', 'Ⴥ'], ['ა', 'ჺ'], 'ჼ', ['ᄀ', 'ቈ'], ['ቊ', 'ቍ'], ['ቐ', 'ቖ'], 'ቘ', ['ቚ', 'ቝ'], ['በ', 'ኈ'], ['ኊ', 'ኍ'], ['ነ', 'ኰ'], ['ኲ', 'ኵ'], ['ኸ', 'ኾ'], 'ዀ', ['ዂ', 'ዅ'], ['ወ', 'ዖ'], ['ዘ', 'ጐ'], ['ጒ', 'ጕ'], ['ጘ', 'ፚ'], ['ᎀ', 'ᎏ'], ['Ꭰ', 'Ᏼ'], ['ᐁ', 'ᙬ'], ['ᙯ', 'ᙿ'], ['ᚁ', 'ᚚ'], ['ᚠ', 'ᛪ'], ['ᛮ', 'ᛰ'], ['ᜀ', 'ᜌ'], ['ᜎ', 'ᜑ'], ['ᜠ', 'ᜱ'], ['ᝀ', 'ᝑ'], ['ᝠ', 'ᝬ'], ['ᝮ', 'ᝰ'], ['ក', 'ឳ'], 'ៗ', 'ៜ', ['ᠠ', 'ᡷ'], ['ᢀ', 'ᢨ'], 'ᢪ', ['ᢰ', 'ᣵ'], ['ᤀ', 'ᤜ'], ['ᥐ', 'ᥭ'], ['ᥰ', 'ᥴ'], ['ᦀ', 'ᦫ'], ['ᧁ', 'ᧇ'], ['ᨀ', 'ᨖ'], ['ᨠ', 'ᩔ'], 'ᪧ', ['ᬅ', 'ᬳ'], ['ᭅ', 'ᭋ'], ['ᮃ', 'ᮠ'], ['ᮮ', 'ᮯ'], ['ᯀ', 'ᯥ'], ['ᰀ', 'ᰣ'], ['ᱍ', 'ᱏ'], ['ᱚ', 'ᱽ'], ['ᳩ', 'ᳬ'], ['ᳮ', 'ᳱ'], ['ᴀ', 'ᶿ'], ['Ḁ', 'ἕ'], ['Ἐ', 'Ἕ'], ['ἠ', 'ὅ'], ['Ὀ', 'Ὅ'], ['ὐ', 'ὗ'], 'Ὑ', 'Ὓ', 'Ὕ', ['Ὗ', 'ώ'], ['ᾀ', 'ᾴ'], ['ᾶ', 'ᾼ'], 'ι', ['ῂ', 'ῄ'], ['ῆ', 'ῌ'], ['ῐ', 'ΐ'], ['ῖ', 'Ί'], ['ῠ', 'Ῥ'], ['ῲ', 'ῴ'], ['ῶ', 'ῼ'], 'ⁱ', 'ⁿ', ['ₐ', 'ₜ'], 'ℂ', 'ℇ', ['ℊ', 'ℓ'], 'ℕ', ['℘', 'ℝ'], 'ℤ', 'Ω', 'ℨ', ['K', 'ℹ'], ['ℼ', 'ℿ'], ['ⅅ', 'ⅉ'], 'ⅎ', ['Ⅰ', 'ↈ'], ['Ⰰ', 'Ⱞ'], ['ⰰ', 'ⱞ'], ['Ⱡ', 'ⳤ'], ['Ⳬ', 'ⳮ'], ['ⴀ', 'ⴥ'], ['ⴰ', 'ⵥ'], 'ⵯ', ['ⶀ', 'ⶖ'], ['ⶠ', 'ⶦ'], ['ⶨ', 'ⶮ'], ['ⶰ', 'ⶶ'], ['ⶸ', 'ⶾ'], ['ⷀ', 'ⷆ'], ['ⷈ', 'ⷎ'], ['ⷐ', 'ⷖ'], ['ⷘ', 'ⷞ'], ['々', '〇'], ['〡', '〩'], ['〱', '〵'], ['〸', '〼'], ['ぁ', 'ゖ'], ['ゝ', 'ゟ'], ['ァ', 'ヺ'], ['ー', 'ヿ'], ['ㄅ', 'ㄭ'], ['ㄱ', 'ㆎ'], ['ㆠ', 'ㆺ'], ['ㇰ', 'ㇿ'], ['㐀', '䶵'], ['一', '鿋'], ['ꀀ', 'ꒌ'], ['ꓐ', 'ꓽ'], ['ꔀ', 'ꘌ'], ['ꘐ', 'ꘟ'], ['ꘪ', 'ꘫ'], ['Ꙁ', 'ꙮ'], ['ꙿ', 'ꚗ'], ['ꚠ', 'ꛯ'], ['ꜗ', 'ꜟ'], ['Ꜣ', 'ꞈ'], ['Ꞌ', 'ꞎ'], ['Ꞑ', 'ꞑ'], ['Ꞡ', 'ꞩ'], ['ꟺ', 'ꠁ'], ['ꠃ', 'ꠅ'], ['ꠇ', 'ꠊ'], ['ꠌ', 'ꠢ'], ['ꡀ', 'ꡳ'], ['ꢂ', 'ꢳ'], ['ꣲ', 'ꣷ'], 'ꣻ', ['ꤊ', 'ꤥ'], ['ꤰ', 'ꥆ'], ['ꥠ', 'ꥼ'], ['ꦄ', 'ꦲ'], 'ꧏ', ['ꨀ', 'ꨨ'], ['ꩀ', 'ꩂ'], ['ꩄ', 'ꩋ'], ['ꩠ', 'ꩶ'], 'ꩺ', ['ꪀ', 'ꪯ'], 'ꪱ', ['ꪵ', 'ꪶ'], ['ꪹ', 'ꪽ'], 'ꫀ', 'ꫂ', ['ꫛ', 'ꫝ'], ['ꬁ', 'ꬆ'], ['ꬉ', 'ꬎ'], ['ꬑ', 'ꬖ'], ['ꬠ', 'ꬦ'], ['ꬨ', 'ꬮ'], ['ꯀ', 'ꯢ'], ['가', '힣'], ['ힰ', 'ퟆ'], ['ퟋ', 'ퟻ'], ['豈', '鶴'], ['侮', '舘'], ['並', '龎'], ['ﬀ', 'ﬆ'], ['ﬓ', 'ﬗ'], 'יִ', ['ײַ', 'ﬨ'], ['שׁ', 'זּ'], ['טּ', 'לּ'], 'מּ', ['נּ', 'סּ'], ['ףּ', 'פּ'], ['צּ', 'ﮱ'], ['ﯓ', 'ﱝ'], ['ﱤ', 'ﴽ'], ['ﵐ', 'ﶏ'], ['ﶒ', 'ﷇ'], ['ﷰ', 'ﷹ'], 'ﹱ', 'ﹳ', 'ﹷ', 'ﹹ', 'ﹻ', 'ﹽ', ['ﹿ', 'ﻼ'], ['Ａ', 'Ｚ'], ['ａ', 'ｚ'], ['ｦ', 'ﾝ'], ['ﾠ', 'ﾾ'], ['ￂ', 'ￇ'], ['ￊ', 'ￏ'], ['ￒ', 'ￗ'], ['ￚ', 'ￜ'], ['𐀀', '𐀋'], ['𐀍', '𐀦'], ['𐀨', '𐀺'], ['𐀼', '𐀽'], ['𐀿', '𐁍'], ['𐁐', '𐁝'], ['𐂀', '𐃺'], ['𐅀', '𐅴'], ['𐊀', '𐊜'], ['𐊠', '𐋐'], ['𐌀', '𐌞'], ['𐌰', '𐍊'], ['𐎀', '𐎝'], ['𐎠', '𐏃'], ['𐏈', '𐏏'], ['𐏑', '𐏕'], ['𐐀', '𐒝'], ['𐠀', '𐠅'], '𐠈', ['𐠊', '𐠵'], ['𐠷', '𐠸'], '𐠼', ['𐠿', '𐡕'], ['𐤀', '𐤕'], ['𐤠', '𐤹'], '𐨀', ['𐨐', '𐨓'], ['𐨕', '𐨗'], ['𐨙', '𐨳'], ['𐩠', '𐩼'], ['𐬀', '𐬵'], ['𐭀', '𐭕'], ['𐭠', '𐭲'], ['𐰀', '𐱈'], ['𑀃', '𑀷'], ['𑂃', '𑂯'], ['𒀀', '𒍮'], ['𒐀', '𒑢'], ['𓀀', '𓐮'], ['𖠀', '𖨸'], ['𛀀', '𛀁'], ['𝐀', '𝑔'], ['𝑖', '𝒜'], ['𝒞', '𝒟'], '𝒢', ['𝒥', '𝒦'], ['𝒩', '𝒬'], ['𝒮', '𝒹'], '𝒻', ['𝒽', '𝓃'], ['𝓅', '𝔅'], ['𝔇', '𝔊'], ['𝔍', '𝔔'], ['𝔖', '𝔜'], ['𝔞', '𝔹'], ['𝔻', '𝔾'], ['𝕀', '𝕄'], '𝕆', ['𝕊', '𝕐'], ['𝕒', '𝚥'], ['𝚨', '𝛀'], ['𝛂', '𝛚'], ['𝛜', '𝛺'], ['𝛼', '𝜔'], ['𝜖', '𝜴'], ['𝜶', '𝝎'], ['𝝐', '𝝮'], ['𝝰', '𝞈'], ['𝞊', '𝞨'], ['𝞪', '𝟂'], ['𝟄', '𝟋'], ['𠀀', '𪛖'], ['𪜀', '𫜴'], ['𫝀', '𫠝'], ['丽', '𪘀'] ==> 00471
     *      == '·' ==> 00460
     *      == '“' ==> 00464
     *      == '”' ==> 00472
     *      == '↦' ==> 00468
     *      == '∴' ==> 00456
     *      == '∵' ==> 00459
     *      == '≔' ==> 00469
     *      == '⊢' ==> 00470
     *      == '⊨' ==> 00457
     *     
     * 00465 (344, 221, A)
     *     
     * 00461 (343, 340, A)
     *      == '\t' ==> 00477
     *      == '\n', '\r', [\28, \30], '', ' ' ==> 00461
     *     
     * 00477 (343, 341)
     *      == '\t' ==> 00477
     *      == '\n', '\r', [\28, \30], '', ' ' ==> 00461
     *     
     * 00462 (358, 285, A)
     *     
     * 00463 (351, 249, A), (358, 285, A)
     *     
     * 00467 (352, 253, A), (358, 285, A)
     *     
     * 00458 (355, 269, A)
     *      == '.' ==> 00474
     *      == ['0', '9'], ['A', 'Z'], ' ' ==> 00458
     *      == ['₀', '₉'] ==> 00473
     *     
     * 00474 (355, 270, A)
     *      == ['0', '9'], ['A', 'Z'], ' ' ==> 00474
     *      == ['₀', '₉'] ==> 00473
     *     
     * 00473 (355, 271, A)
     *      == ['²', '³'], '¹', '⁰', ['⁴', '⁹'] ==> 00476
     *      == ['⁺', '⁻'] ==> 00475
     *      == ['₀', '₉'] ==> 00473
     *     
     * 00476 (355, 272, A)
     *      == ['²', '³'], '¹', '⁰', ['⁴', '⁹'] ==> 00476
     *     
     * 00475 (355, 273)
     *      == ['²', '³'], '¹', '⁰', ['⁴', '⁹'] ==> 00476
     *     
     * 00466 (354, 261, A), (355, 269, A)
     *      == '.' ==> 00474
     *      == ['0', '9'], ['A', 'Z'] ==> 00466
     *      == '_', ['a', 'z'], 'ª', 'µ', '·', 'º', ['À', 'Ö'], ['Ø', 'ö'], ['ø', 'ý'], ['Ā', 'ˁ'], ['ˆ', 'ˑ'], ['ˠ', 'ˤ'], 'ˬ', 'ˮ', ['̀', 'ʹ'], ['Ͷ', 'ͷ'], ['ͻ', 'ͽ'], ['Ά', 'Ί'], 'Ό', ['Ύ', 'Ρ'], ['Σ', 'ϵ'], ['Ϸ', 'ҁ'], ['҃', '҇'], ['Ҋ', 'ԧ'], ['Ա', 'Ֆ'], 'ՙ', ['ա', 'և'], ['֑', 'ֽ'], 'ֿ', ['ׁ', 'ׂ'], ['ׄ', 'ׅ'], 'ׇ', ['א', 'ת'], ['װ', 'ײ'], ['ؐ', 'ؚ'], ['ؠ', '٩'], ['ٮ', 'ۓ'], ['ە', 'ۜ'], ['۟', 'ۨ'], ['۪', 'ۼ'], 'ۿ', ['ܐ', '݊'], ['ݍ', 'ޱ'], ['߀', 'ߵ'], 'ߺ', ['ࠀ', '࠭'], ['ࡀ', '࡛'], ['ऀ', 'ॣ'], ['०', '९'], ['ॱ', 'ॷ'], ['ॹ', 'ॿ'], ['ঁ', 'ঃ'], ['অ', 'ঌ'], ['এ', 'ঐ'], ['ও', 'ন'], ['প', 'র'], 'ল', ['শ', 'হ'], ['়', 'ৄ'], ['ে', 'ৈ'], ['ো', 'ৎ'], 'ৗ', ['ড়', 'ঢ়'], ['য়', 'ৣ'], ['০', 'ৱ'], ['ਁ', 'ਃ'], ['ਅ', 'ਊ'], ['ਏ', 'ਐ'], ['ਓ', 'ਨ'], ['ਪ', 'ਰ'], ['ਲ', 'ਲ਼'], ['ਵ', 'ਸ਼'], ['ਸ', 'ਹ'], '਼', ['ਾ', 'ੂ'], ['ੇ', 'ੈ'], ['ੋ', '੍'], 'ੑ', ['ਖ਼', 'ੜ'], 'ਫ਼', ['੦', 'ੵ'], ['ઁ', 'ઃ'], ['અ', 'ઍ'], ['એ', 'ઑ'], ['ઓ', 'ન'], ['પ', 'ર'], ['લ', 'ળ'], ['વ', 'હ'], ['઼', 'ૅ'], ['ે', 'ૉ'], ['ો', '્'], 'ૐ', ['ૠ', 'ૣ'], ['૦', '૯'], ['ଁ', 'ଃ'], ['ଅ', 'ଌ'], ['ଏ', 'ଐ'], ['ଓ', 'ନ'], ['ପ', 'ର'], ['ଲ', 'ଳ'], ['ଵ', 'ହ'], ['଼', 'ୄ'], ['େ', 'ୈ'], ['ୋ', '୍'], ['ୖ', 'ୗ'], ['ଡ଼', 'ଢ଼'], ['ୟ', 'ୣ'], ['୦', '୯'], 'ୱ', ['ஂ', 'ஃ'], ['அ', 'ஊ'], ['எ', 'ஐ'], ['ஒ', 'க'], ['ங', 'ச'], 'ஜ', ['ஞ', 'ட'], ['ண', 'த'], ['ந', 'ப'], ['ம', 'ஹ'], ['ா', 'ூ'], ['ெ', 'ை'], ['ொ', '்'], 'ௐ', 'ௗ', ['௦', '௯'], ['ఁ', 'ః'], ['అ', 'ఌ'], ['ఎ', 'ఐ'], ['ఒ', 'న'], ['ప', 'ళ'], ['వ', 'హ'], ['ఽ', 'ౄ'], ['ె', 'ై'], ['ొ', '్'], ['ౕ', 'ౖ'], ['ౘ', 'ౙ'], ['ౠ', 'ౣ'], ['౦', '౯'], ['ಂ', 'ಃ'], ['ಅ', 'ಌ'], ['ಎ', 'ಐ'], ['ಒ', 'ನ'], ['ಪ', 'ಳ'], ['ವ', 'ಹ'], ['಼', 'ೄ'], ['ೆ', 'ೈ'], ['ೊ', '್'], ['ೕ', 'ೖ'], 'ೞ', ['ೠ', 'ೣ'], ['೦', '೯'], ['ೱ', 'ೲ'], ['ം', 'ഃ'], ['അ', 'ഌ'], ['എ', 'ഐ'], ['ഒ', 'ഺ'], ['ഽ', 'ൄ'], ['െ', 'ൈ'], ['ൊ', 'ൎ'], 'ൗ', ['ൠ', 'ൣ'], ['൦', '൯'], ['ൺ', 'ൿ'], ['ං', 'ඃ'], ['අ', 'ඖ'], ['ක', 'න'], ['ඳ', 'ර'], 'ල', ['ව', 'ෆ'], '්', ['ා', 'ු'], 'ූ', ['ෘ', 'ෟ'], ['ෲ', 'ෳ'], ['ก', 'ฺ'], ['เ', '๎'], ['๐', '๙'], ['ກ', 'ຂ'], 'ຄ', ['ງ', 'ຈ'], 'ຊ', 'ຍ', ['ດ', 'ທ'], ['ນ', 'ຟ'], ['ມ', 'ຣ'], 'ລ', 'ວ', ['ສ', 'ຫ'], ['ອ', 'ູ'], ['ົ', 'ຽ'], ['ເ', 'ໄ'], 'ໆ', ['່', 'ໍ'], ['໐', '໙'], ['ໜ', 'ໝ'], 'ༀ', ['༘', '༙'], ['༠', '༩'], '༵', '༷', '༹', ['༾', 'ཇ'], ['ཉ', 'ཬ'], ['ཱ', '྄'], ['྆', 'ྗ'], ['ྙ', 'ྼ'], '࿆', ['က', '၉'], ['ၐ', 'ႝ'], ['Ⴀ', 'Ⴥ'], ['ა', 'ჺ'], 'ჼ', ['ᄀ', 'ቈ'], ['ቊ', 'ቍ'], ['ቐ', 'ቖ'], 'ቘ', ['ቚ', 'ቝ'], ['በ', 'ኈ'], ['ኊ', 'ኍ'], ['ነ', 'ኰ'], ['ኲ', 'ኵ'], ['ኸ', 'ኾ'], 'ዀ', ['ዂ', 'ዅ'], ['ወ', 'ዖ'], ['ዘ', 'ጐ'], ['ጒ', 'ጕ'], ['ጘ', 'ፚ'], ['፝', '፟'], ['፩', '፱'], ['ᎀ', 'ᎏ'], ['Ꭰ', 'Ᏼ'], ['ᐁ', 'ᙬ'], ['ᙯ', 'ᙿ'], ['ᚁ', 'ᚚ'], ['ᚠ', 'ᛪ'], ['ᛮ', 'ᛰ'], ['ᜀ', 'ᜌ'], ['ᜎ', '᜔'], ['ᜠ', '᜴'], ['ᝀ', 'ᝓ'], ['ᝠ', 'ᝬ'], ['ᝮ', 'ᝰ'], ['ᝲ', 'ᝳ'], ['ក', 'ឳ'], ['ា', '៓'], 'ៗ', ['ៜ', '៝'], ['០', '៩'], ['᠋', '᠍'], ['᠐', '᠙'], ['ᠠ', 'ᡷ'], ['ᢀ', 'ᢪ'], ['ᢰ', 'ᣵ'], ['ᤀ', 'ᤜ'], ['ᤠ', 'ᤫ'], ['ᤰ', '᤻'], ['᥆', 'ᥭ'], ['ᥰ', 'ᥴ'], ['ᦀ', 'ᦫ'], ['ᦰ', 'ᧉ'], ['᧐', '᧚'], ['ᨀ', 'ᨛ'], ['ᨠ', 'ᩞ'], ['᩠', '᩼'], ['᩿', '᪉'], ['᪐', '᪙'], 'ᪧ', ['ᬀ', 'ᭋ'], ['᭐', '᭙'], ['᭫', '᭳'], ['ᮀ', '᮪'], ['ᮮ', '᮹'], ['ᯀ', '᯳'], ['ᰀ', '᰷'], ['᱀', '᱉'], ['ᱍ', 'ᱽ'], ['᳐', '᳒'], ['᳔', 'ᳲ'], ['ᴀ', 'ᷦ'], ['᷼', 'ἕ'], ['Ἐ', 'Ἕ'], ['ἠ', 'ὅ'], ['Ὀ', 'Ὅ'], ['ὐ', 'ὗ'], 'Ὑ', 'Ὓ', 'Ὕ', ['Ὗ', 'ώ'], ['ᾀ', 'ᾴ'], ['ᾶ', 'ᾼ'], 'ι', ['ῂ', 'ῄ'], ['ῆ', 'ῌ'], ['ῐ', 'ΐ'], ['ῖ', 'Ί'], ['ῠ', 'Ῥ'], ['ῲ', 'ῴ'], ['ῶ', 'ῼ'], ['‿', '⁀'], '⁔', 'ⁱ', 'ⁿ', ['ₐ', 'ₜ'], ['⃐', '⃜'], '⃡', ['⃥', '⃰'], 'ℂ', 'ℇ', ['ℊ', 'ℓ'], 'ℕ', ['℘', 'ℝ'], 'ℤ', 'Ω', 'ℨ', ['K', 'ℹ'], ['ℼ', 'ℿ'], ['ⅅ', 'ⅉ'], 'ⅎ', ['Ⅰ', 'ↈ'], ['Ⰰ', 'Ⱞ'], ['ⰰ', 'ⱞ'], ['Ⱡ', 'ⳤ'], ['Ⳬ', '⳱'], ['ⴀ', 'ⴥ'], ['ⴰ', 'ⵥ'], 'ⵯ', ['⵿', 'ⶖ'], ['ⶠ', 'ⶦ'], ['ⶨ', 'ⶮ'], ['ⶰ', 'ⶶ'], ['ⶸ', 'ⶾ'], ['ⷀ', 'ⷆ'], ['ⷈ', 'ⷎ'], ['ⷐ', 'ⷖ'], ['ⷘ', 'ⷞ'], ['ⷠ', 'ⷿ'], ['々', '〇'], ['〡', '〯'], ['〱', '〵'], ['〸', '〼'], ['ぁ', 'ゖ'], ['゙', '゚'], ['ゝ', 'ゟ'], ['ァ', 'ヺ'], ['ー', 'ヿ'], ['ㄅ', 'ㄭ'], ['ㄱ', 'ㆎ'], ['ㆠ', 'ㆺ'], ['ㇰ', 'ㇿ'], ['㐀', '䶵'], ['一', '鿋'], ['ꀀ', 'ꒌ'], ['ꓐ', 'ꓽ'], ['ꔀ', 'ꘌ'], ['ꘐ', 'ꘫ'], ['Ꙁ', '꙯'], ['꙼', '꙽'], ['ꙿ', 'ꚗ'], ['ꚠ', '꛱'], ['ꜗ', 'ꜟ'], ['Ꜣ', 'ꞈ'], ['Ꞌ', 'ꞎ'], ['Ꞑ', 'ꞑ'], ['Ꞡ', 'ꞩ'], ['ꟺ', 'ꠧ'], ['ꡀ', 'ꡳ'], ['ꢀ', '꣄'], ['꣐', '꣙'], ['꣠', 'ꣷ'], 'ꣻ', ['꤀', '꤭'], ['ꤰ', '꥓'], ['ꥠ', 'ꥼ'], ['ꦀ', '꧀'], ['ꧏ', '꧙'], ['ꨀ', 'ꨶ'], ['ꩀ', 'ꩍ'], ['꩐', '꩙'], ['ꩠ', 'ꩶ'], ['ꩺ', 'ꩻ'], ['ꪀ', 'ꫂ'], ['ꫛ', 'ꫝ'], ['ꬁ', 'ꬆ'], ['ꬉ', 'ꬎ'], ['ꬑ', 'ꬖ'], ['ꬠ', 'ꬦ'], ['ꬨ', 'ꬮ'], ['ꯀ', 'ꯪ'], ['꯬', '꯭'], ['꯰', '꯹'], ['가', '힣'], ['ힰ', 'ퟆ'], ['ퟋ', 'ퟻ'], ['豈', '鶴'], ['侮', '舘'], ['並', '龎'], ['ﬀ', 'ﬆ'], ['ﬓ', 'ﬗ'], ['יִ', 'ﬨ'], ['שׁ', 'זּ'], ['טּ', 'לּ'], 'מּ', ['נּ', 'סּ'], ['ףּ', 'פּ'], ['צּ', 'ﮱ'], ['ﯓ', 'ﱝ'], ['ﱤ', 'ﴽ'], ['ﵐ', 'ﶏ'], ['ﶒ', 'ﷇ'], ['ﷰ', 'ﷹ'], ['︀', '️'], ['︠', '︦'], ['︳', '︴'], ['﹍', '﹏'], 'ﹱ', 'ﹳ', 'ﹷ', 'ﹹ', 'ﹻ', 'ﹽ', ['ﹿ', 'ﻼ'], ['０', '９'], ['Ａ', 'Ｚ'], '＿', ['ａ', 'ｚ'], ['ｦ', 'ﾾ'], ['ￂ', 'ￇ'], ['ￊ', 'ￏ'], ['ￒ', 'ￗ'], ['ￚ', 'ￜ'], ['𐀀', '𐀋'], ['𐀍', '𐀦'], ['𐀨', '𐀺'], ['𐀼', '𐀽'], ['𐀿', '𐁍'], ['𐁐', '𐁝'], ['𐂀', '𐃺'], ['𐅀', '𐅴'], '𐇽', ['𐊀', '𐊜'], ['𐊠', '𐋐'], ['𐌀', '𐌞'], ['𐌰', '𐍊'], ['𐎀', '𐎝'], ['𐎠', '𐏃'], ['𐏈', '𐏏'], ['𐏑', '𐏕'], ['𐐀', '𐒝'], ['𐒠', '𐒩'], ['𐠀', '𐠅'], '𐠈', ['𐠊', '𐠵'], ['𐠷', '𐠸'], '𐠼', ['𐠿', '𐡕'], ['𐤀', '𐤕'], ['𐤠', '𐤹'], ['𐨀', '𐨃'], ['𐨅', '𐨆'], ['𐨌', '𐨓'], ['𐨕', '𐨗'], ['𐨙', '𐨳'], ['𐨸', '𐨺'], '𐨿', ['𐩠', '𐩼'], ['𐬀', '𐬵'], ['𐭀', '𐭕'], ['𐭠', '𐭲'], ['𐰀', '𐱈'], ['𑀀', '𑁆'], ['𑁦', '𑁯'], ['𑂀', '𑂺'], ['𒀀', '𒍮'], ['𒐀', '𒑢'], ['𓀀', '𓐮'], ['𖠀', '𖨸'], ['𛀀', '𛀁'], ['𝅥', '𝅩'], ['𝅭', '𝅲'], ['𝅻', '𝆂'], ['𝆅', '𝆋'], ['𝆪', '𝆭'], ['𝉂', '𝉄'], ['𝐀', '𝑔'], ['𝑖', '𝒜'], ['𝒞', '𝒟'], '𝒢', ['𝒥', '𝒦'], ['𝒩', '𝒬'], ['𝒮', '𝒹'], '𝒻', ['𝒽', '𝓃'], ['𝓅', '𝔅'], ['𝔇', '𝔊'], ['𝔍', '𝔔'], ['𝔖', '𝔜'], ['𝔞', '𝔹'], ['𝔻', '𝔾'], ['𝕀', '𝕄'], '𝕆', ['𝕊', '𝕐'], ['𝕒', '𝚥'], ['𝚨', '𝛀'], ['𝛂', '𝛚'], ['𝛜', '𝛺'], ['𝛼', '𝜔'], ['𝜖', '𝜴'], ['𝜶', '𝝎'], ['𝝐', '𝝮'], ['𝝰', '𝞈'], ['𝞊', '𝞨'], ['𝞪', '𝟂'], ['𝟄', '𝟋'], ['𝟎', '𝟿'], ['𠀀', '𪛖'], ['𪜀', '𫜴'], ['𫝀', '𫠝'], ['丽', '𪘀'], ['󠄀', '󠇯'] ==> 00471
     *      == ' ' ==> 00458
     *      == ['₀', '₉'] ==> 00473
     *     
     * 00471 (354, 261, A)
     *      == ['0', '9'], ['A', 'Z'], '_', ['a', 'z'], 'ª', 'µ', '·', 'º', ['À', 'Ö'], ['Ø', 'ö'], ['ø', 'ý'], ['Ā', 'ˁ'], ['ˆ', 'ˑ'], ['ˠ', 'ˤ'], 'ˬ', 'ˮ', ['̀', 'ʹ'], ['Ͷ', 'ͷ'], ['ͻ', 'ͽ'], ['Ά', 'Ί'], 'Ό', ['Ύ', 'Ρ'], ['Σ', 'ϵ'], ['Ϸ', 'ҁ'], ['҃', '҇'], ['Ҋ', 'ԧ'], ['Ա', 'Ֆ'], 'ՙ', ['ա', 'և'], ['֑', 'ֽ'], 'ֿ', ['ׁ', 'ׂ'], ['ׄ', 'ׅ'], 'ׇ', ['א', 'ת'], ['װ', 'ײ'], ['ؐ', 'ؚ'], ['ؠ', '٩'], ['ٮ', 'ۓ'], ['ە', 'ۜ'], ['۟', 'ۨ'], ['۪', 'ۼ'], 'ۿ', ['ܐ', '݊'], ['ݍ', 'ޱ'], ['߀', 'ߵ'], 'ߺ', ['ࠀ', '࠭'], ['ࡀ', '࡛'], ['ऀ', 'ॣ'], ['०', '९'], ['ॱ', 'ॷ'], ['ॹ', 'ॿ'], ['ঁ', 'ঃ'], ['অ', 'ঌ'], ['এ', 'ঐ'], ['ও', 'ন'], ['প', 'র'], 'ল', ['শ', 'হ'], ['়', 'ৄ'], ['ে', 'ৈ'], ['ো', 'ৎ'], 'ৗ', ['ড়', 'ঢ়'], ['য়', 'ৣ'], ['০', 'ৱ'], ['ਁ', 'ਃ'], ['ਅ', 'ਊ'], ['ਏ', 'ਐ'], ['ਓ', 'ਨ'], ['ਪ', 'ਰ'], ['ਲ', 'ਲ਼'], ['ਵ', 'ਸ਼'], ['ਸ', 'ਹ'], '਼', ['ਾ', 'ੂ'], ['ੇ', 'ੈ'], ['ੋ', '੍'], 'ੑ', ['ਖ਼', 'ੜ'], 'ਫ਼', ['੦', 'ੵ'], ['ઁ', 'ઃ'], ['અ', 'ઍ'], ['એ', 'ઑ'], ['ઓ', 'ન'], ['પ', 'ર'], ['લ', 'ળ'], ['વ', 'હ'], ['઼', 'ૅ'], ['ે', 'ૉ'], ['ો', '્'], 'ૐ', ['ૠ', 'ૣ'], ['૦', '૯'], ['ଁ', 'ଃ'], ['ଅ', 'ଌ'], ['ଏ', 'ଐ'], ['ଓ', 'ନ'], ['ପ', 'ର'], ['ଲ', 'ଳ'], ['ଵ', 'ହ'], ['଼', 'ୄ'], ['େ', 'ୈ'], ['ୋ', '୍'], ['ୖ', 'ୗ'], ['ଡ଼', 'ଢ଼'], ['ୟ', 'ୣ'], ['୦', '୯'], 'ୱ', ['ஂ', 'ஃ'], ['அ', 'ஊ'], ['எ', 'ஐ'], ['ஒ', 'க'], ['ங', 'ச'], 'ஜ', ['ஞ', 'ட'], ['ண', 'த'], ['ந', 'ப'], ['ம', 'ஹ'], ['ா', 'ூ'], ['ெ', 'ை'], ['ொ', '்'], 'ௐ', 'ௗ', ['௦', '௯'], ['ఁ', 'ః'], ['అ', 'ఌ'], ['ఎ', 'ఐ'], ['ఒ', 'న'], ['ప', 'ళ'], ['వ', 'హ'], ['ఽ', 'ౄ'], ['ె', 'ై'], ['ొ', '్'], ['ౕ', 'ౖ'], ['ౘ', 'ౙ'], ['ౠ', 'ౣ'], ['౦', '౯'], ['ಂ', 'ಃ'], ['ಅ', 'ಌ'], ['ಎ', 'ಐ'], ['ಒ', 'ನ'], ['ಪ', 'ಳ'], ['ವ', 'ಹ'], ['಼', 'ೄ'], ['ೆ', 'ೈ'], ['ೊ', '್'], ['ೕ', 'ೖ'], 'ೞ', ['ೠ', 'ೣ'], ['೦', '೯'], ['ೱ', 'ೲ'], ['ം', 'ഃ'], ['അ', 'ഌ'], ['എ', 'ഐ'], ['ഒ', 'ഺ'], ['ഽ', 'ൄ'], ['െ', 'ൈ'], ['ൊ', 'ൎ'], 'ൗ', ['ൠ', 'ൣ'], ['൦', '൯'], ['ൺ', 'ൿ'], ['ං', 'ඃ'], ['අ', 'ඖ'], ['ක', 'න'], ['ඳ', 'ර'], 'ල', ['ව', 'ෆ'], '්', ['ා', 'ු'], 'ූ', ['ෘ', 'ෟ'], ['ෲ', 'ෳ'], ['ก', 'ฺ'], ['เ', '๎'], ['๐', '๙'], ['ກ', 'ຂ'], 'ຄ', ['ງ', 'ຈ'], 'ຊ', 'ຍ', ['ດ', 'ທ'], ['ນ', 'ຟ'], ['ມ', 'ຣ'], 'ລ', 'ວ', ['ສ', 'ຫ'], ['ອ', 'ູ'], ['ົ', 'ຽ'], ['ເ', 'ໄ'], 'ໆ', ['່', 'ໍ'], ['໐', '໙'], ['ໜ', 'ໝ'], 'ༀ', ['༘', '༙'], ['༠', '༩'], '༵', '༷', '༹', ['༾', 'ཇ'], ['ཉ', 'ཬ'], ['ཱ', '྄'], ['྆', 'ྗ'], ['ྙ', 'ྼ'], '࿆', ['က', '၉'], ['ၐ', 'ႝ'], ['Ⴀ', 'Ⴥ'], ['ა', 'ჺ'], 'ჼ', ['ᄀ', 'ቈ'], ['ቊ', 'ቍ'], ['ቐ', 'ቖ'], 'ቘ', ['ቚ', 'ቝ'], ['በ', 'ኈ'], ['ኊ', 'ኍ'], ['ነ', 'ኰ'], ['ኲ', 'ኵ'], ['ኸ', 'ኾ'], 'ዀ', ['ዂ', 'ዅ'], ['ወ', 'ዖ'], ['ዘ', 'ጐ'], ['ጒ', 'ጕ'], ['ጘ', 'ፚ'], ['፝', '፟'], ['፩', '፱'], ['ᎀ', 'ᎏ'], ['Ꭰ', 'Ᏼ'], ['ᐁ', 'ᙬ'], ['ᙯ', 'ᙿ'], ['ᚁ', 'ᚚ'], ['ᚠ', 'ᛪ'], ['ᛮ', 'ᛰ'], ['ᜀ', 'ᜌ'], ['ᜎ', '᜔'], ['ᜠ', '᜴'], ['ᝀ', 'ᝓ'], ['ᝠ', 'ᝬ'], ['ᝮ', 'ᝰ'], ['ᝲ', 'ᝳ'], ['ក', 'ឳ'], ['ា', '៓'], 'ៗ', ['ៜ', '៝'], ['០', '៩'], ['᠋', '᠍'], ['᠐', '᠙'], ['ᠠ', 'ᡷ'], ['ᢀ', 'ᢪ'], ['ᢰ', 'ᣵ'], ['ᤀ', 'ᤜ'], ['ᤠ', 'ᤫ'], ['ᤰ', '᤻'], ['᥆', 'ᥭ'], ['ᥰ', 'ᥴ'], ['ᦀ', 'ᦫ'], ['ᦰ', 'ᧉ'], ['᧐', '᧚'], ['ᨀ', 'ᨛ'], ['ᨠ', 'ᩞ'], ['᩠', '᩼'], ['᩿', '᪉'], ['᪐', '᪙'], 'ᪧ', ['ᬀ', 'ᭋ'], ['᭐', '᭙'], ['᭫', '᭳'], ['ᮀ', '᮪'], ['ᮮ', '᮹'], ['ᯀ', '᯳'], ['ᰀ', '᰷'], ['᱀', '᱉'], ['ᱍ', 'ᱽ'], ['᳐', '᳒'], ['᳔', 'ᳲ'], ['ᴀ', 'ᷦ'], ['᷼', 'ἕ'], ['Ἐ', 'Ἕ'], ['ἠ', 'ὅ'], ['Ὀ', 'Ὅ'], ['ὐ', 'ὗ'], 'Ὑ', 'Ὓ', 'Ὕ', ['Ὗ', 'ώ'], ['ᾀ', 'ᾴ'], ['ᾶ', 'ᾼ'], 'ι', ['ῂ', 'ῄ'], ['ῆ', 'ῌ'], ['ῐ', 'ΐ'], ['ῖ', 'Ί'], ['ῠ', 'Ῥ'], ['ῲ', 'ῴ'], ['ῶ', 'ῼ'], ['‿', '⁀'], '⁔', 'ⁱ', 'ⁿ', ['ₐ', 'ₜ'], ['⃐', '⃜'], '⃡', ['⃥', '⃰'], 'ℂ', 'ℇ', ['ℊ', 'ℓ'], 'ℕ', ['℘', 'ℝ'], 'ℤ', 'Ω', 'ℨ', ['K', 'ℹ'], ['ℼ', 'ℿ'], ['ⅅ', 'ⅉ'], 'ⅎ', ['Ⅰ', 'ↈ'], ['Ⰰ', 'Ⱞ'], ['ⰰ', 'ⱞ'], ['Ⱡ', 'ⳤ'], ['Ⳬ', '⳱'], ['ⴀ', 'ⴥ'], ['ⴰ', 'ⵥ'], 'ⵯ', ['⵿', 'ⶖ'], ['ⶠ', 'ⶦ'], ['ⶨ', 'ⶮ'], ['ⶰ', 'ⶶ'], ['ⶸ', 'ⶾ'], ['ⷀ', 'ⷆ'], ['ⷈ', 'ⷎ'], ['ⷐ', 'ⷖ'], ['ⷘ', 'ⷞ'], ['ⷠ', 'ⷿ'], ['々', '〇'], ['〡', '〯'], ['〱', '〵'], ['〸', '〼'], ['ぁ', 'ゖ'], ['゙', '゚'], ['ゝ', 'ゟ'], ['ァ', 'ヺ'], ['ー', 'ヿ'], ['ㄅ', 'ㄭ'], ['ㄱ', 'ㆎ'], ['ㆠ', 'ㆺ'], ['ㇰ', 'ㇿ'], ['㐀', '䶵'], ['一', '鿋'], ['ꀀ', 'ꒌ'], ['ꓐ', 'ꓽ'], ['ꔀ', 'ꘌ'], ['ꘐ', 'ꘫ'], ['Ꙁ', '꙯'], ['꙼', '꙽'], ['ꙿ', 'ꚗ'], ['ꚠ', '꛱'], ['ꜗ', 'ꜟ'], ['Ꜣ', 'ꞈ'], ['Ꞌ', 'ꞎ'], ['Ꞑ', 'ꞑ'], ['Ꞡ', 'ꞩ'], ['ꟺ', 'ꠧ'], ['ꡀ', 'ꡳ'], ['ꢀ', '꣄'], ['꣐', '꣙'], ['꣠', 'ꣷ'], 'ꣻ', ['꤀', '꤭'], ['ꤰ', '꥓'], ['ꥠ', 'ꥼ'], ['ꦀ', '꧀'], ['ꧏ', '꧙'], ['ꨀ', 'ꨶ'], ['ꩀ', 'ꩍ'], ['꩐', '꩙'], ['ꩠ', 'ꩶ'], ['ꩺ', 'ꩻ'], ['ꪀ', 'ꫂ'], ['ꫛ', 'ꫝ'], ['ꬁ', 'ꬆ'], ['ꬉ', 'ꬎ'], ['ꬑ', 'ꬖ'], ['ꬠ', 'ꬦ'], ['ꬨ', 'ꬮ'], ['ꯀ', 'ꯪ'], ['꯬', '꯭'], ['꯰', '꯹'], ['가', '힣'], ['ힰ', 'ퟆ'], ['ퟋ', 'ퟻ'], ['豈', '鶴'], ['侮', '舘'], ['並', '龎'], ['ﬀ', 'ﬆ'], ['ﬓ', 'ﬗ'], ['יִ', 'ﬨ'], ['שׁ', 'זּ'], ['טּ', 'לּ'], 'מּ', ['נּ', 'סּ'], ['ףּ', 'פּ'], ['צּ', 'ﮱ'], ['ﯓ', 'ﱝ'], ['ﱤ', 'ﴽ'], ['ﵐ', 'ﶏ'], ['ﶒ', 'ﷇ'], ['ﷰ', 'ﷹ'], ['︀', '️'], ['︠', '︦'], ['︳', '︴'], ['﹍', '﹏'], 'ﹱ', 'ﹳ', 'ﹷ', 'ﹹ', 'ﹻ', 'ﹽ', ['ﹿ', 'ﻼ'], ['０', '９'], ['Ａ', 'Ｚ'], '＿', ['ａ', 'ｚ'], ['ｦ', 'ﾾ'], ['ￂ', 'ￇ'], ['ￊ', 'ￏ'], ['ￒ', 'ￗ'], ['ￚ', 'ￜ'], ['𐀀', '𐀋'], ['𐀍', '𐀦'], ['𐀨', '𐀺'], ['𐀼', '𐀽'], ['𐀿', '𐁍'], ['𐁐', '𐁝'], ['𐂀', '𐃺'], ['𐅀', '𐅴'], '𐇽', ['𐊀', '𐊜'], ['𐊠', '𐋐'], ['𐌀', '𐌞'], ['𐌰', '𐍊'], ['𐎀', '𐎝'], ['𐎠', '𐏃'], ['𐏈', '𐏏'], ['𐏑', '𐏕'], ['𐐀', '𐒝'], ['𐒠', '𐒩'], ['𐠀', '𐠅'], '𐠈', ['𐠊', '𐠵'], ['𐠷', '𐠸'], '𐠼', ['𐠿', '𐡕'], ['𐤀', '𐤕'], ['𐤠', '𐤹'], ['𐨀', '𐨃'], ['𐨅', '𐨆'], ['𐨌', '𐨓'], ['𐨕', '𐨗'], ['𐨙', '𐨳'], ['𐨸', '𐨺'], '𐨿', ['𐩠', '𐩼'], ['𐬀', '𐬵'], ['𐭀', '𐭕'], ['𐭠', '𐭲'], ['𐰀', '𐱈'], ['𑀀', '𑁆'], ['𑁦', '𑁯'], ['𑂀', '𑂺'], ['𒀀', '𒍮'], ['𒐀', '𒑢'], ['𓀀', '𓐮'], ['𖠀', '𖨸'], ['𛀀', '𛀁'], ['𝅥', '𝅩'], ['𝅭', '𝅲'], ['𝅻', '𝆂'], ['𝆅', '𝆋'], ['𝆪', '𝆭'], ['𝉂', '𝉄'], ['𝐀', '𝑔'], ['𝑖', '𝒜'], ['𝒞', '𝒟'], '𝒢', ['𝒥', '𝒦'], ['𝒩', '𝒬'], ['𝒮', '𝒹'], '𝒻', ['𝒽', '𝓃'], ['𝓅', '𝔅'], ['𝔇', '𝔊'], ['𝔍', '𝔔'], ['𝔖', '𝔜'], ['𝔞', '𝔹'], ['𝔻', '𝔾'], ['𝕀', '𝕄'], '𝕆', ['𝕊', '𝕐'], ['𝕒', '𝚥'], ['𝚨', '𝛀'], ['𝛂', '𝛚'], ['𝛜', '𝛺'], ['𝛼', '𝜔'], ['𝜖', '𝜴'], ['𝜶', '𝝎'], ['𝝐', '𝝮'], ['𝝰', '𝞈'], ['𝞊', '𝞨'], ['𝞪', '𝟂'], ['𝟄', '𝟋'], ['𝟎', '𝟿'], ['𠀀', '𪛖'], ['𪜀', '𫜴'], ['𫝀', '𫠝'], ['丽', '𪘀'], ['󠄀', '󠇯'] ==> 00471
     *     
     * 00460 (353, 257, A)
     *     
     * 00464 (356, 277, A), (358, 285, A)
     *     
     * 00472 (357, 281, A), (358, 285, A)
     *     
     * 00468 (346, 229, A), (358, 285, A)
     *     
     * 00456 (350, 245, A), (358, 285, A)
     *     
     * 00459 (347, 233, A), (358, 285, A)
     *     
     * 00469 (345, 225, A), (358, 285, A)
     *     
     * 00470 (349, 241, A), (358, 285, A)
     *     
     * 00457 (348, 237, A), (358, 285, A)
     *     
     * END: STATE MACHINE
     */
_484: /* INIT_STATE_TRANSITION_BLOCK */
    input = *(me->buffer._input_p);
    __quex_debug("Init State\n");
    __quex_debug_state(455);
    if( input < 0x1D00 ) {
        if( input < 0xBD0 ) {
            if( input < 0x816 ) {
                if( input < 0x370 ) {
                    if( input < 0xAD ) {
                        switch( input ) {
                            case 0x9: goto _465;/* '\t' */

                            case 0xA: goto _485;/* '\n' */

                            case 0xB: 
                            case 0xC: goto _465;/* ['\v', '\f'] */

                            case 0xD: goto _485;/* '\r' */

                            case 0x1C: 
                            case 0x1D: 
                            case 0x1E: goto _485;/* [\28, \30] */

                            case 0x20: goto _465;/* ' ' */

                            case 0x21: 
                            case 0x22: 
                            case 0x23: 
                            case 0x24: 
                            case 0x25: 
                            case 0x26: 
                            case 0x27: goto _462;/* ['!', '''] */

                            case 0x28: goto _463;/* '(' */

                            case 0x29: goto _467;/* ')' */

                            case 0x2A: 
                            case 0x2B: 
                            case 0x2C: 
                            case 0x2D: 
                            case 0x2E: 
                            case 0x2F: goto _462;/* ['*', '/'] */

                            case 0x30: 
                            case 0x31: 
                            case 0x32: 
                            case 0x33: 
                            case 0x34: 
                            case 0x35: 
                            case 0x36: 
                            case 0x37: 
                            case 0x38: 
                            case 0x39: goto _486;/* ['0', '9'] */

                            case 0x3A: 
                            case 0x3B: 
                            case 0x3C: 
                            case 0x3D: 
                            case 0x3E: 
                            case 0x3F: 
                            case 0x40: goto _462;/* [':', '@'] */

                            case 0x41: 
                            case 0x42: 
                            case 0x43: 
                            case 0x44: 
                            case 0x45: 
                            case 0x46: 
                            case 0x47: 
                            case 0x48: 
                            case 0x49: 
                            case 0x4A: 
                            case 0x4B: 
                            case 0x4C: 
                            case 0x4D: 
                            case 0x4E: 
                            case 0x4F: 
                            case 0x50: 
                            case 0x51: 
                            case 0x52: 
                            case 0x53: 
                            case 0x54: 
                            case 0x55: 
                            case 0x56: 
                            case 0x57: 
                            case 0x58: 
                            case 0x59: 
                            case 0x5A: goto _487;/* ['A', 'Z'] */

                            case 0x5B: 
                            case 0x5C: 
                            case 0x5D: 
                            case 0x5E: goto _462;/* ['[', '^'] */

                            case 0x60: goto _462;/* '`' */

                            case 0x61: 
                            case 0x62: 
                            case 0x63: 
                            case 0x64: 
                            case 0x65: 
                            case 0x66: 
                            case 0x67: 
                            case 0x68: 
                            case 0x69: 
                            case 0x6A: 
                            case 0x6B: 
                            case 0x6C: 
                            case 0x6D: 
                            case 0x6E: 
                            case 0x6F: 
                            case 0x70: 
                            case 0x71: 
                            case 0x72: 
                            case 0x73: 
                            case 0x74: 
                            case 0x75: 
                            case 0x76: 
                            case 0x77: 
                            case 0x78: 
                            case 0x79: 
                            case 0x7A: goto _488;/* ['a', 'z'] */

                            case 0x7B: 
                            case 0x7C: 
                            case 0x7D: 
                            case 0x7E: goto _462;/* ['{', '~'] */

                            case 0x85: goto _485;/* '' */

                            case 0xA0: goto _465;/* ' ' */

                            case 0xA1: 
                            case 0xA2: 
                            case 0xA3: 
                            case 0xA4: 
                            case 0xA5: 
                            case 0xA6: 
                            case 0xA7: goto _462;/* ['¡', '§'] */

                            case 0xA9: goto _462;/* '©' */

                            case 0xAA: goto _488;/* 'ª' */

                            case 0xAB: 
                            case 0xAC: goto _462;/* ['«', '¬'] */


                        }
                    } else {
                        if( input < 0xD8 ) {
                            switch( input ) {
                                case 0xAE: goto _462;/* '®' */

                                case 0xB0: 
                                case 0xB1: goto _462;/* ['°', '±'] */

                                case 0xB5: goto _488;/* 'µ' */

                                case 0xB6: goto _462;/* '¶' */

                                case 0xB7: goto _460;/* '·' */

                                case 0xBA: goto _488;/* 'º' */

                                case 0xBB: goto _462;/* '»' */

                                case 0xBF: goto _462;/* '¿' */

                                case 0xC0: 
                                case 0xC1: 
                                case 0xC2: 
                                case 0xC3: 
                                case 0xC4: 
                                case 0xC5: 
                                case 0xC6: 
                                case 0xC7: 
                                case 0xC8: 
                                case 0xC9: 
                                case 0xCA: 
                                case 0xCB: 
                                case 0xCC: 
                                case 0xCD: 
                                case 0xCE: 
                                case 0xCF: 
                                case 0xD0: 
                                case 0xD1: 
                                case 0xD2: 
                                case 0xD3: 
                                case 0xD4: 
                                case 0xD5: 
                                case 0xD6: goto _488;/* ['À', 'Ö'] */

                                case 0xD7: goto _462;/* '×' */


                            }
                        } else {
                            if( input < 0x2C6 ) {
                                if( input < 0xFE ) {
                                    switch( input ) {
                                        case 0xD8: 
                                        case 0xD9: 
                                        case 0xDA: 
                                        case 0xDB: 
                                        case 0xDC: 
                                        case 0xDD: 
                                        case 0xDE: 
                                        case 0xDF: 
                                        case 0xE0: 
                                        case 0xE1: 
                                        case 0xE2: 
                                        case 0xE3: 
                                        case 0xE4: 
                                        case 0xE5: 
                                        case 0xE6: 
                                        case 0xE7: 
                                        case 0xE8: 
                                        case 0xE9: 
                                        case 0xEA: 
                                        case 0xEB: 
                                        case 0xEC: 
                                        case 0xED: 
                                        case 0xEE: 
                                        case 0xEF: 
                                        case 0xF0: 
                                        case 0xF1: 
                                        case 0xF2: 
                                        case 0xF3: 
                                        case 0xF4: 
                                        case 0xF5: 
                                        case 0xF6: goto _488;/* ['Ø', 'ö'] */

                                        case 0xF7: goto _462;/* '÷' */

                                        case 0xF8: 
                                        case 0xF9: 
                                        case 0xFA: 
                                        case 0xFB: 
                                        case 0xFC: 
                                        case 0xFD: goto _488;/* ['ø', 'ý'] */


                                    }
                                } else {
                                    if( input >= 0x2C2 ) {

                                    } else if( input >= 0x100 ) {
                                        goto _488;/* ['Ā', 'ˁ'] */

                                    } else if( input == 0xFF ) {
                                        QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 455, 363);/* 'ÿ' */

                                    } else {

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x2C6: 
                                    case 0x2C7: 
                                    case 0x2C8: 
                                    case 0x2C9: 
                                    case 0x2CA: 
                                    case 0x2CB: 
                                    case 0x2CC: 
                                    case 0x2CD: 
                                    case 0x2CE: 
                                    case 0x2CF: 
                                    case 0x2D0: 
                                    case 0x2D1: goto _488;/* ['ˆ', 'ˑ'] */

                                    case 0x2E0: 
                                    case 0x2E1: 
                                    case 0x2E2: 
                                    case 0x2E3: 
                                    case 0x2E4: goto _488;/* ['ˠ', 'ˤ'] */

                                    case 0x2EC: goto _488;/* 'ˬ' */

                                    case 0x2EE: goto _488;/* 'ˮ' */


                                }
                            }
                        }
                    }
                } else {
                    if( input < 0x620 ) {
                        if( input < 0x3F6 ) {
                            switch( input ) {
                                case 0x370: 
                                case 0x371: 
                                case 0x372: 
                                case 0x373: 
                                case 0x374: goto _488;/* ['Ͱ', 'ʹ'] */

                                case 0x376: 
                                case 0x377: goto _488;/* ['Ͷ', 'ͷ'] */

                                case 0x37B: 
                                case 0x37C: 
                                case 0x37D: goto _488;/* ['ͻ', 'ͽ'] */

                                case 0x386: goto _488;/* 'Ά' */

                                case 0x388: 
                                case 0x389: 
                                case 0x38A: goto _488;/* ['Έ', 'Ί'] */

                                case 0x38C: goto _488;/* 'Ό' */

                                case 0x38E: 
                                case 0x38F: 
                                case 0x390: 
                                case 0x391: 
                                case 0x392: 
                                case 0x393: 
                                case 0x394: 
                                case 0x395: 
                                case 0x396: 
                                case 0x397: 
                                case 0x398: 
                                case 0x399: 
                                case 0x39A: 
                                case 0x39B: 
                                case 0x39C: 
                                case 0x39D: 
                                case 0x39E: 
                                case 0x39F: 
                                case 0x3A0: 
                                case 0x3A1: goto _488;/* ['Ύ', 'Ρ'] */

                                case 0x3A3: 
                                case 0x3A4: 
                                case 0x3A5: 
                                case 0x3A6: 
                                case 0x3A7: 
                                case 0x3A8: 
                                case 0x3A9: 
                                case 0x3AA: 
                                case 0x3AB: 
                                case 0x3AC: 
                                case 0x3AD: 
                                case 0x3AE: 
                                case 0x3AF: 
                                case 0x3B0: 
                                case 0x3B1: 
                                case 0x3B2: 
                                case 0x3B3: 
                                case 0x3B4: 
                                case 0x3B5: 
                                case 0x3B6: 
                                case 0x3B7: 
                                case 0x3B8: 
                                case 0x3B9: 
                                case 0x3BA: 
                                case 0x3BB: 
                                case 0x3BC: 
                                case 0x3BD: 
                                case 0x3BE: 
                                case 0x3BF: 
                                case 0x3C0: 
                                case 0x3C1: 
                                case 0x3C2: 
                                case 0x3C3: 
                                case 0x3C4: 
                                case 0x3C5: 
                                case 0x3C6: 
                                case 0x3C7: 
                                case 0x3C8: 
                                case 0x3C9: 
                                case 0x3CA: 
                                case 0x3CB: 
                                case 0x3CC: 
                                case 0x3CD: 
                                case 0x3CE: 
                                case 0x3CF: 
                                case 0x3D0: 
                                case 0x3D1: 
                                case 0x3D2: 
                                case 0x3D3: 
                                case 0x3D4: 
                                case 0x3D5: 
                                case 0x3D6: 
                                case 0x3D7: 
                                case 0x3D8: 
                                case 0x3D9: 
                                case 0x3DA: 
                                case 0x3DB: 
                                case 0x3DC: 
                                case 0x3DD: 
                                case 0x3DE: 
                                case 0x3DF: 
                                case 0x3E0: 
                                case 0x3E1: 
                                case 0x3E2: 
                                case 0x3E3: 
                                case 0x3E4: 
                                case 0x3E5: 
                                case 0x3E6: 
                                case 0x3E7: 
                                case 0x3E8: 
                                case 0x3E9: 
                                case 0x3EA: 
                                case 0x3EB: 
                                case 0x3EC: 
                                case 0x3ED: 
                                case 0x3EE: 
                                case 0x3EF: 
                                case 0x3F0: 
                                case 0x3F1: 
                                case 0x3F2: 
                                case 0x3F3: 
                                case 0x3F4: 
                                case 0x3F5: goto _488;/* ['Σ', 'ϵ'] */


                            }
                        } else {
                            if( input < 0x559 ) {
                                if( input < 0x48A ) {
                                    if( input == 0x3F6 ) {

                                    } else if( input < 0x482 ) {
                                        goto _488;/* ['Ϸ', 'ҁ'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x528 ) {
                                        goto _488;/* ['Ҋ', 'ԧ'] */

                                    } else if( input < 0x531 ) {

                                    } else if( input < 0x557 ) {
                                        goto _488;/* ['Ա', 'Ֆ'] */

                                    } else {

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x559: goto _488;/* 'ՙ' */

                                    case 0x561: 
                                    case 0x562: 
                                    case 0x563: 
                                    case 0x564: 
                                    case 0x565: 
                                    case 0x566: 
                                    case 0x567: 
                                    case 0x568: 
                                    case 0x569: 
                                    case 0x56A: 
                                    case 0x56B: 
                                    case 0x56C: 
                                    case 0x56D: 
                                    case 0x56E: 
                                    case 0x56F: 
                                    case 0x570: 
                                    case 0x571: 
                                    case 0x572: 
                                    case 0x573: 
                                    case 0x574: 
                                    case 0x575: 
                                    case 0x576: 
                                    case 0x577: 
                                    case 0x578: 
                                    case 0x579: 
                                    case 0x57A: 
                                    case 0x57B: 
                                    case 0x57C: 
                                    case 0x57D: 
                                    case 0x57E: 
                                    case 0x57F: 
                                    case 0x580: 
                                    case 0x581: 
                                    case 0x582: 
                                    case 0x583: 
                                    case 0x584: 
                                    case 0x585: 
                                    case 0x586: 
                                    case 0x587: goto _488;/* ['ա', 'և'] */

                                    case 0x5D0: 
                                    case 0x5D1: 
                                    case 0x5D2: 
                                    case 0x5D3: 
                                    case 0x5D4: 
                                    case 0x5D5: 
                                    case 0x5D6: 
                                    case 0x5D7: 
                                    case 0x5D8: 
                                    case 0x5D9: 
                                    case 0x5DA: 
                                    case 0x5DB: 
                                    case 0x5DC: 
                                    case 0x5DD: 
                                    case 0x5DE: 
                                    case 0x5DF: 
                                    case 0x5E0: 
                                    case 0x5E1: 
                                    case 0x5E2: 
                                    case 0x5E3: 
                                    case 0x5E4: 
                                    case 0x5E5: 
                                    case 0x5E6: 
                                    case 0x5E7: 
                                    case 0x5E8: 
                                    case 0x5E9: 
                                    case 0x5EA: goto _488;/* ['א', 'ת'] */

                                    case 0x5F0: 
                                    case 0x5F1: 
                                    case 0x5F2: goto _488;/* ['װ', 'ײ'] */


                                }
                            }
                        }
                    } else {
                        if( input < 0x700 ) {
                            if( input < 0x6D6 ) {
                                if( input < 0x670 ) {
                                    switch( input ) {
                                        case 0x620: 
                                        case 0x621: 
                                        case 0x622: 
                                        case 0x623: 
                                        case 0x624: 
                                        case 0x625: 
                                        case 0x626: 
                                        case 0x627: 
                                        case 0x628: 
                                        case 0x629: 
                                        case 0x62A: 
                                        case 0x62B: 
                                        case 0x62C: 
                                        case 0x62D: 
                                        case 0x62E: 
                                        case 0x62F: 
                                        case 0x630: 
                                        case 0x631: 
                                        case 0x632: 
                                        case 0x633: 
                                        case 0x634: 
                                        case 0x635: 
                                        case 0x636: 
                                        case 0x637: 
                                        case 0x638: 
                                        case 0x639: 
                                        case 0x63A: 
                                        case 0x63B: 
                                        case 0x63C: 
                                        case 0x63D: 
                                        case 0x63E: 
                                        case 0x63F: 
                                        case 0x640: 
                                        case 0x641: 
                                        case 0x642: 
                                        case 0x643: 
                                        case 0x644: 
                                        case 0x645: 
                                        case 0x646: 
                                        case 0x647: 
                                        case 0x648: 
                                        case 0x649: 
                                        case 0x64A: goto _488;/* ['ؠ', 'ي'] */

                                        case 0x66E: 
                                        case 0x66F: goto _488;/* ['ٮ', 'ٯ'] */


                                    }
                                } else {
                                    if( input == 0x670 ) {

                                    } else if( input < 0x6D4 ) {
                                        goto _488;/* ['ٱ', 'ۓ'] */

                                    } else if( input == 0x6D4 ) {

                                    } else {
                                        goto _488;/* 'ە' */

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x6E5: 
                                    case 0x6E6: goto _488;/* ['ۥ', 'ۦ'] */

                                    case 0x6EE: 
                                    case 0x6EF: goto _488;/* ['ۮ', 'ۯ'] */

                                    case 0x6FA: 
                                    case 0x6FB: 
                                    case 0x6FC: goto _488;/* ['ۺ', 'ۼ'] */

                                    case 0x6FF: goto _488;/* 'ۿ' */


                                }
                            }
                        } else {
                            if( input < 0x7B2 ) {
                                if( input < 0x730 ) {
                                    switch( input ) {
                                        case 0x710: goto _488;/* 'ܐ' */

                                        case 0x712: 
                                        case 0x713: 
                                        case 0x714: 
                                        case 0x715: 
                                        case 0x716: 
                                        case 0x717: 
                                        case 0x718: 
                                        case 0x719: 
                                        case 0x71A: 
                                        case 0x71B: 
                                        case 0x71C: 
                                        case 0x71D: 
                                        case 0x71E: 
                                        case 0x71F: 
                                        case 0x720: 
                                        case 0x721: 
                                        case 0x722: 
                                        case 0x723: 
                                        case 0x724: 
                                        case 0x725: 
                                        case 0x726: 
                                        case 0x727: 
                                        case 0x728: 
                                        case 0x729: 
                                        case 0x72A: 
                                        case 0x72B: 
                                        case 0x72C: 
                                        case 0x72D: 
                                        case 0x72E: 
                                        case 0x72F: goto _488;/* ['ܒ', 'ܯ'] */


                                    }
                                } else {
                                    if( input < 0x74D ) {

                                    } else if( input < 0x7A6 ) {
                                        goto _488;/* ['ݍ', 'ޥ'] */

                                    } else if( input < 0x7B1 ) {

                                    } else {
                                        goto _488;/* 'ޱ' */

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x7CA: 
                                    case 0x7CB: 
                                    case 0x7CC: 
                                    case 0x7CD: 
                                    case 0x7CE: 
                                    case 0x7CF: 
                                    case 0x7D0: 
                                    case 0x7D1: 
                                    case 0x7D2: 
                                    case 0x7D3: 
                                    case 0x7D4: 
                                    case 0x7D5: 
                                    case 0x7D6: 
                                    case 0x7D7: 
                                    case 0x7D8: 
                                    case 0x7D9: 
                                    case 0x7DA: 
                                    case 0x7DB: 
                                    case 0x7DC: 
                                    case 0x7DD: 
                                    case 0x7DE: 
                                    case 0x7DF: 
                                    case 0x7E0: 
                                    case 0x7E1: 
                                    case 0x7E2: 
                                    case 0x7E3: 
                                    case 0x7E4: 
                                    case 0x7E5: 
                                    case 0x7E6: 
                                    case 0x7E7: 
                                    case 0x7E8: 
                                    case 0x7E9: 
                                    case 0x7EA: goto _488;/* ['ߊ', 'ߪ'] */

                                    case 0x7F4: 
                                    case 0x7F5: goto _488;/* ['ߴ', 'ߵ'] */

                                    case 0x7FA: goto _488;/* 'ߺ' */

                                    case 0x800: 
                                    case 0x801: 
                                    case 0x802: 
                                    case 0x803: 
                                    case 0x804: 
                                    case 0x805: 
                                    case 0x806: 
                                    case 0x807: 
                                    case 0x808: 
                                    case 0x809: 
                                    case 0x80A: 
                                    case 0x80B: 
                                    case 0x80C: 
                                    case 0x80D: 
                                    case 0x80E: 
                                    case 0x80F: 
                                    case 0x810: 
                                    case 0x811: 
                                    case 0x812: 
                                    case 0x813: 
                                    case 0x814: 
                                    case 0x815: goto _488;/* ['ࠀ', 'ࠕ'] */


                                }
                            }
                        }
                    }
                }
            } else {
                if( input < 0xA5F ) {
                    if( input < 0x9B3 ) {
                        switch( input ) {
                            case 0x81A: goto _488;/* 'ࠚ' */

                            case 0x824: goto _488;/* 'ࠤ' */

                            case 0x828: goto _488;/* 'ࠨ' */

                            case 0x840: 
                            case 0x841: 
                            case 0x842: 
                            case 0x843: 
                            case 0x844: 
                            case 0x845: 
                            case 0x846: 
                            case 0x847: 
                            case 0x848: 
                            case 0x849: 
                            case 0x84A: 
                            case 0x84B: 
                            case 0x84C: 
                            case 0x84D: 
                            case 0x84E: 
                            case 0x84F: 
                            case 0x850: 
                            case 0x851: 
                            case 0x852: 
                            case 0x853: 
                            case 0x854: 
                            case 0x855: 
                            case 0x856: 
                            case 0x857: 
                            case 0x858: goto _488;/* ['ࡀ', 'ࡘ'] */

                            case 0x904: 
                            case 0x905: 
                            case 0x906: 
                            case 0x907: 
                            case 0x908: 
                            case 0x909: 
                            case 0x90A: 
                            case 0x90B: 
                            case 0x90C: 
                            case 0x90D: 
                            case 0x90E: 
                            case 0x90F: 
                            case 0x910: 
                            case 0x911: 
                            case 0x912: 
                            case 0x913: 
                            case 0x914: 
                            case 0x915: 
                            case 0x916: 
                            case 0x917: 
                            case 0x918: 
                            case 0x919: 
                            case 0x91A: 
                            case 0x91B: 
                            case 0x91C: 
                            case 0x91D: 
                            case 0x91E: 
                            case 0x91F: 
                            case 0x920: 
                            case 0x921: 
                            case 0x922: 
                            case 0x923: 
                            case 0x924: 
                            case 0x925: 
                            case 0x926: 
                            case 0x927: 
                            case 0x928: 
                            case 0x929: 
                            case 0x92A: 
                            case 0x92B: 
                            case 0x92C: 
                            case 0x92D: 
                            case 0x92E: 
                            case 0x92F: 
                            case 0x930: 
                            case 0x931: 
                            case 0x932: 
                            case 0x933: 
                            case 0x934: 
                            case 0x935: 
                            case 0x936: 
                            case 0x937: 
                            case 0x938: 
                            case 0x939: goto _488;/* ['ऄ', 'ह'] */

                            case 0x93D: goto _488;/* 'ऽ' */

                            case 0x950: goto _488;/* 'ॐ' */

                            case 0x958: 
                            case 0x959: 
                            case 0x95A: 
                            case 0x95B: 
                            case 0x95C: 
                            case 0x95D: 
                            case 0x95E: 
                            case 0x95F: 
                            case 0x960: 
                            case 0x961: goto _488;/* ['क़', 'ॡ'] */

                            case 0x971: 
                            case 0x972: 
                            case 0x973: 
                            case 0x974: 
                            case 0x975: 
                            case 0x976: 
                            case 0x977: goto _488;/* ['ॱ', 'ॷ'] */

                            case 0x979: 
                            case 0x97A: 
                            case 0x97B: 
                            case 0x97C: 
                            case 0x97D: 
                            case 0x97E: 
                            case 0x97F: goto _488;/* ['ॹ', 'ॿ'] */

                            case 0x985: 
                            case 0x986: 
                            case 0x987: 
                            case 0x988: 
                            case 0x989: 
                            case 0x98A: 
                            case 0x98B: 
                            case 0x98C: goto _488;/* ['অ', 'ঌ'] */

                            case 0x98F: 
                            case 0x990: goto _488;/* ['এ', 'ঐ'] */

                            case 0x993: 
                            case 0x994: 
                            case 0x995: 
                            case 0x996: 
                            case 0x997: 
                            case 0x998: 
                            case 0x999: 
                            case 0x99A: 
                            case 0x99B: 
                            case 0x99C: 
                            case 0x99D: 
                            case 0x99E: 
                            case 0x99F: 
                            case 0x9A0: 
                            case 0x9A1: 
                            case 0x9A2: 
                            case 0x9A3: 
                            case 0x9A4: 
                            case 0x9A5: 
                            case 0x9A6: 
                            case 0x9A7: 
                            case 0x9A8: goto _488;/* ['ও', 'ন'] */

                            case 0x9AA: 
                            case 0x9AB: 
                            case 0x9AC: 
                            case 0x9AD: 
                            case 0x9AE: 
                            case 0x9AF: 
                            case 0x9B0: goto _488;/* ['প', 'র'] */

                            case 0x9B2: goto _488;/* 'ল' */


                        }
                    } else {
                        switch( input ) {
                            case 0x9B6: 
                            case 0x9B7: 
                            case 0x9B8: 
                            case 0x9B9: goto _488;/* ['শ', 'হ'] */

                            case 0x9BD: goto _488;/* 'ঽ' */

                            case 0x9CE: goto _488;/* 'ৎ' */

                            case 0x9DC: 
                            case 0x9DD: goto _488;/* ['ড়', 'ঢ়'] */

                            case 0x9DF: 
                            case 0x9E0: 
                            case 0x9E1: goto _488;/* ['য়', 'ৡ'] */

                            case 0x9F0: 
                            case 0x9F1: goto _488;/* ['ৰ', 'ৱ'] */

                            case 0xA05: 
                            case 0xA06: 
                            case 0xA07: 
                            case 0xA08: 
                            case 0xA09: 
                            case 0xA0A: goto _488;/* ['ਅ', 'ਊ'] */

                            case 0xA0F: 
                            case 0xA10: goto _488;/* ['ਏ', 'ਐ'] */

                            case 0xA13: 
                            case 0xA14: 
                            case 0xA15: 
                            case 0xA16: 
                            case 0xA17: 
                            case 0xA18: 
                            case 0xA19: 
                            case 0xA1A: 
                            case 0xA1B: 
                            case 0xA1C: 
                            case 0xA1D: 
                            case 0xA1E: 
                            case 0xA1F: 
                            case 0xA20: 
                            case 0xA21: 
                            case 0xA22: 
                            case 0xA23: 
                            case 0xA24: 
                            case 0xA25: 
                            case 0xA26: 
                            case 0xA27: 
                            case 0xA28: goto _488;/* ['ਓ', 'ਨ'] */

                            case 0xA2A: 
                            case 0xA2B: 
                            case 0xA2C: 
                            case 0xA2D: 
                            case 0xA2E: 
                            case 0xA2F: 
                            case 0xA30: goto _488;/* ['ਪ', 'ਰ'] */

                            case 0xA32: 
                            case 0xA33: goto _488;/* ['ਲ', 'ਲ਼'] */

                            case 0xA35: 
                            case 0xA36: goto _488;/* ['ਵ', 'ਸ਼'] */

                            case 0xA38: 
                            case 0xA39: goto _488;/* ['ਸ', 'ਹ'] */

                            case 0xA59: 
                            case 0xA5A: 
                            case 0xA5B: 
                            case 0xA5C: goto _488;/* ['ਖ਼', 'ੜ'] */

                            case 0xA5E: goto _488;/* 'ਫ਼' */


                        }
                    }
                } else {
                    switch( input ) {
                        case 0xA72: 
                        case 0xA73: 
                        case 0xA74: goto _488;/* ['ੲ', 'ੴ'] */

                        case 0xA85: 
                        case 0xA86: 
                        case 0xA87: 
                        case 0xA88: 
                        case 0xA89: 
                        case 0xA8A: 
                        case 0xA8B: 
                        case 0xA8C: 
                        case 0xA8D: goto _488;/* ['અ', 'ઍ'] */

                        case 0xA8F: 
                        case 0xA90: 
                        case 0xA91: goto _488;/* ['એ', 'ઑ'] */

                        case 0xA93: 
                        case 0xA94: 
                        case 0xA95: 
                        case 0xA96: 
                        case 0xA97: 
                        case 0xA98: 
                        case 0xA99: 
                        case 0xA9A: 
                        case 0xA9B: 
                        case 0xA9C: 
                        case 0xA9D: 
                        case 0xA9E: 
                        case 0xA9F: 
                        case 0xAA0: 
                        case 0xAA1: 
                        case 0xAA2: 
                        case 0xAA3: 
                        case 0xAA4: 
                        case 0xAA5: 
                        case 0xAA6: 
                        case 0xAA7: 
                        case 0xAA8: goto _488;/* ['ઓ', 'ન'] */

                        case 0xAAA: 
                        case 0xAAB: 
                        case 0xAAC: 
                        case 0xAAD: 
                        case 0xAAE: 
                        case 0xAAF: 
                        case 0xAB0: goto _488;/* ['પ', 'ર'] */

                        case 0xAB2: 
                        case 0xAB3: goto _488;/* ['લ', 'ળ'] */

                        case 0xAB5: 
                        case 0xAB6: 
                        case 0xAB7: 
                        case 0xAB8: 
                        case 0xAB9: goto _488;/* ['વ', 'હ'] */

                        case 0xABD: goto _488;/* 'ઽ' */

                        case 0xAD0: goto _488;/* 'ૐ' */

                        case 0xAE0: 
                        case 0xAE1: goto _488;/* ['ૠ', 'ૡ'] */

                        case 0xB05: 
                        case 0xB06: 
                        case 0xB07: 
                        case 0xB08: 
                        case 0xB09: 
                        case 0xB0A: 
                        case 0xB0B: 
                        case 0xB0C: goto _488;/* ['ଅ', 'ଌ'] */

                        case 0xB0F: 
                        case 0xB10: goto _488;/* ['ଏ', 'ଐ'] */

                        case 0xB13: 
                        case 0xB14: 
                        case 0xB15: 
                        case 0xB16: 
                        case 0xB17: 
                        case 0xB18: 
                        case 0xB19: 
                        case 0xB1A: 
                        case 0xB1B: 
                        case 0xB1C: 
                        case 0xB1D: 
                        case 0xB1E: 
                        case 0xB1F: 
                        case 0xB20: 
                        case 0xB21: 
                        case 0xB22: 
                        case 0xB23: 
                        case 0xB24: 
                        case 0xB25: 
                        case 0xB26: 
                        case 0xB27: 
                        case 0xB28: goto _488;/* ['ଓ', 'ନ'] */

                        case 0xB2A: 
                        case 0xB2B: 
                        case 0xB2C: 
                        case 0xB2D: 
                        case 0xB2E: 
                        case 0xB2F: 
                        case 0xB30: goto _488;/* ['ପ', 'ର'] */

                        case 0xB32: 
                        case 0xB33: goto _488;/* ['ଲ', 'ଳ'] */

                        case 0xB35: 
                        case 0xB36: 
                        case 0xB37: 
                        case 0xB38: 
                        case 0xB39: goto _488;/* ['ଵ', 'ହ'] */

                        case 0xB3D: goto _488;/* 'ଽ' */

                        case 0xB5C: 
                        case 0xB5D: goto _488;/* ['ଡ଼', 'ଢ଼'] */

                        case 0xB5F: 
                        case 0xB60: 
                        case 0xB61: goto _488;/* ['ୟ', 'ୡ'] */

                        case 0xB71: goto _488;/* 'ୱ' */

                        case 0xB83: goto _488;/* 'ஃ' */

                        case 0xB85: 
                        case 0xB86: 
                        case 0xB87: 
                        case 0xB88: 
                        case 0xB89: 
                        case 0xB8A: goto _488;/* ['அ', 'ஊ'] */

                        case 0xB8E: 
                        case 0xB8F: 
                        case 0xB90: goto _488;/* ['எ', 'ஐ'] */

                        case 0xB92: 
                        case 0xB93: 
                        case 0xB94: 
                        case 0xB95: goto _488;/* ['ஒ', 'க'] */

                        case 0xB99: 
                        case 0xB9A: goto _488;/* ['ங', 'ச'] */

                        case 0xB9C: goto _488;/* 'ஜ' */

                        case 0xB9E: 
                        case 0xB9F: goto _488;/* ['ஞ', 'ட'] */

                        case 0xBA3: 
                        case 0xBA4: goto _488;/* ['ண', 'த'] */

                        case 0xBA8: 
                        case 0xBA9: 
                        case 0xBAA: goto _488;/* ['ந', 'ப'] */

                        case 0xBAE: 
                        case 0xBAF: 
                        case 0xBB0: 
                        case 0xBB1: 
                        case 0xBB2: 
                        case 0xBB3: 
                        case 0xBB4: 
                        case 0xBB5: 
                        case 0xBB6: 
                        case 0xBB7: 
                        case 0xBB8: 
                        case 0xBB9: goto _488;/* ['ம', 'ஹ'] */


                    }
                }
            }
        } else {
            if( input < 0x1071 ) {
                if( input < 0xE01 ) {
                    if( input < 0xCDE ) {
                        switch( input ) {
                            case 0xBD0: goto _488;/* 'ௐ' */

                            case 0xC05: 
                            case 0xC06: 
                            case 0xC07: 
                            case 0xC08: 
                            case 0xC09: 
                            case 0xC0A: 
                            case 0xC0B: 
                            case 0xC0C: goto _488;/* ['అ', 'ఌ'] */

                            case 0xC0E: 
                            case 0xC0F: 
                            case 0xC10: goto _488;/* ['ఎ', 'ఐ'] */

                            case 0xC12: 
                            case 0xC13: 
                            case 0xC14: 
                            case 0xC15: 
                            case 0xC16: 
                            case 0xC17: 
                            case 0xC18: 
                            case 0xC19: 
                            case 0xC1A: 
                            case 0xC1B: 
                            case 0xC1C: 
                            case 0xC1D: 
                            case 0xC1E: 
                            case 0xC1F: 
                            case 0xC20: 
                            case 0xC21: 
                            case 0xC22: 
                            case 0xC23: 
                            case 0xC24: 
                            case 0xC25: 
                            case 0xC26: 
                            case 0xC27: 
                            case 0xC28: goto _488;/* ['ఒ', 'న'] */

                            case 0xC2A: 
                            case 0xC2B: 
                            case 0xC2C: 
                            case 0xC2D: 
                            case 0xC2E: 
                            case 0xC2F: 
                            case 0xC30: 
                            case 0xC31: 
                            case 0xC32: 
                            case 0xC33: goto _488;/* ['ప', 'ళ'] */

                            case 0xC35: 
                            case 0xC36: 
                            case 0xC37: 
                            case 0xC38: 
                            case 0xC39: goto _488;/* ['వ', 'హ'] */

                            case 0xC3D: goto _488;/* 'ఽ' */

                            case 0xC58: 
                            case 0xC59: goto _488;/* ['ౘ', 'ౙ'] */

                            case 0xC60: 
                            case 0xC61: goto _488;/* ['ౠ', 'ౡ'] */

                            case 0xC85: 
                            case 0xC86: 
                            case 0xC87: 
                            case 0xC88: 
                            case 0xC89: 
                            case 0xC8A: 
                            case 0xC8B: 
                            case 0xC8C: goto _488;/* ['ಅ', 'ಌ'] */

                            case 0xC8E: 
                            case 0xC8F: 
                            case 0xC90: goto _488;/* ['ಎ', 'ಐ'] */

                            case 0xC92: 
                            case 0xC93: 
                            case 0xC94: 
                            case 0xC95: 
                            case 0xC96: 
                            case 0xC97: 
                            case 0xC98: 
                            case 0xC99: 
                            case 0xC9A: 
                            case 0xC9B: 
                            case 0xC9C: 
                            case 0xC9D: 
                            case 0xC9E: 
                            case 0xC9F: 
                            case 0xCA0: 
                            case 0xCA1: 
                            case 0xCA2: 
                            case 0xCA3: 
                            case 0xCA4: 
                            case 0xCA5: 
                            case 0xCA6: 
                            case 0xCA7: 
                            case 0xCA8: goto _488;/* ['ಒ', 'ನ'] */

                            case 0xCAA: 
                            case 0xCAB: 
                            case 0xCAC: 
                            case 0xCAD: 
                            case 0xCAE: 
                            case 0xCAF: 
                            case 0xCB0: 
                            case 0xCB1: 
                            case 0xCB2: 
                            case 0xCB3: goto _488;/* ['ಪ', 'ಳ'] */

                            case 0xCB5: 
                            case 0xCB6: 
                            case 0xCB7: 
                            case 0xCB8: 
                            case 0xCB9: goto _488;/* ['ವ', 'ಹ'] */

                            case 0xCBD: goto _488;/* 'ಽ' */


                        }
                    } else {
                        switch( input ) {
                            case 0xCDE: goto _488;/* 'ೞ' */

                            case 0xCE0: 
                            case 0xCE1: goto _488;/* ['ೠ', 'ೡ'] */

                            case 0xCF1: 
                            case 0xCF2: goto _488;/* ['ೱ', 'ೲ'] */

                            case 0xD05: 
                            case 0xD06: 
                            case 0xD07: 
                            case 0xD08: 
                            case 0xD09: 
                            case 0xD0A: 
                            case 0xD0B: 
                            case 0xD0C: goto _488;/* ['അ', 'ഌ'] */

                            case 0xD0E: 
                            case 0xD0F: 
                            case 0xD10: goto _488;/* ['എ', 'ഐ'] */

                            case 0xD12: 
                            case 0xD13: 
                            case 0xD14: 
                            case 0xD15: 
                            case 0xD16: 
                            case 0xD17: 
                            case 0xD18: 
                            case 0xD19: 
                            case 0xD1A: 
                            case 0xD1B: 
                            case 0xD1C: 
                            case 0xD1D: 
                            case 0xD1E: 
                            case 0xD1F: 
                            case 0xD20: 
                            case 0xD21: 
                            case 0xD22: 
                            case 0xD23: 
                            case 0xD24: 
                            case 0xD25: 
                            case 0xD26: 
                            case 0xD27: 
                            case 0xD28: 
                            case 0xD29: 
                            case 0xD2A: 
                            case 0xD2B: 
                            case 0xD2C: 
                            case 0xD2D: 
                            case 0xD2E: 
                            case 0xD2F: 
                            case 0xD30: 
                            case 0xD31: 
                            case 0xD32: 
                            case 0xD33: 
                            case 0xD34: 
                            case 0xD35: 
                            case 0xD36: 
                            case 0xD37: 
                            case 0xD38: 
                            case 0xD39: 
                            case 0xD3A: goto _488;/* ['ഒ', 'ഺ'] */

                            case 0xD3D: goto _488;/* 'ഽ' */

                            case 0xD4E: goto _488;/* 'ൎ' */

                            case 0xD60: 
                            case 0xD61: goto _488;/* ['ൠ', 'ൡ'] */

                            case 0xD7A: 
                            case 0xD7B: 
                            case 0xD7C: 
                            case 0xD7D: 
                            case 0xD7E: 
                            case 0xD7F: goto _488;/* ['ൺ', 'ൿ'] */

                            case 0xD85: 
                            case 0xD86: 
                            case 0xD87: 
                            case 0xD88: 
                            case 0xD89: 
                            case 0xD8A: 
                            case 0xD8B: 
                            case 0xD8C: 
                            case 0xD8D: 
                            case 0xD8E: 
                            case 0xD8F: 
                            case 0xD90: 
                            case 0xD91: 
                            case 0xD92: 
                            case 0xD93: 
                            case 0xD94: 
                            case 0xD95: 
                            case 0xD96: goto _488;/* ['අ', 'ඖ'] */

                            case 0xD9A: 
                            case 0xD9B: 
                            case 0xD9C: 
                            case 0xD9D: 
                            case 0xD9E: 
                            case 0xD9F: 
                            case 0xDA0: 
                            case 0xDA1: 
                            case 0xDA2: 
                            case 0xDA3: 
                            case 0xDA4: 
                            case 0xDA5: 
                            case 0xDA6: 
                            case 0xDA7: 
                            case 0xDA8: 
                            case 0xDA9: 
                            case 0xDAA: 
                            case 0xDAB: 
                            case 0xDAC: 
                            case 0xDAD: 
                            case 0xDAE: 
                            case 0xDAF: 
                            case 0xDB0: 
                            case 0xDB1: goto _488;/* ['ක', 'න'] */

                            case 0xDB3: 
                            case 0xDB4: 
                            case 0xDB5: 
                            case 0xDB6: 
                            case 0xDB7: 
                            case 0xDB8: 
                            case 0xDB9: 
                            case 0xDBA: 
                            case 0xDBB: goto _488;/* ['ඳ', 'ර'] */

                            case 0xDBD: goto _488;/* 'ල' */

                            case 0xDC0: 
                            case 0xDC1: 
                            case 0xDC2: 
                            case 0xDC3: 
                            case 0xDC4: 
                            case 0xDC5: 
                            case 0xDC6: goto _488;/* ['ව', 'ෆ'] */


                        }
                    }
                } else {
                    if( input < 0xEB2 ) {
                        switch( input ) {
                            case 0xE01: 
                            case 0xE02: 
                            case 0xE03: 
                            case 0xE04: 
                            case 0xE05: 
                            case 0xE06: 
                            case 0xE07: 
                            case 0xE08: 
                            case 0xE09: 
                            case 0xE0A: 
                            case 0xE0B: 
                            case 0xE0C: 
                            case 0xE0D: 
                            case 0xE0E: 
                            case 0xE0F: 
                            case 0xE10: 
                            case 0xE11: 
                            case 0xE12: 
                            case 0xE13: 
                            case 0xE14: 
                            case 0xE15: 
                            case 0xE16: 
                            case 0xE17: 
                            case 0xE18: 
                            case 0xE19: 
                            case 0xE1A: 
                            case 0xE1B: 
                            case 0xE1C: 
                            case 0xE1D: 
                            case 0xE1E: 
                            case 0xE1F: 
                            case 0xE20: 
                            case 0xE21: 
                            case 0xE22: 
                            case 0xE23: 
                            case 0xE24: 
                            case 0xE25: 
                            case 0xE26: 
                            case 0xE27: 
                            case 0xE28: 
                            case 0xE29: 
                            case 0xE2A: 
                            case 0xE2B: 
                            case 0xE2C: 
                            case 0xE2D: 
                            case 0xE2E: 
                            case 0xE2F: 
                            case 0xE30: goto _488;/* ['ก', 'ะ'] */

                            case 0xE32: goto _488;/* 'า' */

                            case 0xE40: 
                            case 0xE41: 
                            case 0xE42: 
                            case 0xE43: 
                            case 0xE44: 
                            case 0xE45: 
                            case 0xE46: goto _488;/* ['เ', 'ๆ'] */

                            case 0xE81: 
                            case 0xE82: goto _488;/* ['ກ', 'ຂ'] */

                            case 0xE84: goto _488;/* 'ຄ' */

                            case 0xE87: 
                            case 0xE88: goto _488;/* ['ງ', 'ຈ'] */

                            case 0xE8A: goto _488;/* 'ຊ' */

                            case 0xE8D: goto _488;/* 'ຍ' */

                            case 0xE94: 
                            case 0xE95: 
                            case 0xE96: 
                            case 0xE97: goto _488;/* ['ດ', 'ທ'] */

                            case 0xE99: 
                            case 0xE9A: 
                            case 0xE9B: 
                            case 0xE9C: 
                            case 0xE9D: 
                            case 0xE9E: 
                            case 0xE9F: goto _488;/* ['ນ', 'ຟ'] */

                            case 0xEA1: 
                            case 0xEA2: 
                            case 0xEA3: goto _488;/* ['ມ', 'ຣ'] */

                            case 0xEA5: goto _488;/* 'ລ' */

                            case 0xEA7: goto _488;/* 'ວ' */

                            case 0xEAA: 
                            case 0xEAB: goto _488;/* ['ສ', 'ຫ'] */

                            case 0xEAD: 
                            case 0xEAE: 
                            case 0xEAF: 
                            case 0xEB0: goto _488;/* ['ອ', 'ະ'] */


                        }
                    } else {
                        switch( input ) {
                            case 0xEB2: goto _488;/* 'າ' */

                            case 0xEBD: goto _488;/* 'ຽ' */

                            case 0xEC0: 
                            case 0xEC1: 
                            case 0xEC2: 
                            case 0xEC3: 
                            case 0xEC4: goto _488;/* ['ເ', 'ໄ'] */

                            case 0xEC6: goto _488;/* 'ໆ' */

                            case 0xEDC: 
                            case 0xEDD: goto _488;/* ['ໜ', 'ໝ'] */

                            case 0xF00: goto _488;/* 'ༀ' */

                            case 0xF40: 
                            case 0xF41: 
                            case 0xF42: 
                            case 0xF43: 
                            case 0xF44: 
                            case 0xF45: 
                            case 0xF46: 
                            case 0xF47: goto _488;/* ['ཀ', 'ཇ'] */

                            case 0xF49: 
                            case 0xF4A: 
                            case 0xF4B: 
                            case 0xF4C: 
                            case 0xF4D: 
                            case 0xF4E: 
                            case 0xF4F: 
                            case 0xF50: 
                            case 0xF51: 
                            case 0xF52: 
                            case 0xF53: 
                            case 0xF54: 
                            case 0xF55: 
                            case 0xF56: 
                            case 0xF57: 
                            case 0xF58: 
                            case 0xF59: 
                            case 0xF5A: 
                            case 0xF5B: 
                            case 0xF5C: 
                            case 0xF5D: 
                            case 0xF5E: 
                            case 0xF5F: 
                            case 0xF60: 
                            case 0xF61: 
                            case 0xF62: 
                            case 0xF63: 
                            case 0xF64: 
                            case 0xF65: 
                            case 0xF66: 
                            case 0xF67: 
                            case 0xF68: 
                            case 0xF69: 
                            case 0xF6A: 
                            case 0xF6B: 
                            case 0xF6C: goto _488;/* ['ཉ', 'ཬ'] */

                            case 0xF88: 
                            case 0xF89: 
                            case 0xF8A: 
                            case 0xF8B: 
                            case 0xF8C: goto _488;/* ['ྈ', 'ྌ'] */

                            case 0x1000: 
                            case 0x1001: 
                            case 0x1002: 
                            case 0x1003: 
                            case 0x1004: 
                            case 0x1005: 
                            case 0x1006: 
                            case 0x1007: 
                            case 0x1008: 
                            case 0x1009: 
                            case 0x100A: 
                            case 0x100B: 
                            case 0x100C: 
                            case 0x100D: 
                            case 0x100E: 
                            case 0x100F: 
                            case 0x1010: 
                            case 0x1011: 
                            case 0x1012: 
                            case 0x1013: 
                            case 0x1014: 
                            case 0x1015: 
                            case 0x1016: 
                            case 0x1017: 
                            case 0x1018: 
                            case 0x1019: 
                            case 0x101A: 
                            case 0x101B: 
                            case 0x101C: 
                            case 0x101D: 
                            case 0x101E: 
                            case 0x101F: 
                            case 0x1020: 
                            case 0x1021: 
                            case 0x1022: 
                            case 0x1023: 
                            case 0x1024: 
                            case 0x1025: 
                            case 0x1026: 
                            case 0x1027: 
                            case 0x1028: 
                            case 0x1029: 
                            case 0x102A: goto _488;/* ['က', 'ဪ'] */

                            case 0x103F: goto _488;/* 'ဿ' */

                            case 0x1050: 
                            case 0x1051: 
                            case 0x1052: 
                            case 0x1053: 
                            case 0x1054: 
                            case 0x1055: goto _488;/* ['ၐ', 'ၕ'] */

                            case 0x105A: 
                            case 0x105B: 
                            case 0x105C: 
                            case 0x105D: goto _488;/* ['ၚ', 'ၝ'] */

                            case 0x1061: goto _488;/* 'ၡ' */

                            case 0x1065: 
                            case 0x1066: goto _488;/* ['ၥ', 'ၦ'] */

                            case 0x106E: 
                            case 0x106F: 
                            case 0x1070: goto _488;/* ['ၮ', 'ၰ'] */


                        }
                    }
                }
            } else {
                if( input < 0x1712 ) {
                    if( input < 0x12BF ) {
                        if( input < 0x1250 ) {
                            if( input < 0x10D0 ) {
                                switch( input ) {
                                    case 0x1075: 
                                    case 0x1076: 
                                    case 0x1077: 
                                    case 0x1078: 
                                    case 0x1079: 
                                    case 0x107A: 
                                    case 0x107B: 
                                    case 0x107C: 
                                    case 0x107D: 
                                    case 0x107E: 
                                    case 0x107F: 
                                    case 0x1080: 
                                    case 0x1081: goto _488;/* ['ၵ', 'ႁ'] */

                                    case 0x108E: goto _488;/* 'ႎ' */

                                    case 0x10A0: 
                                    case 0x10A1: 
                                    case 0x10A2: 
                                    case 0x10A3: 
                                    case 0x10A4: 
                                    case 0x10A5: 
                                    case 0x10A6: 
                                    case 0x10A7: 
                                    case 0x10A8: 
                                    case 0x10A9: 
                                    case 0x10AA: 
                                    case 0x10AB: 
                                    case 0x10AC: 
                                    case 0x10AD: 
                                    case 0x10AE: 
                                    case 0x10AF: 
                                    case 0x10B0: 
                                    case 0x10B1: 
                                    case 0x10B2: 
                                    case 0x10B3: 
                                    case 0x10B4: 
                                    case 0x10B5: 
                                    case 0x10B6: 
                                    case 0x10B7: 
                                    case 0x10B8: 
                                    case 0x10B9: 
                                    case 0x10BA: 
                                    case 0x10BB: 
                                    case 0x10BC: 
                                    case 0x10BD: 
                                    case 0x10BE: 
                                    case 0x10BF: 
                                    case 0x10C0: 
                                    case 0x10C1: 
                                    case 0x10C2: 
                                    case 0x10C3: 
                                    case 0x10C4: 
                                    case 0x10C5: goto _488;/* ['Ⴀ', 'Ⴥ'] */


                                }
                            } else {
                                if( input < 0x1100 ) {
                                    switch( input ) {
                                        case 0x10D0: 
                                        case 0x10D1: 
                                        case 0x10D2: 
                                        case 0x10D3: 
                                        case 0x10D4: 
                                        case 0x10D5: 
                                        case 0x10D6: 
                                        case 0x10D7: 
                                        case 0x10D8: 
                                        case 0x10D9: 
                                        case 0x10DA: 
                                        case 0x10DB: 
                                        case 0x10DC: 
                                        case 0x10DD: 
                                        case 0x10DE: 
                                        case 0x10DF: 
                                        case 0x10E0: 
                                        case 0x10E1: 
                                        case 0x10E2: 
                                        case 0x10E3: 
                                        case 0x10E4: 
                                        case 0x10E5: 
                                        case 0x10E6: 
                                        case 0x10E7: 
                                        case 0x10E8: 
                                        case 0x10E9: 
                                        case 0x10EA: 
                                        case 0x10EB: 
                                        case 0x10EC: 
                                        case 0x10ED: 
                                        case 0x10EE: 
                                        case 0x10EF: 
                                        case 0x10F0: 
                                        case 0x10F1: 
                                        case 0x10F2: 
                                        case 0x10F3: 
                                        case 0x10F4: 
                                        case 0x10F5: 
                                        case 0x10F6: 
                                        case 0x10F7: 
                                        case 0x10F8: 
                                        case 0x10F9: 
                                        case 0x10FA: goto _488;/* ['ა', 'ჺ'] */

                                        case 0x10FC: goto _488;/* 'ჼ' */


                                    }
                                } else {
                                    if( input < 0x1249 ) {
                                        goto _488;/* ['ᄀ', 'ቈ'] */

                                    } else if( input == 0x1249 ) {

                                    } else if( input < 0x124E ) {
                                        goto _488;/* ['ቊ', 'ቍ'] */

                                    } else {

                                    }
                                }
                            }
                        } else {
                            switch( input ) {
                                case 0x1250: 
                                case 0x1251: 
                                case 0x1252: 
                                case 0x1253: 
                                case 0x1254: 
                                case 0x1255: 
                                case 0x1256: goto _488;/* ['ቐ', 'ቖ'] */

                                case 0x1258: goto _488;/* 'ቘ' */

                                case 0x125A: 
                                case 0x125B: 
                                case 0x125C: 
                                case 0x125D: goto _488;/* ['ቚ', 'ቝ'] */

                                case 0x1260: 
                                case 0x1261: 
                                case 0x1262: 
                                case 0x1263: 
                                case 0x1264: 
                                case 0x1265: 
                                case 0x1266: 
                                case 0x1267: 
                                case 0x1268: 
                                case 0x1269: 
                                case 0x126A: 
                                case 0x126B: 
                                case 0x126C: 
                                case 0x126D: 
                                case 0x126E: 
                                case 0x126F: 
                                case 0x1270: 
                                case 0x1271: 
                                case 0x1272: 
                                case 0x1273: 
                                case 0x1274: 
                                case 0x1275: 
                                case 0x1276: 
                                case 0x1277: 
                                case 0x1278: 
                                case 0x1279: 
                                case 0x127A: 
                                case 0x127B: 
                                case 0x127C: 
                                case 0x127D: 
                                case 0x127E: 
                                case 0x127F: 
                                case 0x1280: 
                                case 0x1281: 
                                case 0x1282: 
                                case 0x1283: 
                                case 0x1284: 
                                case 0x1285: 
                                case 0x1286: 
                                case 0x1287: 
                                case 0x1288: goto _488;/* ['በ', 'ኈ'] */

                                case 0x128A: 
                                case 0x128B: 
                                case 0x128C: 
                                case 0x128D: goto _488;/* ['ኊ', 'ኍ'] */

                                case 0x1290: 
                                case 0x1291: 
                                case 0x1292: 
                                case 0x1293: 
                                case 0x1294: 
                                case 0x1295: 
                                case 0x1296: 
                                case 0x1297: 
                                case 0x1298: 
                                case 0x1299: 
                                case 0x129A: 
                                case 0x129B: 
                                case 0x129C: 
                                case 0x129D: 
                                case 0x129E: 
                                case 0x129F: 
                                case 0x12A0: 
                                case 0x12A1: 
                                case 0x12A2: 
                                case 0x12A3: 
                                case 0x12A4: 
                                case 0x12A5: 
                                case 0x12A6: 
                                case 0x12A7: 
                                case 0x12A8: 
                                case 0x12A9: 
                                case 0x12AA: 
                                case 0x12AB: 
                                case 0x12AC: 
                                case 0x12AD: 
                                case 0x12AE: 
                                case 0x12AF: 
                                case 0x12B0: goto _488;/* ['ነ', 'ኰ'] */

                                case 0x12B2: 
                                case 0x12B3: 
                                case 0x12B4: 
                                case 0x12B5: goto _488;/* ['ኲ', 'ኵ'] */

                                case 0x12B8: 
                                case 0x12B9: 
                                case 0x12BA: 
                                case 0x12BB: 
                                case 0x12BC: 
                                case 0x12BD: 
                                case 0x12BE: goto _488;/* ['ኸ', 'ኾ'] */


                            }
                        }
                    } else {
                        if( input < 0x13A0 ) {
                            if( input < 0x12D8 ) {
                                switch( input ) {
                                    case 0x12C0: goto _488;/* 'ዀ' */

                                    case 0x12C2: 
                                    case 0x12C3: 
                                    case 0x12C4: 
                                    case 0x12C5: goto _488;/* ['ዂ', 'ዅ'] */

                                    case 0x12C8: 
                                    case 0x12C9: 
                                    case 0x12CA: 
                                    case 0x12CB: 
                                    case 0x12CC: 
                                    case 0x12CD: 
                                    case 0x12CE: 
                                    case 0x12CF: 
                                    case 0x12D0: 
                                    case 0x12D1: 
                                    case 0x12D2: 
                                    case 0x12D3: 
                                    case 0x12D4: 
                                    case 0x12D5: 
                                    case 0x12D6: goto _488;/* ['ወ', 'ዖ'] */


                                }
                            } else {
                                if( input < 0x1318 ) {
                                    switch( input ) {
                                        case 0x12D8: 
                                        case 0x12D9: 
                                        case 0x12DA: 
                                        case 0x12DB: 
                                        case 0x12DC: 
                                        case 0x12DD: 
                                        case 0x12DE: 
                                        case 0x12DF: 
                                        case 0x12E0: 
                                        case 0x12E1: 
                                        case 0x12E2: 
                                        case 0x12E3: 
                                        case 0x12E4: 
                                        case 0x12E5: 
                                        case 0x12E6: 
                                        case 0x12E7: 
                                        case 0x12E8: 
                                        case 0x12E9: 
                                        case 0x12EA: 
                                        case 0x12EB: 
                                        case 0x12EC: 
                                        case 0x12ED: 
                                        case 0x12EE: 
                                        case 0x12EF: 
                                        case 0x12F0: 
                                        case 0x12F1: 
                                        case 0x12F2: 
                                        case 0x12F3: 
                                        case 0x12F4: 
                                        case 0x12F5: 
                                        case 0x12F6: 
                                        case 0x12F7: 
                                        case 0x12F8: 
                                        case 0x12F9: 
                                        case 0x12FA: 
                                        case 0x12FB: 
                                        case 0x12FC: 
                                        case 0x12FD: 
                                        case 0x12FE: 
                                        case 0x12FF: 
                                        case 0x1300: 
                                        case 0x1301: 
                                        case 0x1302: 
                                        case 0x1303: 
                                        case 0x1304: 
                                        case 0x1305: 
                                        case 0x1306: 
                                        case 0x1307: 
                                        case 0x1308: 
                                        case 0x1309: 
                                        case 0x130A: 
                                        case 0x130B: 
                                        case 0x130C: 
                                        case 0x130D: 
                                        case 0x130E: 
                                        case 0x130F: 
                                        case 0x1310: goto _488;/* ['ዘ', 'ጐ'] */

                                        case 0x1312: 
                                        case 0x1313: 
                                        case 0x1314: 
                                        case 0x1315: goto _488;/* ['ጒ', 'ጕ'] */


                                    }
                                } else {
                                    if( input < 0x135B ) {
                                        goto _488;/* ['ጘ', 'ፚ'] */

                                    } else if( input < 0x1380 ) {

                                    } else if( input < 0x1390 ) {
                                        goto _488;/* ['ᎀ', 'ᎏ'] */

                                    } else {

                                    }
                                }
                            }
                        } else {
                            if( input < 0x169B ) {
                                if( input < 0x166D ) {
                                    if( input < 0x13F5 ) {
                                        goto _488;/* ['Ꭰ', 'Ᏼ'] */

                                    } else if( input < 0x1401 ) {

                                    } else {
                                        goto _488;/* ['ᐁ', 'ᙬ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x166F: 
                                        case 0x1670: 
                                        case 0x1671: 
                                        case 0x1672: 
                                        case 0x1673: 
                                        case 0x1674: 
                                        case 0x1675: 
                                        case 0x1676: 
                                        case 0x1677: 
                                        case 0x1678: 
                                        case 0x1679: 
                                        case 0x167A: 
                                        case 0x167B: 
                                        case 0x167C: 
                                        case 0x167D: 
                                        case 0x167E: 
                                        case 0x167F: goto _488;/* ['ᙯ', 'ᙿ'] */

                                        case 0x1680: goto _465;/* ' ' */

                                        case 0x1681: 
                                        case 0x1682: 
                                        case 0x1683: 
                                        case 0x1684: 
                                        case 0x1685: 
                                        case 0x1686: 
                                        case 0x1687: 
                                        case 0x1688: 
                                        case 0x1689: 
                                        case 0x168A: 
                                        case 0x168B: 
                                        case 0x168C: 
                                        case 0x168D: 
                                        case 0x168E: 
                                        case 0x168F: 
                                        case 0x1690: 
                                        case 0x1691: 
                                        case 0x1692: 
                                        case 0x1693: 
                                        case 0x1694: 
                                        case 0x1695: 
                                        case 0x1696: 
                                        case 0x1697: 
                                        case 0x1698: 
                                        case 0x1699: 
                                        case 0x169A: goto _488;/* ['ᚁ', 'ᚚ'] */


                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x16A0: 
                                    case 0x16A1: 
                                    case 0x16A2: 
                                    case 0x16A3: 
                                    case 0x16A4: 
                                    case 0x16A5: 
                                    case 0x16A6: 
                                    case 0x16A7: 
                                    case 0x16A8: 
                                    case 0x16A9: 
                                    case 0x16AA: 
                                    case 0x16AB: 
                                    case 0x16AC: 
                                    case 0x16AD: 
                                    case 0x16AE: 
                                    case 0x16AF: 
                                    case 0x16B0: 
                                    case 0x16B1: 
                                    case 0x16B2: 
                                    case 0x16B3: 
                                    case 0x16B4: 
                                    case 0x16B5: 
                                    case 0x16B6: 
                                    case 0x16B7: 
                                    case 0x16B8: 
                                    case 0x16B9: 
                                    case 0x16BA: 
                                    case 0x16BB: 
                                    case 0x16BC: 
                                    case 0x16BD: 
                                    case 0x16BE: 
                                    case 0x16BF: 
                                    case 0x16C0: 
                                    case 0x16C1: 
                                    case 0x16C2: 
                                    case 0x16C3: 
                                    case 0x16C4: 
                                    case 0x16C5: 
                                    case 0x16C6: 
                                    case 0x16C7: 
                                    case 0x16C8: 
                                    case 0x16C9: 
                                    case 0x16CA: 
                                    case 0x16CB: 
                                    case 0x16CC: 
                                    case 0x16CD: 
                                    case 0x16CE: 
                                    case 0x16CF: 
                                    case 0x16D0: 
                                    case 0x16D1: 
                                    case 0x16D2: 
                                    case 0x16D3: 
                                    case 0x16D4: 
                                    case 0x16D5: 
                                    case 0x16D6: 
                                    case 0x16D7: 
                                    case 0x16D8: 
                                    case 0x16D9: 
                                    case 0x16DA: 
                                    case 0x16DB: 
                                    case 0x16DC: 
                                    case 0x16DD: 
                                    case 0x16DE: 
                                    case 0x16DF: 
                                    case 0x16E0: 
                                    case 0x16E1: 
                                    case 0x16E2: 
                                    case 0x16E3: 
                                    case 0x16E4: 
                                    case 0x16E5: 
                                    case 0x16E6: 
                                    case 0x16E7: 
                                    case 0x16E8: 
                                    case 0x16E9: 
                                    case 0x16EA: goto _488;/* ['ᚠ', 'ᛪ'] */

                                    case 0x16EE: 
                                    case 0x16EF: 
                                    case 0x16F0: goto _488;/* ['ᛮ', 'ᛰ'] */

                                    case 0x1700: 
                                    case 0x1701: 
                                    case 0x1702: 
                                    case 0x1703: 
                                    case 0x1704: 
                                    case 0x1705: 
                                    case 0x1706: 
                                    case 0x1707: 
                                    case 0x1708: 
                                    case 0x1709: 
                                    case 0x170A: 
                                    case 0x170B: 
                                    case 0x170C: goto _488;/* ['ᜀ', 'ᜌ'] */

                                    case 0x170E: 
                                    case 0x170F: 
                                    case 0x1710: 
                                    case 0x1711: goto _488;/* ['ᜎ', 'ᜑ'] */


                                }
                            }
                        }
                    }
                } else {
                    if( input < 0x1975 ) {
                        if( input < 0x180E ) {
                            switch( input ) {
                                case 0x1720: 
                                case 0x1721: 
                                case 0x1722: 
                                case 0x1723: 
                                case 0x1724: 
                                case 0x1725: 
                                case 0x1726: 
                                case 0x1727: 
                                case 0x1728: 
                                case 0x1729: 
                                case 0x172A: 
                                case 0x172B: 
                                case 0x172C: 
                                case 0x172D: 
                                case 0x172E: 
                                case 0x172F: 
                                case 0x1730: 
                                case 0x1731: goto _488;/* ['ᜠ', 'ᜱ'] */

                                case 0x1740: 
                                case 0x1741: 
                                case 0x1742: 
                                case 0x1743: 
                                case 0x1744: 
                                case 0x1745: 
                                case 0x1746: 
                                case 0x1747: 
                                case 0x1748: 
                                case 0x1749: 
                                case 0x174A: 
                                case 0x174B: 
                                case 0x174C: 
                                case 0x174D: 
                                case 0x174E: 
                                case 0x174F: 
                                case 0x1750: 
                                case 0x1751: goto _488;/* ['ᝀ', 'ᝑ'] */

                                case 0x1760: 
                                case 0x1761: 
                                case 0x1762: 
                                case 0x1763: 
                                case 0x1764: 
                                case 0x1765: 
                                case 0x1766: 
                                case 0x1767: 
                                case 0x1768: 
                                case 0x1769: 
                                case 0x176A: 
                                case 0x176B: 
                                case 0x176C: goto _488;/* ['ᝠ', 'ᝬ'] */

                                case 0x176E: 
                                case 0x176F: 
                                case 0x1770: goto _488;/* ['ᝮ', 'ᝰ'] */

                                case 0x1780: 
                                case 0x1781: 
                                case 0x1782: 
                                case 0x1783: 
                                case 0x1784: 
                                case 0x1785: 
                                case 0x1786: 
                                case 0x1787: 
                                case 0x1788: 
                                case 0x1789: 
                                case 0x178A: 
                                case 0x178B: 
                                case 0x178C: 
                                case 0x178D: 
                                case 0x178E: 
                                case 0x178F: 
                                case 0x1790: 
                                case 0x1791: 
                                case 0x1792: 
                                case 0x1793: 
                                case 0x1794: 
                                case 0x1795: 
                                case 0x1796: 
                                case 0x1797: 
                                case 0x1798: 
                                case 0x1799: 
                                case 0x179A: 
                                case 0x179B: 
                                case 0x179C: 
                                case 0x179D: 
                                case 0x179E: 
                                case 0x179F: 
                                case 0x17A0: 
                                case 0x17A1: 
                                case 0x17A2: 
                                case 0x17A3: 
                                case 0x17A4: 
                                case 0x17A5: 
                                case 0x17A6: 
                                case 0x17A7: 
                                case 0x17A8: 
                                case 0x17A9: 
                                case 0x17AA: 
                                case 0x17AB: 
                                case 0x17AC: 
                                case 0x17AD: 
                                case 0x17AE: 
                                case 0x17AF: 
                                case 0x17B0: 
                                case 0x17B1: 
                                case 0x17B2: 
                                case 0x17B3: goto _488;/* ['ក', 'ឳ'] */

                                case 0x17D7: goto _488;/* 'ៗ' */

                                case 0x17DC: goto _488;/* 'ៜ' */


                            }
                        } else {
                            if( input < 0x18AB ) {
                                if( input < 0x1878 ) {
                                    if( input == 0x180E ) {
                                        goto _465;/* '᠎' */

                                    } else if( input < 0x1820 ) {

                                    } else {
                                        goto _488;/* ['ᠠ', 'ᡷ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1880: 
                                        case 0x1881: 
                                        case 0x1882: 
                                        case 0x1883: 
                                        case 0x1884: 
                                        case 0x1885: 
                                        case 0x1886: 
                                        case 0x1887: 
                                        case 0x1888: 
                                        case 0x1889: 
                                        case 0x188A: 
                                        case 0x188B: 
                                        case 0x188C: 
                                        case 0x188D: 
                                        case 0x188E: 
                                        case 0x188F: 
                                        case 0x1890: 
                                        case 0x1891: 
                                        case 0x1892: 
                                        case 0x1893: 
                                        case 0x1894: 
                                        case 0x1895: 
                                        case 0x1896: 
                                        case 0x1897: 
                                        case 0x1898: 
                                        case 0x1899: 
                                        case 0x189A: 
                                        case 0x189B: 
                                        case 0x189C: 
                                        case 0x189D: 
                                        case 0x189E: 
                                        case 0x189F: 
                                        case 0x18A0: 
                                        case 0x18A1: 
                                        case 0x18A2: 
                                        case 0x18A3: 
                                        case 0x18A4: 
                                        case 0x18A5: 
                                        case 0x18A6: 
                                        case 0x18A7: 
                                        case 0x18A8: goto _488;/* ['ᢀ', 'ᢨ'] */

                                        case 0x18AA: goto _488;/* 'ᢪ' */


                                    }
                                }
                            } else {
                                if( input < 0x191D ) {
                                    if( input < 0x18B0 ) {

                                    } else if( input < 0x18F6 ) {
                                        goto _488;/* ['ᢰ', 'ᣵ'] */

                                    } else if( input < 0x1900 ) {

                                    } else {
                                        goto _488;/* ['ᤀ', 'ᤜ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1950: 
                                        case 0x1951: 
                                        case 0x1952: 
                                        case 0x1953: 
                                        case 0x1954: 
                                        case 0x1955: 
                                        case 0x1956: 
                                        case 0x1957: 
                                        case 0x1958: 
                                        case 0x1959: 
                                        case 0x195A: 
                                        case 0x195B: 
                                        case 0x195C: 
                                        case 0x195D: 
                                        case 0x195E: 
                                        case 0x195F: 
                                        case 0x1960: 
                                        case 0x1961: 
                                        case 0x1962: 
                                        case 0x1963: 
                                        case 0x1964: 
                                        case 0x1965: 
                                        case 0x1966: 
                                        case 0x1967: 
                                        case 0x1968: 
                                        case 0x1969: 
                                        case 0x196A: 
                                        case 0x196B: 
                                        case 0x196C: 
                                        case 0x196D: goto _488;/* ['ᥐ', 'ᥭ'] */

                                        case 0x1970: 
                                        case 0x1971: 
                                        case 0x1972: 
                                        case 0x1973: 
                                        case 0x1974: goto _488;/* ['ᥰ', 'ᥴ'] */


                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0x1B83 ) {
                            if( input < 0x1A20 ) {
                                switch( input ) {
                                    case 0x1980: 
                                    case 0x1981: 
                                    case 0x1982: 
                                    case 0x1983: 
                                    case 0x1984: 
                                    case 0x1985: 
                                    case 0x1986: 
                                    case 0x1987: 
                                    case 0x1988: 
                                    case 0x1989: 
                                    case 0x198A: 
                                    case 0x198B: 
                                    case 0x198C: 
                                    case 0x198D: 
                                    case 0x198E: 
                                    case 0x198F: 
                                    case 0x1990: 
                                    case 0x1991: 
                                    case 0x1992: 
                                    case 0x1993: 
                                    case 0x1994: 
                                    case 0x1995: 
                                    case 0x1996: 
                                    case 0x1997: 
                                    case 0x1998: 
                                    case 0x1999: 
                                    case 0x199A: 
                                    case 0x199B: 
                                    case 0x199C: 
                                    case 0x199D: 
                                    case 0x199E: 
                                    case 0x199F: 
                                    case 0x19A0: 
                                    case 0x19A1: 
                                    case 0x19A2: 
                                    case 0x19A3: 
                                    case 0x19A4: 
                                    case 0x19A5: 
                                    case 0x19A6: 
                                    case 0x19A7: 
                                    case 0x19A8: 
                                    case 0x19A9: 
                                    case 0x19AA: 
                                    case 0x19AB: goto _488;/* ['ᦀ', 'ᦫ'] */

                                    case 0x19C1: 
                                    case 0x19C2: 
                                    case 0x19C3: 
                                    case 0x19C4: 
                                    case 0x19C5: 
                                    case 0x19C6: 
                                    case 0x19C7: goto _488;/* ['ᧁ', 'ᧇ'] */

                                    case 0x1A00: 
                                    case 0x1A01: 
                                    case 0x1A02: 
                                    case 0x1A03: 
                                    case 0x1A04: 
                                    case 0x1A05: 
                                    case 0x1A06: 
                                    case 0x1A07: 
                                    case 0x1A08: 
                                    case 0x1A09: 
                                    case 0x1A0A: 
                                    case 0x1A0B: 
                                    case 0x1A0C: 
                                    case 0x1A0D: 
                                    case 0x1A0E: 
                                    case 0x1A0F: 
                                    case 0x1A10: 
                                    case 0x1A11: 
                                    case 0x1A12: 
                                    case 0x1A13: 
                                    case 0x1A14: 
                                    case 0x1A15: 
                                    case 0x1A16: goto _488;/* ['ᨀ', 'ᨖ'] */


                                }
                            } else {
                                if( input < 0x1B05 ) {
                                    switch( input ) {
                                        case 0x1A20: 
                                        case 0x1A21: 
                                        case 0x1A22: 
                                        case 0x1A23: 
                                        case 0x1A24: 
                                        case 0x1A25: 
                                        case 0x1A26: 
                                        case 0x1A27: 
                                        case 0x1A28: 
                                        case 0x1A29: 
                                        case 0x1A2A: 
                                        case 0x1A2B: 
                                        case 0x1A2C: 
                                        case 0x1A2D: 
                                        case 0x1A2E: 
                                        case 0x1A2F: 
                                        case 0x1A30: 
                                        case 0x1A31: 
                                        case 0x1A32: 
                                        case 0x1A33: 
                                        case 0x1A34: 
                                        case 0x1A35: 
                                        case 0x1A36: 
                                        case 0x1A37: 
                                        case 0x1A38: 
                                        case 0x1A39: 
                                        case 0x1A3A: 
                                        case 0x1A3B: 
                                        case 0x1A3C: 
                                        case 0x1A3D: 
                                        case 0x1A3E: 
                                        case 0x1A3F: 
                                        case 0x1A40: 
                                        case 0x1A41: 
                                        case 0x1A42: 
                                        case 0x1A43: 
                                        case 0x1A44: 
                                        case 0x1A45: 
                                        case 0x1A46: 
                                        case 0x1A47: 
                                        case 0x1A48: 
                                        case 0x1A49: 
                                        case 0x1A4A: 
                                        case 0x1A4B: 
                                        case 0x1A4C: 
                                        case 0x1A4D: 
                                        case 0x1A4E: 
                                        case 0x1A4F: 
                                        case 0x1A50: 
                                        case 0x1A51: 
                                        case 0x1A52: 
                                        case 0x1A53: 
                                        case 0x1A54: goto _488;/* ['ᨠ', 'ᩔ'] */

                                        case 0x1AA7: goto _488;/* 'ᪧ' */


                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1B05: 
                                        case 0x1B06: 
                                        case 0x1B07: 
                                        case 0x1B08: 
                                        case 0x1B09: 
                                        case 0x1B0A: 
                                        case 0x1B0B: 
                                        case 0x1B0C: 
                                        case 0x1B0D: 
                                        case 0x1B0E: 
                                        case 0x1B0F: 
                                        case 0x1B10: 
                                        case 0x1B11: 
                                        case 0x1B12: 
                                        case 0x1B13: 
                                        case 0x1B14: 
                                        case 0x1B15: 
                                        case 0x1B16: 
                                        case 0x1B17: 
                                        case 0x1B18: 
                                        case 0x1B19: 
                                        case 0x1B1A: 
                                        case 0x1B1B: 
                                        case 0x1B1C: 
                                        case 0x1B1D: 
                                        case 0x1B1E: 
                                        case 0x1B1F: 
                                        case 0x1B20: 
                                        case 0x1B21: 
                                        case 0x1B22: 
                                        case 0x1B23: 
                                        case 0x1B24: 
                                        case 0x1B25: 
                                        case 0x1B26: 
                                        case 0x1B27: 
                                        case 0x1B28: 
                                        case 0x1B29: 
                                        case 0x1B2A: 
                                        case 0x1B2B: 
                                        case 0x1B2C: 
                                        case 0x1B2D: 
                                        case 0x1B2E: 
                                        case 0x1B2F: 
                                        case 0x1B30: 
                                        case 0x1B31: 
                                        case 0x1B32: 
                                        case 0x1B33: goto _488;/* ['ᬅ', 'ᬳ'] */

                                        case 0x1B45: 
                                        case 0x1B46: 
                                        case 0x1B47: 
                                        case 0x1B48: 
                                        case 0x1B49: 
                                        case 0x1B4A: 
                                        case 0x1B4B: goto _488;/* ['ᭅ', 'ᭋ'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0x1C4D ) {
                                if( input < 0x1BC0 ) {
                                    switch( input ) {
                                        case 0x1B83: 
                                        case 0x1B84: 
                                        case 0x1B85: 
                                        case 0x1B86: 
                                        case 0x1B87: 
                                        case 0x1B88: 
                                        case 0x1B89: 
                                        case 0x1B8A: 
                                        case 0x1B8B: 
                                        case 0x1B8C: 
                                        case 0x1B8D: 
                                        case 0x1B8E: 
                                        case 0x1B8F: 
                                        case 0x1B90: 
                                        case 0x1B91: 
                                        case 0x1B92: 
                                        case 0x1B93: 
                                        case 0x1B94: 
                                        case 0x1B95: 
                                        case 0x1B96: 
                                        case 0x1B97: 
                                        case 0x1B98: 
                                        case 0x1B99: 
                                        case 0x1B9A: 
                                        case 0x1B9B: 
                                        case 0x1B9C: 
                                        case 0x1B9D: 
                                        case 0x1B9E: 
                                        case 0x1B9F: 
                                        case 0x1BA0: goto _488;/* ['ᮃ', 'ᮠ'] */

                                        case 0x1BAE: 
                                        case 0x1BAF: goto _488;/* ['ᮮ', 'ᮯ'] */


                                    }
                                } else {
                                    if( input < 0x1BE6 ) {
                                        goto _488;/* ['ᯀ', 'ᯥ'] */

                                    } else if( input < 0x1C00 ) {

                                    } else if( input < 0x1C24 ) {
                                        goto _488;/* ['ᰀ', 'ᰣ'] */

                                    } else {

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x1C4D: 
                                    case 0x1C4E: 
                                    case 0x1C4F: goto _488;/* ['ᱍ', 'ᱏ'] */

                                    case 0x1C5A: 
                                    case 0x1C5B: 
                                    case 0x1C5C: 
                                    case 0x1C5D: 
                                    case 0x1C5E: 
                                    case 0x1C5F: 
                                    case 0x1C60: 
                                    case 0x1C61: 
                                    case 0x1C62: 
                                    case 0x1C63: 
                                    case 0x1C64: 
                                    case 0x1C65: 
                                    case 0x1C66: 
                                    case 0x1C67: 
                                    case 0x1C68: 
                                    case 0x1C69: 
                                    case 0x1C6A: 
                                    case 0x1C6B: 
                                    case 0x1C6C: 
                                    case 0x1C6D: 
                                    case 0x1C6E: 
                                    case 0x1C6F: 
                                    case 0x1C70: 
                                    case 0x1C71: 
                                    case 0x1C72: 
                                    case 0x1C73: 
                                    case 0x1C74: 
                                    case 0x1C75: 
                                    case 0x1C76: 
                                    case 0x1C77: 
                                    case 0x1C78: 
                                    case 0x1C79: 
                                    case 0x1C7A: 
                                    case 0x1C7B: 
                                    case 0x1C7C: 
                                    case 0x1C7D: goto _488;/* ['ᱚ', 'ᱽ'] */

                                    case 0x1CE9: 
                                    case 0x1CEA: 
                                    case 0x1CEB: 
                                    case 0x1CEC: goto _488;/* ['ᳩ', 'ᳬ'] */

                                    case 0x1CEE: 
                                    case 0x1CEF: 
                                    case 0x1CF0: 
                                    case 0x1CF1: goto _488;/* ['ᳮ', 'ᳱ'] */


                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        if( input < 0xAAC1 ) {
            if( input < 0x2DA0 ) {
                if( input < 0x2080 ) {
                    if( input < 0x1FD0 ) {
                        if( input < 0x1F5C ) {
                            if( input < 0x1F46 ) {
                                if( input < 0x1F16 ) {
                                    if( input < 0x1DC0 ) {
                                        goto _488;/* ['ᴀ', 'ᶿ'] */

                                    } else if( input < 0x1E00 ) {

                                    } else {
                                        goto _488;/* ['Ḁ', 'ἕ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1F18: 
                                        case 0x1F19: 
                                        case 0x1F1A: 
                                        case 0x1F1B: 
                                        case 0x1F1C: 
                                        case 0x1F1D: goto _488;/* ['Ἐ', 'Ἕ'] */

                                        case 0x1F20: 
                                        case 0x1F21: 
                                        case 0x1F22: 
                                        case 0x1F23: 
                                        case 0x1F24: 
                                        case 0x1F25: 
                                        case 0x1F26: 
                                        case 0x1F27: 
                                        case 0x1F28: 
                                        case 0x1F29: 
                                        case 0x1F2A: 
                                        case 0x1F2B: 
                                        case 0x1F2C: 
                                        case 0x1F2D: 
                                        case 0x1F2E: 
                                        case 0x1F2F: 
                                        case 0x1F30: 
                                        case 0x1F31: 
                                        case 0x1F32: 
                                        case 0x1F33: 
                                        case 0x1F34: 
                                        case 0x1F35: 
                                        case 0x1F36: 
                                        case 0x1F37: 
                                        case 0x1F38: 
                                        case 0x1F39: 
                                        case 0x1F3A: 
                                        case 0x1F3B: 
                                        case 0x1F3C: 
                                        case 0x1F3D: 
                                        case 0x1F3E: 
                                        case 0x1F3F: 
                                        case 0x1F40: 
                                        case 0x1F41: 
                                        case 0x1F42: 
                                        case 0x1F43: 
                                        case 0x1F44: 
                                        case 0x1F45: goto _488;/* ['ἠ', 'ὅ'] */


                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x1F48: 
                                    case 0x1F49: 
                                    case 0x1F4A: 
                                    case 0x1F4B: 
                                    case 0x1F4C: 
                                    case 0x1F4D: goto _488;/* ['Ὀ', 'Ὅ'] */

                                    case 0x1F50: 
                                    case 0x1F51: 
                                    case 0x1F52: 
                                    case 0x1F53: 
                                    case 0x1F54: 
                                    case 0x1F55: 
                                    case 0x1F56: 
                                    case 0x1F57: goto _488;/* ['ὐ', 'ὗ'] */

                                    case 0x1F59: goto _488;/* 'Ὑ' */

                                    case 0x1F5B: goto _488;/* 'Ὓ' */


                                }
                            }
                        } else {
                            switch( input ) {
                                case 0x1F5D: goto _488;/* 'Ὕ' */

                                case 0x1F5F: 
                                case 0x1F60: 
                                case 0x1F61: 
                                case 0x1F62: 
                                case 0x1F63: 
                                case 0x1F64: 
                                case 0x1F65: 
                                case 0x1F66: 
                                case 0x1F67: 
                                case 0x1F68: 
                                case 0x1F69: 
                                case 0x1F6A: 
                                case 0x1F6B: 
                                case 0x1F6C: 
                                case 0x1F6D: 
                                case 0x1F6E: 
                                case 0x1F6F: 
                                case 0x1F70: 
                                case 0x1F71: 
                                case 0x1F72: 
                                case 0x1F73: 
                                case 0x1F74: 
                                case 0x1F75: 
                                case 0x1F76: 
                                case 0x1F77: 
                                case 0x1F78: 
                                case 0x1F79: 
                                case 0x1F7A: 
                                case 0x1F7B: 
                                case 0x1F7C: 
                                case 0x1F7D: goto _488;/* ['Ὗ', 'ώ'] */

                                case 0x1F80: 
                                case 0x1F81: 
                                case 0x1F82: 
                                case 0x1F83: 
                                case 0x1F84: 
                                case 0x1F85: 
                                case 0x1F86: 
                                case 0x1F87: 
                                case 0x1F88: 
                                case 0x1F89: 
                                case 0x1F8A: 
                                case 0x1F8B: 
                                case 0x1F8C: 
                                case 0x1F8D: 
                                case 0x1F8E: 
                                case 0x1F8F: 
                                case 0x1F90: 
                                case 0x1F91: 
                                case 0x1F92: 
                                case 0x1F93: 
                                case 0x1F94: 
                                case 0x1F95: 
                                case 0x1F96: 
                                case 0x1F97: 
                                case 0x1F98: 
                                case 0x1F99: 
                                case 0x1F9A: 
                                case 0x1F9B: 
                                case 0x1F9C: 
                                case 0x1F9D: 
                                case 0x1F9E: 
                                case 0x1F9F: 
                                case 0x1FA0: 
                                case 0x1FA1: 
                                case 0x1FA2: 
                                case 0x1FA3: 
                                case 0x1FA4: 
                                case 0x1FA5: 
                                case 0x1FA6: 
                                case 0x1FA7: 
                                case 0x1FA8: 
                                case 0x1FA9: 
                                case 0x1FAA: 
                                case 0x1FAB: 
                                case 0x1FAC: 
                                case 0x1FAD: 
                                case 0x1FAE: 
                                case 0x1FAF: 
                                case 0x1FB0: 
                                case 0x1FB1: 
                                case 0x1FB2: 
                                case 0x1FB3: 
                                case 0x1FB4: goto _488;/* ['ᾀ', 'ᾴ'] */

                                case 0x1FB6: 
                                case 0x1FB7: 
                                case 0x1FB8: 
                                case 0x1FB9: 
                                case 0x1FBA: 
                                case 0x1FBB: 
                                case 0x1FBC: goto _488;/* ['ᾶ', 'ᾼ'] */

                                case 0x1FBE: goto _488;/* 'ι' */

                                case 0x1FC2: 
                                case 0x1FC3: 
                                case 0x1FC4: goto _488;/* ['ῂ', 'ῄ'] */

                                case 0x1FC6: 
                                case 0x1FC7: 
                                case 0x1FC8: 
                                case 0x1FC9: 
                                case 0x1FCA: 
                                case 0x1FCB: 
                                case 0x1FCC: goto _488;/* ['ῆ', 'ῌ'] */


                            }
                        }
                    } else {
                        switch( input ) {
                            case 0x1FD0: 
                            case 0x1FD1: 
                            case 0x1FD2: 
                            case 0x1FD3: goto _488;/* ['ῐ', 'ΐ'] */

                            case 0x1FD6: 
                            case 0x1FD7: 
                            case 0x1FD8: 
                            case 0x1FD9: 
                            case 0x1FDA: 
                            case 0x1FDB: goto _488;/* ['ῖ', 'Ί'] */

                            case 0x1FE0: 
                            case 0x1FE1: 
                            case 0x1FE2: 
                            case 0x1FE3: 
                            case 0x1FE4: 
                            case 0x1FE5: 
                            case 0x1FE6: 
                            case 0x1FE7: 
                            case 0x1FE8: 
                            case 0x1FE9: 
                            case 0x1FEA: 
                            case 0x1FEB: 
                            case 0x1FEC: goto _488;/* ['ῠ', 'Ῥ'] */

                            case 0x1FF2: 
                            case 0x1FF3: 
                            case 0x1FF4: goto _488;/* ['ῲ', 'ῴ'] */

                            case 0x1FF6: 
                            case 0x1FF7: 
                            case 0x1FF8: 
                            case 0x1FF9: 
                            case 0x1FFA: 
                            case 0x1FFB: 
                            case 0x1FFC: goto _488;/* ['ῶ', 'ῼ'] */

                            case 0x2000: 
                            case 0x2001: 
                            case 0x2002: 
                            case 0x2003: 
                            case 0x2004: 
                            case 0x2005: 
                            case 0x2006: 
                            case 0x2007: 
                            case 0x2008: 
                            case 0x2009: 
                            case 0x200A: goto _465;/* [' ', ' '] */

                            case 0x2010: 
                            case 0x2011: 
                            case 0x2012: 
                            case 0x2013: 
                            case 0x2014: 
                            case 0x2015: 
                            case 0x2016: 
                            case 0x2017: 
                            case 0x2018: 
                            case 0x2019: 
                            case 0x201A: 
                            case 0x201B: goto _462;/* ['‐', '‛'] */

                            case 0x201C: goto _464;/* '“' */

                            case 0x201D: goto _472;/* '”' */

                            case 0x201E: 
                            case 0x201F: 
                            case 0x2020: 
                            case 0x2021: 
                            case 0x2022: 
                            case 0x2023: 
                            case 0x2024: 
                            case 0x2025: 
                            case 0x2026: 
                            case 0x2027: goto _462;/* ['„', '‧'] */

                            case 0x2028: goto _465;/* ' ' */

                            case 0x2029: goto _485;/* ' ' */

                            case 0x202F: goto _465;/* ' ' */

                            case 0x2030: 
                            case 0x2031: 
                            case 0x2032: 
                            case 0x2033: 
                            case 0x2034: 
                            case 0x2035: 
                            case 0x2036: 
                            case 0x2037: 
                            case 0x2038: 
                            case 0x2039: 
                            case 0x203A: 
                            case 0x203B: 
                            case 0x203C: 
                            case 0x203D: 
                            case 0x203E: goto _462;/* ['‰', '‾'] */

                            case 0x2041: 
                            case 0x2042: 
                            case 0x2043: 
                            case 0x2044: 
                            case 0x2045: 
                            case 0x2046: 
                            case 0x2047: 
                            case 0x2048: 
                            case 0x2049: 
                            case 0x204A: 
                            case 0x204B: 
                            case 0x204C: 
                            case 0x204D: 
                            case 0x204E: 
                            case 0x204F: 
                            case 0x2050: 
                            case 0x2051: 
                            case 0x2052: 
                            case 0x2053: goto _462;/* ['⁁', '⁓'] */

                            case 0x2055: 
                            case 0x2056: 
                            case 0x2057: 
                            case 0x2058: 
                            case 0x2059: 
                            case 0x205A: 
                            case 0x205B: 
                            case 0x205C: 
                            case 0x205D: 
                            case 0x205E: goto _462;/* ['⁕', '⁞'] */

                            case 0x205F: goto _465;/* ' ' */

                            case 0x2071: goto _488;/* 'ⁱ' */

                            case 0x207F: goto _488;/* 'ⁿ' */


                        }
                    }
                } else {
                    if( input < 0x21A6 ) {
                        switch( input ) {
                            case 0x2090: 
                            case 0x2091: 
                            case 0x2092: 
                            case 0x2093: 
                            case 0x2094: 
                            case 0x2095: 
                            case 0x2096: 
                            case 0x2097: 
                            case 0x2098: 
                            case 0x2099: 
                            case 0x209A: 
                            case 0x209B: 
                            case 0x209C: goto _488;/* ['ₐ', 'ₜ'] */

                            case 0x2102: goto _488;/* 'ℂ' */

                            case 0x2107: goto _488;/* 'ℇ' */

                            case 0x210A: 
                            case 0x210B: 
                            case 0x210C: 
                            case 0x210D: 
                            case 0x210E: 
                            case 0x210F: 
                            case 0x2110: 
                            case 0x2111: 
                            case 0x2112: 
                            case 0x2113: goto _488;/* ['ℊ', 'ℓ'] */

                            case 0x2115: goto _488;/* 'ℕ' */

                            case 0x2118: 
                            case 0x2119: 
                            case 0x211A: 
                            case 0x211B: 
                            case 0x211C: 
                            case 0x211D: goto _488;/* ['℘', 'ℝ'] */

                            case 0x2124: goto _488;/* 'ℤ' */

                            case 0x2126: goto _488;/* 'Ω' */

                            case 0x2128: goto _488;/* 'ℨ' */

                            case 0x212A: 
                            case 0x212B: 
                            case 0x212C: 
                            case 0x212D: 
                            case 0x212E: 
                            case 0x212F: 
                            case 0x2130: 
                            case 0x2131: 
                            case 0x2132: 
                            case 0x2133: 
                            case 0x2134: 
                            case 0x2135: 
                            case 0x2136: 
                            case 0x2137: 
                            case 0x2138: 
                            case 0x2139: goto _488;/* ['K', 'ℹ'] */

                            case 0x213C: 
                            case 0x213D: 
                            case 0x213E: 
                            case 0x213F: goto _488;/* ['ℼ', 'ℿ'] */

                            case 0x2145: 
                            case 0x2146: 
                            case 0x2147: 
                            case 0x2148: 
                            case 0x2149: goto _488;/* ['ⅅ', 'ⅉ'] */

                            case 0x214E: goto _488;/* 'ⅎ' */

                            case 0x2160: 
                            case 0x2161: 
                            case 0x2162: 
                            case 0x2163: 
                            case 0x2164: 
                            case 0x2165: 
                            case 0x2166: 
                            case 0x2167: 
                            case 0x2168: 
                            case 0x2169: 
                            case 0x216A: 
                            case 0x216B: 
                            case 0x216C: 
                            case 0x216D: 
                            case 0x216E: 
                            case 0x216F: 
                            case 0x2170: 
                            case 0x2171: 
                            case 0x2172: 
                            case 0x2173: 
                            case 0x2174: 
                            case 0x2175: 
                            case 0x2176: 
                            case 0x2177: 
                            case 0x2178: 
                            case 0x2179: 
                            case 0x217A: 
                            case 0x217B: 
                            case 0x217C: 
                            case 0x217D: 
                            case 0x217E: 
                            case 0x217F: 
                            case 0x2180: 
                            case 0x2181: 
                            case 0x2182: 
                            case 0x2183: 
                            case 0x2184: 
                            case 0x2185: 
                            case 0x2186: 
                            case 0x2187: 
                            case 0x2188: goto _488;/* ['Ⅰ', 'ↈ'] */

                            case 0x2190: 
                            case 0x2191: 
                            case 0x2192: 
                            case 0x2193: 
                            case 0x2194: 
                            case 0x2195: 
                            case 0x2196: 
                            case 0x2197: 
                            case 0x2198: 
                            case 0x2199: 
                            case 0x219A: 
                            case 0x219B: 
                            case 0x219C: 
                            case 0x219D: 
                            case 0x219E: 
                            case 0x219F: 
                            case 0x21A0: 
                            case 0x21A1: 
                            case 0x21A2: 
                            case 0x21A3: 
                            case 0x21A4: 
                            case 0x21A5: goto _462;/* ['←', '↥'] */


                        }
                    } else {
                        if( input < 0x2C00 ) {
                            if( input < 0x22A2 ) {
                                if( input < 0x2235 ) {
                                    if( input == 0x21A6 ) {
                                        goto _468;/* '↦' */

                                    } else if( input < 0x2234 ) {
                                        goto _462;/* ['↧', '∳'] */

                                    } else {
                                        goto _456;/* '∴' */

                                    }
                                } else {
                                    if( input == 0x2235 ) {
                                        goto _459;/* '∵' */

                                    } else if( input < 0x2254 ) {
                                        goto _462;/* ['∶', '≓'] */

                                    } else if( input == 0x2254 ) {
                                        goto _469;/* '≔' */

                                    } else {
                                        goto _462;/* ['≕', '⊡'] */

                                    }
                                }
                            } else {
                                if( input < 0x2460 ) {
                                    if( input == 0x22A2 ) {
                                        goto _470;/* '⊢' */

                                    } else if( input < 0x22A8 ) {
                                        goto _462;/* ['⊣', '⊧'] */

                                    } else if( input == 0x22A8 ) {
                                        goto _457;/* '⊨' */

                                    } else {
                                        goto _462;/* ['⊩', '⑟'] */

                                    }
                                } else {
                                    if( input < 0x2500 ) {

                                    } else if( input < 0x2776 ) {
                                        goto _462;/* ['─', '❵'] */

                                    } else if( input < 0x2794 ) {

                                    } else {
                                        goto _462;/* ['➔', '⯿'] */

                                    }
                                }
                            }
                        } else {
                            if( input < 0x2D00 ) {
                                if( input < 0x2C60 ) {
                                    if( input < 0x2C2F ) {
                                        goto _488;/* ['Ⰰ', 'Ⱞ'] */

                                    } else if( input == 0x2C2F ) {

                                    } else if( input < 0x2C5F ) {
                                        goto _488;/* ['ⰰ', 'ⱞ'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x2CE5 ) {
                                        goto _488;/* ['Ⱡ', 'ⳤ'] */

                                    } else if( input < 0x2CEB ) {

                                    } else if( input < 0x2CEF ) {
                                        goto _488;/* ['Ⳬ', 'ⳮ'] */

                                    } else {

                                    }
                                }
                            } else {
                                if( input < 0x2D6F ) {
                                    if( input < 0x2D26 ) {
                                        goto _488;/* ['ⴀ', 'ⴥ'] */

                                    } else if( input < 0x2D30 ) {

                                    } else if( input < 0x2D66 ) {
                                        goto _488;/* ['ⴰ', 'ⵥ'] */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x2D6F: goto _488;/* 'ⵯ' */

                                        case 0x2D80: 
                                        case 0x2D81: 
                                        case 0x2D82: 
                                        case 0x2D83: 
                                        case 0x2D84: 
                                        case 0x2D85: 
                                        case 0x2D86: 
                                        case 0x2D87: 
                                        case 0x2D88: 
                                        case 0x2D89: 
                                        case 0x2D8A: 
                                        case 0x2D8B: 
                                        case 0x2D8C: 
                                        case 0x2D8D: 
                                        case 0x2D8E: 
                                        case 0x2D8F: 
                                        case 0x2D90: 
                                        case 0x2D91: 
                                        case 0x2D92: 
                                        case 0x2D93: 
                                        case 0x2D94: 
                                        case 0x2D95: 
                                        case 0x2D96: goto _488;/* ['ⶀ', 'ⶖ'] */


                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if( input < 0xA640 ) {
                    if( input < 0x3041 ) {
                        if( input < 0x2DDF ) {
                            switch( input ) {
                                case 0x2DA0: 
                                case 0x2DA1: 
                                case 0x2DA2: 
                                case 0x2DA3: 
                                case 0x2DA4: 
                                case 0x2DA5: 
                                case 0x2DA6: goto _488;/* ['ⶠ', 'ⶦ'] */

                                case 0x2DA8: 
                                case 0x2DA9: 
                                case 0x2DAA: 
                                case 0x2DAB: 
                                case 0x2DAC: 
                                case 0x2DAD: 
                                case 0x2DAE: goto _488;/* ['ⶨ', 'ⶮ'] */

                                case 0x2DB0: 
                                case 0x2DB1: 
                                case 0x2DB2: 
                                case 0x2DB3: 
                                case 0x2DB4: 
                                case 0x2DB5: 
                                case 0x2DB6: goto _488;/* ['ⶰ', 'ⶶ'] */

                                case 0x2DB8: 
                                case 0x2DB9: 
                                case 0x2DBA: 
                                case 0x2DBB: 
                                case 0x2DBC: 
                                case 0x2DBD: 
                                case 0x2DBE: goto _488;/* ['ⶸ', 'ⶾ'] */

                                case 0x2DC0: 
                                case 0x2DC1: 
                                case 0x2DC2: 
                                case 0x2DC3: 
                                case 0x2DC4: 
                                case 0x2DC5: 
                                case 0x2DC6: goto _488;/* ['ⷀ', 'ⷆ'] */

                                case 0x2DC8: 
                                case 0x2DC9: 
                                case 0x2DCA: 
                                case 0x2DCB: 
                                case 0x2DCC: 
                                case 0x2DCD: 
                                case 0x2DCE: goto _488;/* ['ⷈ', 'ⷎ'] */

                                case 0x2DD0: 
                                case 0x2DD1: 
                                case 0x2DD2: 
                                case 0x2DD3: 
                                case 0x2DD4: 
                                case 0x2DD5: 
                                case 0x2DD6: goto _488;/* ['ⷐ', 'ⷖ'] */

                                case 0x2DD8: 
                                case 0x2DD9: 
                                case 0x2DDA: 
                                case 0x2DDB: 
                                case 0x2DDC: 
                                case 0x2DDD: 
                                case 0x2DDE: goto _488;/* ['ⷘ', 'ⷞ'] */


                            }
                        } else {
                            if( input < 0x3008 ) {
                                if( input < 0x3000 ) {
                                    if( input < 0x2E00 ) {

                                    } else if( input < 0x2E80 ) {
                                        goto _462;/* ['⸀', '⹿'] */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x3000: goto _465;/* '　' */

                                        case 0x3001: 
                                        case 0x3002: 
                                        case 0x3003: goto _462;/* ['、', '〃'] */

                                        case 0x3005: 
                                        case 0x3006: 
                                        case 0x3007: goto _488;/* ['々', '〇'] */


                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x3008: 
                                    case 0x3009: 
                                    case 0x300A: 
                                    case 0x300B: 
                                    case 0x300C: 
                                    case 0x300D: 
                                    case 0x300E: 
                                    case 0x300F: 
                                    case 0x3010: 
                                    case 0x3011: 
                                    case 0x3012: 
                                    case 0x3013: 
                                    case 0x3014: 
                                    case 0x3015: 
                                    case 0x3016: 
                                    case 0x3017: 
                                    case 0x3018: 
                                    case 0x3019: 
                                    case 0x301A: 
                                    case 0x301B: 
                                    case 0x301C: 
                                    case 0x301D: 
                                    case 0x301E: 
                                    case 0x301F: 
                                    case 0x3020: goto _462;/* ['〈', '〠'] */

                                    case 0x3021: 
                                    case 0x3022: 
                                    case 0x3023: 
                                    case 0x3024: 
                                    case 0x3025: 
                                    case 0x3026: 
                                    case 0x3027: 
                                    case 0x3028: 
                                    case 0x3029: goto _488;/* ['〡', '〩'] */

                                    case 0x3030: goto _462;/* '〰' */

                                    case 0x3031: 
                                    case 0x3032: 
                                    case 0x3033: 
                                    case 0x3034: 
                                    case 0x3035: goto _488;/* ['〱', '〵'] */

                                    case 0x3038: 
                                    case 0x3039: 
                                    case 0x303A: 
                                    case 0x303B: 
                                    case 0x303C: goto _488;/* ['〸', '〼'] */


                                }
                            }
                        }
                    } else {
                        if( input < 0x3200 ) {
                            if( input < 0x3100 ) {
                                if( input < 0x30A0 ) {
                                    if( input < 0x3097 ) {
                                        goto _488;/* ['ぁ', 'ゖ'] */

                                    } else if( input < 0x309D ) {

                                    } else {
                                        goto _488;/* ['ゝ', 'ゟ'] */

                                    }
                                } else {
                                    if( input == 0x30A0 ) {

                                    } else if( input < 0x30FB ) {
                                        goto _488;/* ['ァ', 'ヺ'] */

                                    } else if( input == 0x30FB ) {

                                    } else {
                                        goto _488;/* ['ー', 'ヿ'] */

                                    }
                                }
                            } else {
                                if( input < 0x318F ) {
                                    if( input < 0x3105 ) {

                                    } else if( input < 0x312E ) {
                                        goto _488;/* ['ㄅ', 'ㄭ'] */

                                    } else if( input < 0x3131 ) {

                                    } else {
                                        goto _488;/* ['ㄱ', 'ㆎ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x31A0: 
                                        case 0x31A1: 
                                        case 0x31A2: 
                                        case 0x31A3: 
                                        case 0x31A4: 
                                        case 0x31A5: 
                                        case 0x31A6: 
                                        case 0x31A7: 
                                        case 0x31A8: 
                                        case 0x31A9: 
                                        case 0x31AA: 
                                        case 0x31AB: 
                                        case 0x31AC: 
                                        case 0x31AD: 
                                        case 0x31AE: 
                                        case 0x31AF: 
                                        case 0x31B0: 
                                        case 0x31B1: 
                                        case 0x31B2: 
                                        case 0x31B3: 
                                        case 0x31B4: 
                                        case 0x31B5: 
                                        case 0x31B6: 
                                        case 0x31B7: 
                                        case 0x31B8: 
                                        case 0x31B9: 
                                        case 0x31BA: goto _488;/* ['ㆠ', 'ㆺ'] */

                                        case 0x31F0: 
                                        case 0x31F1: 
                                        case 0x31F2: 
                                        case 0x31F3: 
                                        case 0x31F4: 
                                        case 0x31F5: 
                                        case 0x31F6: 
                                        case 0x31F7: 
                                        case 0x31F8: 
                                        case 0x31F9: 
                                        case 0x31FA: 
                                        case 0x31FB: 
                                        case 0x31FC: 
                                        case 0x31FD: 
                                        case 0x31FE: 
                                        case 0x31FF: goto _488;/* ['ㇰ', 'ㇿ'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0xA4D0 ) {
                                if( input < 0x4E00 ) {
                                    if( input < 0x3400 ) {

                                    } else if( input < 0x4DB6 ) {
                                        goto _488;/* ['㐀', '䶵'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x9FCC ) {
                                        goto _488;/* ['一', '鿋'] */

                                    } else if( input < 0xA000 ) {

                                    } else if( input < 0xA48D ) {
                                        goto _488;/* ['ꀀ', 'ꒌ'] */

                                    } else {

                                    }
                                }
                            } else {
                                if( input < 0xA610 ) {
                                    if( input < 0xA4FE ) {
                                        goto _488;/* ['ꓐ', 'ꓽ'] */

                                    } else if( input < 0xA500 ) {

                                    } else if( input < 0xA60D ) {
                                        goto _488;/* ['ꔀ', 'ꘌ'] */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0xA610: 
                                        case 0xA611: 
                                        case 0xA612: 
                                        case 0xA613: 
                                        case 0xA614: 
                                        case 0xA615: 
                                        case 0xA616: 
                                        case 0xA617: 
                                        case 0xA618: 
                                        case 0xA619: 
                                        case 0xA61A: 
                                        case 0xA61B: 
                                        case 0xA61C: 
                                        case 0xA61D: 
                                        case 0xA61E: 
                                        case 0xA61F: goto _488;/* ['ꘐ', 'ꘟ'] */

                                        case 0xA62A: 
                                        case 0xA62B: goto _488;/* ['ꘪ', 'ꘫ'] */


                                    }
                                }
                            }
                        }
                    }
                } else {
                    if( input < 0xA8FB ) {
                        if( input < 0xA7AA ) {
                            if( input < 0xA720 ) {
                                if( input < 0xA698 ) {
                                    if( input < 0xA66F ) {
                                        goto _488;/* ['Ꙁ', 'ꙮ'] */

                                    } else if( input < 0xA67F ) {

                                    } else {
                                        goto _488;/* ['ꙿ', 'ꚗ'] */

                                    }
                                } else {
                                    if( input < 0xA6A0 ) {

                                    } else if( input < 0xA6F0 ) {
                                        goto _488;/* ['ꚠ', 'ꛯ'] */

                                    } else if( input < 0xA717 ) {

                                    } else {
                                        goto _488;/* ['ꜗ', 'ꜟ'] */

                                    }
                                }
                            } else {
                                if( input < 0xA78F ) {
                                    if( input < 0xA722 ) {

                                    } else if( input < 0xA789 ) {
                                        goto _488;/* ['Ꜣ', 'ꞈ'] */

                                    } else if( input < 0xA78B ) {

                                    } else {
                                        goto _488;/* ['Ꞌ', 'ꞎ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0xA790: 
                                        case 0xA791: goto _488;/* ['Ꞑ', 'ꞑ'] */

                                        case 0xA7A0: 
                                        case 0xA7A1: 
                                        case 0xA7A2: 
                                        case 0xA7A3: 
                                        case 0xA7A4: 
                                        case 0xA7A5: 
                                        case 0xA7A6: 
                                        case 0xA7A7: 
                                        case 0xA7A8: 
                                        case 0xA7A9: goto _488;/* ['Ꞡ', 'ꞩ'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0xA80C ) {
                                switch( input ) {
                                    case 0xA7FA: 
                                    case 0xA7FB: 
                                    case 0xA7FC: 
                                    case 0xA7FD: 
                                    case 0xA7FE: 
                                    case 0xA7FF: 
                                    case 0xA800: 
                                    case 0xA801: goto _488;/* ['ꟺ', 'ꠁ'] */

                                    case 0xA803: 
                                    case 0xA804: 
                                    case 0xA805: goto _488;/* ['ꠃ', 'ꠅ'] */

                                    case 0xA807: 
                                    case 0xA808: 
                                    case 0xA809: 
                                    case 0xA80A: goto _488;/* ['ꠇ', 'ꠊ'] */


                                }
                            } else {
                                if( input < 0xA882 ) {
                                    if( input < 0xA823 ) {
                                        goto _488;/* ['ꠌ', 'ꠢ'] */

                                    } else if( input < 0xA840 ) {

                                    } else if( input < 0xA874 ) {
                                        goto _488;/* ['ꡀ', 'ꡳ'] */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0xA882: 
                                        case 0xA883: 
                                        case 0xA884: 
                                        case 0xA885: 
                                        case 0xA886: 
                                        case 0xA887: 
                                        case 0xA888: 
                                        case 0xA889: 
                                        case 0xA88A: 
                                        case 0xA88B: 
                                        case 0xA88C: 
                                        case 0xA88D: 
                                        case 0xA88E: 
                                        case 0xA88F: 
                                        case 0xA890: 
                                        case 0xA891: 
                                        case 0xA892: 
                                        case 0xA893: 
                                        case 0xA894: 
                                        case 0xA895: 
                                        case 0xA896: 
                                        case 0xA897: 
                                        case 0xA898: 
                                        case 0xA899: 
                                        case 0xA89A: 
                                        case 0xA89B: 
                                        case 0xA89C: 
                                        case 0xA89D: 
                                        case 0xA89E: 
                                        case 0xA89F: 
                                        case 0xA8A0: 
                                        case 0xA8A1: 
                                        case 0xA8A2: 
                                        case 0xA8A3: 
                                        case 0xA8A4: 
                                        case 0xA8A5: 
                                        case 0xA8A6: 
                                        case 0xA8A7: 
                                        case 0xA8A8: 
                                        case 0xA8A9: 
                                        case 0xA8AA: 
                                        case 0xA8AB: 
                                        case 0xA8AC: 
                                        case 0xA8AD: 
                                        case 0xA8AE: 
                                        case 0xA8AF: 
                                        case 0xA8B0: 
                                        case 0xA8B1: 
                                        case 0xA8B2: 
                                        case 0xA8B3: goto _488;/* ['ꢂ', 'ꢳ'] */

                                        case 0xA8F2: 
                                        case 0xA8F3: 
                                        case 0xA8F4: 
                                        case 0xA8F5: 
                                        case 0xA8F6: 
                                        case 0xA8F7: goto _488;/* ['ꣲ', 'ꣷ'] */


                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0xAA43 ) {
                            if( input < 0xA97D ) {
                                switch( input ) {
                                    case 0xA8FB: goto _488;/* 'ꣻ' */

                                    case 0xA90A: 
                                    case 0xA90B: 
                                    case 0xA90C: 
                                    case 0xA90D: 
                                    case 0xA90E: 
                                    case 0xA90F: 
                                    case 0xA910: 
                                    case 0xA911: 
                                    case 0xA912: 
                                    case 0xA913: 
                                    case 0xA914: 
                                    case 0xA915: 
                                    case 0xA916: 
                                    case 0xA917: 
                                    case 0xA918: 
                                    case 0xA919: 
                                    case 0xA91A: 
                                    case 0xA91B: 
                                    case 0xA91C: 
                                    case 0xA91D: 
                                    case 0xA91E: 
                                    case 0xA91F: 
                                    case 0xA920: 
                                    case 0xA921: 
                                    case 0xA922: 
                                    case 0xA923: 
                                    case 0xA924: 
                                    case 0xA925: goto _488;/* ['ꤊ', 'ꤥ'] */

                                    case 0xA930: 
                                    case 0xA931: 
                                    case 0xA932: 
                                    case 0xA933: 
                                    case 0xA934: 
                                    case 0xA935: 
                                    case 0xA936: 
                                    case 0xA937: 
                                    case 0xA938: 
                                    case 0xA939: 
                                    case 0xA93A: 
                                    case 0xA93B: 
                                    case 0xA93C: 
                                    case 0xA93D: 
                                    case 0xA93E: 
                                    case 0xA93F: 
                                    case 0xA940: 
                                    case 0xA941: 
                                    case 0xA942: 
                                    case 0xA943: 
                                    case 0xA944: 
                                    case 0xA945: 
                                    case 0xA946: goto _488;/* ['ꤰ', 'ꥆ'] */

                                    case 0xA960: 
                                    case 0xA961: 
                                    case 0xA962: 
                                    case 0xA963: 
                                    case 0xA964: 
                                    case 0xA965: 
                                    case 0xA966: 
                                    case 0xA967: 
                                    case 0xA968: 
                                    case 0xA969: 
                                    case 0xA96A: 
                                    case 0xA96B: 
                                    case 0xA96C: 
                                    case 0xA96D: 
                                    case 0xA96E: 
                                    case 0xA96F: 
                                    case 0xA970: 
                                    case 0xA971: 
                                    case 0xA972: 
                                    case 0xA973: 
                                    case 0xA974: 
                                    case 0xA975: 
                                    case 0xA976: 
                                    case 0xA977: 
                                    case 0xA978: 
                                    case 0xA979: 
                                    case 0xA97A: 
                                    case 0xA97B: 
                                    case 0xA97C: goto _488;/* ['ꥠ', 'ꥼ'] */


                                }
                            } else {
                                switch( input ) {
                                    case 0xA984: 
                                    case 0xA985: 
                                    case 0xA986: 
                                    case 0xA987: 
                                    case 0xA988: 
                                    case 0xA989: 
                                    case 0xA98A: 
                                    case 0xA98B: 
                                    case 0xA98C: 
                                    case 0xA98D: 
                                    case 0xA98E: 
                                    case 0xA98F: 
                                    case 0xA990: 
                                    case 0xA991: 
                                    case 0xA992: 
                                    case 0xA993: 
                                    case 0xA994: 
                                    case 0xA995: 
                                    case 0xA996: 
                                    case 0xA997: 
                                    case 0xA998: 
                                    case 0xA999: 
                                    case 0xA99A: 
                                    case 0xA99B: 
                                    case 0xA99C: 
                                    case 0xA99D: 
                                    case 0xA99E: 
                                    case 0xA99F: 
                                    case 0xA9A0: 
                                    case 0xA9A1: 
                                    case 0xA9A2: 
                                    case 0xA9A3: 
                                    case 0xA9A4: 
                                    case 0xA9A5: 
                                    case 0xA9A6: 
                                    case 0xA9A7: 
                                    case 0xA9A8: 
                                    case 0xA9A9: 
                                    case 0xA9AA: 
                                    case 0xA9AB: 
                                    case 0xA9AC: 
                                    case 0xA9AD: 
                                    case 0xA9AE: 
                                    case 0xA9AF: 
                                    case 0xA9B0: 
                                    case 0xA9B1: 
                                    case 0xA9B2: goto _488;/* ['ꦄ', 'ꦲ'] */

                                    case 0xA9CF: goto _488;/* 'ꧏ' */

                                    case 0xAA00: 
                                    case 0xAA01: 
                                    case 0xAA02: 
                                    case 0xAA03: 
                                    case 0xAA04: 
                                    case 0xAA05: 
                                    case 0xAA06: 
                                    case 0xAA07: 
                                    case 0xAA08: 
                                    case 0xAA09: 
                                    case 0xAA0A: 
                                    case 0xAA0B: 
                                    case 0xAA0C: 
                                    case 0xAA0D: 
                                    case 0xAA0E: 
                                    case 0xAA0F: 
                                    case 0xAA10: 
                                    case 0xAA11: 
                                    case 0xAA12: 
                                    case 0xAA13: 
                                    case 0xAA14: 
                                    case 0xAA15: 
                                    case 0xAA16: 
                                    case 0xAA17: 
                                    case 0xAA18: 
                                    case 0xAA19: 
                                    case 0xAA1A: 
                                    case 0xAA1B: 
                                    case 0xAA1C: 
                                    case 0xAA1D: 
                                    case 0xAA1E: 
                                    case 0xAA1F: 
                                    case 0xAA20: 
                                    case 0xAA21: 
                                    case 0xAA22: 
                                    case 0xAA23: 
                                    case 0xAA24: 
                                    case 0xAA25: 
                                    case 0xAA26: 
                                    case 0xAA27: 
                                    case 0xAA28: goto _488;/* ['ꨀ', 'ꨨ'] */

                                    case 0xAA40: 
                                    case 0xAA41: 
                                    case 0xAA42: goto _488;/* ['ꩀ', 'ꩂ'] */


                                }
                            }
                        } else {
                            switch( input ) {
                                case 0xAA44: 
                                case 0xAA45: 
                                case 0xAA46: 
                                case 0xAA47: 
                                case 0xAA48: 
                                case 0xAA49: 
                                case 0xAA4A: 
                                case 0xAA4B: goto _488;/* ['ꩄ', 'ꩋ'] */

                                case 0xAA60: 
                                case 0xAA61: 
                                case 0xAA62: 
                                case 0xAA63: 
                                case 0xAA64: 
                                case 0xAA65: 
                                case 0xAA66: 
                                case 0xAA67: 
                                case 0xAA68: 
                                case 0xAA69: 
                                case 0xAA6A: 
                                case 0xAA6B: 
                                case 0xAA6C: 
                                case 0xAA6D: 
                                case 0xAA6E: 
                                case 0xAA6F: 
                                case 0xAA70: 
                                case 0xAA71: 
                                case 0xAA72: 
                                case 0xAA73: 
                                case 0xAA74: 
                                case 0xAA75: 
                                case 0xAA76: goto _488;/* ['ꩠ', 'ꩶ'] */

                                case 0xAA7A: goto _488;/* 'ꩺ' */

                                case 0xAA80: 
                                case 0xAA81: 
                                case 0xAA82: 
                                case 0xAA83: 
                                case 0xAA84: 
                                case 0xAA85: 
                                case 0xAA86: 
                                case 0xAA87: 
                                case 0xAA88: 
                                case 0xAA89: 
                                case 0xAA8A: 
                                case 0xAA8B: 
                                case 0xAA8C: 
                                case 0xAA8D: 
                                case 0xAA8E: 
                                case 0xAA8F: 
                                case 0xAA90: 
                                case 0xAA91: 
                                case 0xAA92: 
                                case 0xAA93: 
                                case 0xAA94: 
                                case 0xAA95: 
                                case 0xAA96: 
                                case 0xAA97: 
                                case 0xAA98: 
                                case 0xAA99: 
                                case 0xAA9A: 
                                case 0xAA9B: 
                                case 0xAA9C: 
                                case 0xAA9D: 
                                case 0xAA9E: 
                                case 0xAA9F: 
                                case 0xAAA0: 
                                case 0xAAA1: 
                                case 0xAAA2: 
                                case 0xAAA3: 
                                case 0xAAA4: 
                                case 0xAAA5: 
                                case 0xAAA6: 
                                case 0xAAA7: 
                                case 0xAAA8: 
                                case 0xAAA9: 
                                case 0xAAAA: 
                                case 0xAAAB: 
                                case 0xAAAC: 
                                case 0xAAAD: 
                                case 0xAAAE: 
                                case 0xAAAF: goto _488;/* ['ꪀ', 'ꪯ'] */

                                case 0xAAB1: goto _488;/* 'ꪱ' */

                                case 0xAAB5: 
                                case 0xAAB6: goto _488;/* ['ꪵ', 'ꪶ'] */

                                case 0xAAB9: 
                                case 0xAABA: 
                                case 0xAABB: 
                                case 0xAABC: 
                                case 0xAABD: goto _488;/* ['ꪹ', 'ꪽ'] */

                                case 0xAAC0: goto _488;/* 'ꫀ' */


                            }
                        }
                    }
                }
            }
        } else {
            if( input < 0x103D0 ) {
                if( input < 0xFE45 ) {
                    if( input < 0xFB07 ) {
                        if( input < 0xABC0 ) {
                            switch( input ) {
                                case 0xAAC2: goto _488;/* 'ꫂ' */

                                case 0xAADB: 
                                case 0xAADC: 
                                case 0xAADD: goto _488;/* ['ꫛ', 'ꫝ'] */

                                case 0xAB01: 
                                case 0xAB02: 
                                case 0xAB03: 
                                case 0xAB04: 
                                case 0xAB05: 
                                case 0xAB06: goto _488;/* ['ꬁ', 'ꬆ'] */

                                case 0xAB09: 
                                case 0xAB0A: 
                                case 0xAB0B: 
                                case 0xAB0C: 
                                case 0xAB0D: 
                                case 0xAB0E: goto _488;/* ['ꬉ', 'ꬎ'] */

                                case 0xAB11: 
                                case 0xAB12: 
                                case 0xAB13: 
                                case 0xAB14: 
                                case 0xAB15: 
                                case 0xAB16: goto _488;/* ['ꬑ', 'ꬖ'] */

                                case 0xAB20: 
                                case 0xAB21: 
                                case 0xAB22: 
                                case 0xAB23: 
                                case 0xAB24: 
                                case 0xAB25: 
                                case 0xAB26: goto _488;/* ['ꬠ', 'ꬦ'] */

                                case 0xAB28: 
                                case 0xAB29: 
                                case 0xAB2A: 
                                case 0xAB2B: 
                                case 0xAB2C: 
                                case 0xAB2D: 
                                case 0xAB2E: goto _488;/* ['ꬨ', 'ꬮ'] */


                            }
                        } else {
                            if( input < 0xD7FC ) {
                                if( input < 0xD7A4 ) {
                                    if( input < 0xABE3 ) {
                                        goto _488;/* ['ꯀ', 'ꯢ'] */

                                    } else if( input < 0xAC00 ) {

                                    } else {
                                        goto _488;/* ['가', '힣'] */

                                    }
                                } else {
                                    if( input < 0xD7B0 ) {

                                    } else if( input < 0xD7C7 ) {
                                        goto _488;/* ['ힰ', 'ퟆ'] */

                                    } else if( input < 0xD7CB ) {

                                    } else {
                                        goto _488;/* ['ퟋ', 'ퟻ'] */

                                    }
                                }
                            } else {
                                if( input < 0xFA6E ) {
                                    if( input < 0xF900 ) {

                                    } else if( input < 0xFA2E ) {
                                        goto _488;/* ['豈', '鶴'] */

                                    } else if( input < 0xFA30 ) {

                                    } else {
                                        goto _488;/* ['侮', '舘'] */

                                    }
                                } else {
                                    if( input < 0xFA70 ) {

                                    } else if( input < 0xFADA ) {
                                        goto _488;/* ['並', '龎'] */

                                    } else if( input < 0xFB00 ) {

                                    } else {
                                        goto _488;/* ['ﬀ', 'ﬆ'] */

                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0xFB43 ) {
                            switch( input ) {
                                case 0xFB13: 
                                case 0xFB14: 
                                case 0xFB15: 
                                case 0xFB16: 
                                case 0xFB17: goto _488;/* ['ﬓ', 'ﬗ'] */

                                case 0xFB1D: goto _488;/* 'יִ' */

                                case 0xFB1F: 
                                case 0xFB20: 
                                case 0xFB21: 
                                case 0xFB22: 
                                case 0xFB23: 
                                case 0xFB24: 
                                case 0xFB25: 
                                case 0xFB26: 
                                case 0xFB27: 
                                case 0xFB28: goto _488;/* ['ײַ', 'ﬨ'] */

                                case 0xFB2A: 
                                case 0xFB2B: 
                                case 0xFB2C: 
                                case 0xFB2D: 
                                case 0xFB2E: 
                                case 0xFB2F: 
                                case 0xFB30: 
                                case 0xFB31: 
                                case 0xFB32: 
                                case 0xFB33: 
                                case 0xFB34: 
                                case 0xFB35: 
                                case 0xFB36: goto _488;/* ['שׁ', 'זּ'] */

                                case 0xFB38: 
                                case 0xFB39: 
                                case 0xFB3A: 
                                case 0xFB3B: 
                                case 0xFB3C: goto _488;/* ['טּ', 'לּ'] */

                                case 0xFB3E: goto _488;/* 'מּ' */

                                case 0xFB40: 
                                case 0xFB41: goto _488;/* ['נּ', 'סּ'] */


                            }
                        } else {
                            if( input < 0xFD3E ) {
                                if( input < 0xFBB2 ) {
                                    if( input < 0xFB45 ) {
                                        goto _488;/* ['ףּ', 'פּ'] */

                                    } else if( input == 0xFB45 ) {

                                    } else {
                                        goto _488;/* ['צּ', 'ﮱ'] */

                                    }
                                } else {
                                    if( input < 0xFBD3 ) {

                                    } else if( input < 0xFC5E ) {
                                        goto _488;/* ['ﯓ', 'ﱝ'] */

                                    } else if( input < 0xFC64 ) {

                                    } else {
                                        goto _488;/* ['ﱤ', 'ﴽ'] */

                                    }
                                }
                            } else {
                                if( input < 0xFD92 ) {
                                    switch( input ) {
                                        case 0xFD3E: 
                                        case 0xFD3F: goto _462;/* ['﴾', '﴿'] */

                                        case 0xFD50: 
                                        case 0xFD51: 
                                        case 0xFD52: 
                                        case 0xFD53: 
                                        case 0xFD54: 
                                        case 0xFD55: 
                                        case 0xFD56: 
                                        case 0xFD57: 
                                        case 0xFD58: 
                                        case 0xFD59: 
                                        case 0xFD5A: 
                                        case 0xFD5B: 
                                        case 0xFD5C: 
                                        case 0xFD5D: 
                                        case 0xFD5E: 
                                        case 0xFD5F: 
                                        case 0xFD60: 
                                        case 0xFD61: 
                                        case 0xFD62: 
                                        case 0xFD63: 
                                        case 0xFD64: 
                                        case 0xFD65: 
                                        case 0xFD66: 
                                        case 0xFD67: 
                                        case 0xFD68: 
                                        case 0xFD69: 
                                        case 0xFD6A: 
                                        case 0xFD6B: 
                                        case 0xFD6C: 
                                        case 0xFD6D: 
                                        case 0xFD6E: 
                                        case 0xFD6F: 
                                        case 0xFD70: 
                                        case 0xFD71: 
                                        case 0xFD72: 
                                        case 0xFD73: 
                                        case 0xFD74: 
                                        case 0xFD75: 
                                        case 0xFD76: 
                                        case 0xFD77: 
                                        case 0xFD78: 
                                        case 0xFD79: 
                                        case 0xFD7A: 
                                        case 0xFD7B: 
                                        case 0xFD7C: 
                                        case 0xFD7D: 
                                        case 0xFD7E: 
                                        case 0xFD7F: 
                                        case 0xFD80: 
                                        case 0xFD81: 
                                        case 0xFD82: 
                                        case 0xFD83: 
                                        case 0xFD84: 
                                        case 0xFD85: 
                                        case 0xFD86: 
                                        case 0xFD87: 
                                        case 0xFD88: 
                                        case 0xFD89: 
                                        case 0xFD8A: 
                                        case 0xFD8B: 
                                        case 0xFD8C: 
                                        case 0xFD8D: 
                                        case 0xFD8E: 
                                        case 0xFD8F: goto _488;/* ['ﵐ', 'ﶏ'] */


                                    }
                                } else {
                                    switch( input ) {
                                        case 0xFD92: 
                                        case 0xFD93: 
                                        case 0xFD94: 
                                        case 0xFD95: 
                                        case 0xFD96: 
                                        case 0xFD97: 
                                        case 0xFD98: 
                                        case 0xFD99: 
                                        case 0xFD9A: 
                                        case 0xFD9B: 
                                        case 0xFD9C: 
                                        case 0xFD9D: 
                                        case 0xFD9E: 
                                        case 0xFD9F: 
                                        case 0xFDA0: 
                                        case 0xFDA1: 
                                        case 0xFDA2: 
                                        case 0xFDA3: 
                                        case 0xFDA4: 
                                        case 0xFDA5: 
                                        case 0xFDA6: 
                                        case 0xFDA7: 
                                        case 0xFDA8: 
                                        case 0xFDA9: 
                                        case 0xFDAA: 
                                        case 0xFDAB: 
                                        case 0xFDAC: 
                                        case 0xFDAD: 
                                        case 0xFDAE: 
                                        case 0xFDAF: 
                                        case 0xFDB0: 
                                        case 0xFDB1: 
                                        case 0xFDB2: 
                                        case 0xFDB3: 
                                        case 0xFDB4: 
                                        case 0xFDB5: 
                                        case 0xFDB6: 
                                        case 0xFDB7: 
                                        case 0xFDB8: 
                                        case 0xFDB9: 
                                        case 0xFDBA: 
                                        case 0xFDBB: 
                                        case 0xFDBC: 
                                        case 0xFDBD: 
                                        case 0xFDBE: 
                                        case 0xFDBF: 
                                        case 0xFDC0: 
                                        case 0xFDC1: 
                                        case 0xFDC2: 
                                        case 0xFDC3: 
                                        case 0xFDC4: 
                                        case 0xFDC5: 
                                        case 0xFDC6: 
                                        case 0xFDC7: goto _488;/* ['ﶒ', 'ﷇ'] */

                                        case 0xFDF0: 
                                        case 0xFDF1: 
                                        case 0xFDF2: 
                                        case 0xFDF3: 
                                        case 0xFDF4: 
                                        case 0xFDF5: 
                                        case 0xFDF6: 
                                        case 0xFDF7: 
                                        case 0xFDF8: 
                                        case 0xFDF9: goto _488;/* ['ﷰ', 'ﷹ'] */


                                    }
                                }
                            }
                        }
                    }
                } else {
                    if( input < 0xFFDA ) {
                        if( input < 0xFEFD ) {
                            if( input < 0xFE78 ) {
                                switch( input ) {
                                    case 0xFE45: 
                                    case 0xFE46: goto _462;/* ['﹅', '﹆'] */

                                    case 0xFE71: goto _488;/* 'ﹱ' */

                                    case 0xFE73: goto _488;/* 'ﹳ' */

                                    case 0xFE77: goto _488;/* 'ﹷ' */


                                }
                            } else {
                                if( input < 0xFE7C ) {
                                    switch( input ) {
                                        case 0xFE79: goto _488;/* 'ﹹ' */

                                        case 0xFE7B: goto _488;/* 'ﹻ' */


                                    }
                                } else {
                                    if( input == 0xFE7C ) {

                                    } else if( input == 0xFE7D ) {
                                        goto _488;/* 'ﹽ' */

                                    } else if( input == 0xFE7E ) {

                                    } else {
                                        goto _488;/* ['ﹿ', 'ﻼ'] */

                                    }
                                }
                            }
                        } else {
                            if( input < 0xFFA0 ) {
                                if( input < 0xFF41 ) {
                                    switch( input ) {
                                        case 0xFF21: 
                                        case 0xFF22: 
                                        case 0xFF23: 
                                        case 0xFF24: 
                                        case 0xFF25: 
                                        case 0xFF26: 
                                        case 0xFF27: 
                                        case 0xFF28: 
                                        case 0xFF29: 
                                        case 0xFF2A: 
                                        case 0xFF2B: 
                                        case 0xFF2C: 
                                        case 0xFF2D: 
                                        case 0xFF2E: 
                                        case 0xFF2F: 
                                        case 0xFF30: 
                                        case 0xFF31: 
                                        case 0xFF32: 
                                        case 0xFF33: 
                                        case 0xFF34: 
                                        case 0xFF35: 
                                        case 0xFF36: 
                                        case 0xFF37: 
                                        case 0xFF38: 
                                        case 0xFF39: 
                                        case 0xFF3A: goto _488;/* ['Ａ', 'Ｚ'] */


                                    }
                                } else {
                                    if( input < 0xFF5B ) {
                                        goto _488;/* ['ａ', 'ｚ'] */

                                    } else if( input < 0xFF66 ) {

                                    } else if( input < 0xFF9E ) {
                                        goto _488;/* ['ｦ', 'ﾝ'] */

                                    } else {

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0xFFA0: 
                                    case 0xFFA1: 
                                    case 0xFFA2: 
                                    case 0xFFA3: 
                                    case 0xFFA4: 
                                    case 0xFFA5: 
                                    case 0xFFA6: 
                                    case 0xFFA7: 
                                    case 0xFFA8: 
                                    case 0xFFA9: 
                                    case 0xFFAA: 
                                    case 0xFFAB: 
                                    case 0xFFAC: 
                                    case 0xFFAD: 
                                    case 0xFFAE: 
                                    case 0xFFAF: 
                                    case 0xFFB0: 
                                    case 0xFFB1: 
                                    case 0xFFB2: 
                                    case 0xFFB3: 
                                    case 0xFFB4: 
                                    case 0xFFB5: 
                                    case 0xFFB6: 
                                    case 0xFFB7: 
                                    case 0xFFB8: 
                                    case 0xFFB9: 
                                    case 0xFFBA: 
                                    case 0xFFBB: 
                                    case 0xFFBC: 
                                    case 0xFFBD: 
                                    case 0xFFBE: goto _488;/* ['ﾠ', 'ﾾ'] */

                                    case 0xFFC2: 
                                    case 0xFFC3: 
                                    case 0xFFC4: 
                                    case 0xFFC5: 
                                    case 0xFFC6: 
                                    case 0xFFC7: goto _488;/* ['ￂ', 'ￇ'] */

                                    case 0xFFCA: 
                                    case 0xFFCB: 
                                    case 0xFFCC: 
                                    case 0xFFCD: 
                                    case 0xFFCE: 
                                    case 0xFFCF: goto _488;/* ['ￊ', 'ￏ'] */

                                    case 0xFFD2: 
                                    case 0xFFD3: 
                                    case 0xFFD4: 
                                    case 0xFFD5: 
                                    case 0xFFD6: 
                                    case 0xFFD7: goto _488;/* ['ￒ', 'ￗ'] */


                                }
                            }
                        }
                    } else {
                        if( input < 0x100FB ) {
                            if( input < 0x1003B ) {
                                switch( input ) {
                                    case 0xFFDA: 
                                    case 0xFFDB: 
                                    case 0xFFDC: goto _488;/* ['ￚ', 'ￜ'] */

                                    case 0x10000: 
                                    case 0x10001: 
                                    case 0x10002: 
                                    case 0x10003: 
                                    case 0x10004: 
                                    case 0x10005: 
                                    case 0x10006: 
                                    case 0x10007: 
                                    case 0x10008: 
                                    case 0x10009: 
                                    case 0x1000A: 
                                    case 0x1000B: goto _488;/* ['𐀀', '𐀋'] */

                                    case 0x1000D: 
                                    case 0x1000E: 
                                    case 0x1000F: 
                                    case 0x10010: 
                                    case 0x10011: 
                                    case 0x10012: 
                                    case 0x10013: 
                                    case 0x10014: 
                                    case 0x10015: 
                                    case 0x10016: 
                                    case 0x10017: 
                                    case 0x10018: 
                                    case 0x10019: 
                                    case 0x1001A: 
                                    case 0x1001B: 
                                    case 0x1001C: 
                                    case 0x1001D: 
                                    case 0x1001E: 
                                    case 0x1001F: 
                                    case 0x10020: 
                                    case 0x10021: 
                                    case 0x10022: 
                                    case 0x10023: 
                                    case 0x10024: 
                                    case 0x10025: 
                                    case 0x10026: goto _488;/* ['𐀍', '𐀦'] */

                                    case 0x10028: 
                                    case 0x10029: 
                                    case 0x1002A: 
                                    case 0x1002B: 
                                    case 0x1002C: 
                                    case 0x1002D: 
                                    case 0x1002E: 
                                    case 0x1002F: 
                                    case 0x10030: 
                                    case 0x10031: 
                                    case 0x10032: 
                                    case 0x10033: 
                                    case 0x10034: 
                                    case 0x10035: 
                                    case 0x10036: 
                                    case 0x10037: 
                                    case 0x10038: 
                                    case 0x10039: 
                                    case 0x1003A: goto _488;/* ['𐀨', '𐀺'] */


                                }
                            } else {
                                if( input < 0x1004E ) {
                                    switch( input ) {
                                        case 0x1003C: 
                                        case 0x1003D: goto _488;/* ['𐀼', '𐀽'] */

                                        case 0x1003F: 
                                        case 0x10040: 
                                        case 0x10041: 
                                        case 0x10042: 
                                        case 0x10043: 
                                        case 0x10044: 
                                        case 0x10045: 
                                        case 0x10046: 
                                        case 0x10047: 
                                        case 0x10048: 
                                        case 0x10049: 
                                        case 0x1004A: 
                                        case 0x1004B: 
                                        case 0x1004C: 
                                        case 0x1004D: goto _488;/* ['𐀿', '𐁍'] */


                                    }
                                } else {
                                    if( input < 0x10050 ) {

                                    } else if( input < 0x1005E ) {
                                        goto _488;/* ['𐁐', '𐁝'] */

                                    } else if( input < 0x10080 ) {

                                    } else {
                                        goto _488;/* ['𐂀', '𐃺'] */

                                    }
                                }
                            }
                        } else {
                            if( input < 0x1031F ) {
                                if( input < 0x1029D ) {
                                    if( input < 0x10140 ) {

                                    } else if( input < 0x10175 ) {
                                        goto _488;/* ['𐅀', '𐅴'] */

                                    } else if( input < 0x10280 ) {

                                    } else {
                                        goto _488;/* ['𐊀', '𐊜'] */

                                    }
                                } else {
                                    if( input < 0x102A0 ) {

                                    } else if( input < 0x102D1 ) {
                                        goto _488;/* ['𐊠', '𐋐'] */

                                    } else if( input < 0x10300 ) {

                                    } else {
                                        goto _488;/* ['𐌀', '𐌞'] */

                                    }
                                }
                            } else {
                                if( input < 0x1039E ) {
                                    switch( input ) {
                                        case 0x10330: 
                                        case 0x10331: 
                                        case 0x10332: 
                                        case 0x10333: 
                                        case 0x10334: 
                                        case 0x10335: 
                                        case 0x10336: 
                                        case 0x10337: 
                                        case 0x10338: 
                                        case 0x10339: 
                                        case 0x1033A: 
                                        case 0x1033B: 
                                        case 0x1033C: 
                                        case 0x1033D: 
                                        case 0x1033E: 
                                        case 0x1033F: 
                                        case 0x10340: 
                                        case 0x10341: 
                                        case 0x10342: 
                                        case 0x10343: 
                                        case 0x10344: 
                                        case 0x10345: 
                                        case 0x10346: 
                                        case 0x10347: 
                                        case 0x10348: 
                                        case 0x10349: 
                                        case 0x1034A: goto _488;/* ['𐌰', '𐍊'] */

                                        case 0x10380: 
                                        case 0x10381: 
                                        case 0x10382: 
                                        case 0x10383: 
                                        case 0x10384: 
                                        case 0x10385: 
                                        case 0x10386: 
                                        case 0x10387: 
                                        case 0x10388: 
                                        case 0x10389: 
                                        case 0x1038A: 
                                        case 0x1038B: 
                                        case 0x1038C: 
                                        case 0x1038D: 
                                        case 0x1038E: 
                                        case 0x1038F: 
                                        case 0x10390: 
                                        case 0x10391: 
                                        case 0x10392: 
                                        case 0x10393: 
                                        case 0x10394: 
                                        case 0x10395: 
                                        case 0x10396: 
                                        case 0x10397: 
                                        case 0x10398: 
                                        case 0x10399: 
                                        case 0x1039A: 
                                        case 0x1039B: 
                                        case 0x1039C: 
                                        case 0x1039D: goto _488;/* ['𐎀', '𐎝'] */


                                    }
                                } else {
                                    switch( input ) {
                                        case 0x103A0: 
                                        case 0x103A1: 
                                        case 0x103A2: 
                                        case 0x103A3: 
                                        case 0x103A4: 
                                        case 0x103A5: 
                                        case 0x103A6: 
                                        case 0x103A7: 
                                        case 0x103A8: 
                                        case 0x103A9: 
                                        case 0x103AA: 
                                        case 0x103AB: 
                                        case 0x103AC: 
                                        case 0x103AD: 
                                        case 0x103AE: 
                                        case 0x103AF: 
                                        case 0x103B0: 
                                        case 0x103B1: 
                                        case 0x103B2: 
                                        case 0x103B3: 
                                        case 0x103B4: 
                                        case 0x103B5: 
                                        case 0x103B6: 
                                        case 0x103B7: 
                                        case 0x103B8: 
                                        case 0x103B9: 
                                        case 0x103BA: 
                                        case 0x103BB: 
                                        case 0x103BC: 
                                        case 0x103BD: 
                                        case 0x103BE: 
                                        case 0x103BF: 
                                        case 0x103C0: 
                                        case 0x103C1: 
                                        case 0x103C2: 
                                        case 0x103C3: goto _488;/* ['𐎠', '𐏃'] */

                                        case 0x103C8: 
                                        case 0x103C9: 
                                        case 0x103CA: 
                                        case 0x103CB: 
                                        case 0x103CC: 
                                        case 0x103CD: 
                                        case 0x103CE: 
                                        case 0x103CF: goto _488;/* ['𐏈', '𐏏'] */


                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if( input < 0x1D4A3 ) {
                    if( input < 0x10A7D ) {
                        if( input < 0x1083F ) {
                            if( input < 0x10808 ) {
                                if( input < 0x10400 ) {
                                    switch( input ) {
                                        case 0x103D1: 
                                        case 0x103D2: 
                                        case 0x103D3: 
                                        case 0x103D4: 
                                        case 0x103D5: goto _488;/* ['𐏑', '𐏕'] */


                                    }
                                } else {
                                    if( input < 0x1049E ) {
                                        goto _488;/* ['𐐀', '𐒝'] */

                                    } else if( input < 0x10800 ) {

                                    } else if( input < 0x10806 ) {
                                        goto _488;/* ['𐠀', '𐠅'] */

                                    } else {

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x10808: goto _488;/* '𐠈' */

                                    case 0x1080A: 
                                    case 0x1080B: 
                                    case 0x1080C: 
                                    case 0x1080D: 
                                    case 0x1080E: 
                                    case 0x1080F: 
                                    case 0x10810: 
                                    case 0x10811: 
                                    case 0x10812: 
                                    case 0x10813: 
                                    case 0x10814: 
                                    case 0x10815: 
                                    case 0x10816: 
                                    case 0x10817: 
                                    case 0x10818: 
                                    case 0x10819: 
                                    case 0x1081A: 
                                    case 0x1081B: 
                                    case 0x1081C: 
                                    case 0x1081D: 
                                    case 0x1081E: 
                                    case 0x1081F: 
                                    case 0x10820: 
                                    case 0x10821: 
                                    case 0x10822: 
                                    case 0x10823: 
                                    case 0x10824: 
                                    case 0x10825: 
                                    case 0x10826: 
                                    case 0x10827: 
                                    case 0x10828: 
                                    case 0x10829: 
                                    case 0x1082A: 
                                    case 0x1082B: 
                                    case 0x1082C: 
                                    case 0x1082D: 
                                    case 0x1082E: 
                                    case 0x1082F: 
                                    case 0x10830: 
                                    case 0x10831: 
                                    case 0x10832: 
                                    case 0x10833: 
                                    case 0x10834: 
                                    case 0x10835: goto _488;/* ['𐠊', '𐠵'] */

                                    case 0x10837: 
                                    case 0x10838: goto _488;/* ['𐠷', '𐠸'] */

                                    case 0x1083C: goto _488;/* '𐠼' */


                                }
                            }
                        } else {
                            if( input < 0x10A01 ) {
                                switch( input ) {
                                    case 0x1083F: 
                                    case 0x10840: 
                                    case 0x10841: 
                                    case 0x10842: 
                                    case 0x10843: 
                                    case 0x10844: 
                                    case 0x10845: 
                                    case 0x10846: 
                                    case 0x10847: 
                                    case 0x10848: 
                                    case 0x10849: 
                                    case 0x1084A: 
                                    case 0x1084B: 
                                    case 0x1084C: 
                                    case 0x1084D: 
                                    case 0x1084E: 
                                    case 0x1084F: 
                                    case 0x10850: 
                                    case 0x10851: 
                                    case 0x10852: 
                                    case 0x10853: 
                                    case 0x10854: 
                                    case 0x10855: goto _488;/* ['𐠿', '𐡕'] */

                                    case 0x10900: 
                                    case 0x10901: 
                                    case 0x10902: 
                                    case 0x10903: 
                                    case 0x10904: 
                                    case 0x10905: 
                                    case 0x10906: 
                                    case 0x10907: 
                                    case 0x10908: 
                                    case 0x10909: 
                                    case 0x1090A: 
                                    case 0x1090B: 
                                    case 0x1090C: 
                                    case 0x1090D: 
                                    case 0x1090E: 
                                    case 0x1090F: 
                                    case 0x10910: 
                                    case 0x10911: 
                                    case 0x10912: 
                                    case 0x10913: 
                                    case 0x10914: 
                                    case 0x10915: goto _488;/* ['𐤀', '𐤕'] */

                                    case 0x10920: 
                                    case 0x10921: 
                                    case 0x10922: 
                                    case 0x10923: 
                                    case 0x10924: 
                                    case 0x10925: 
                                    case 0x10926: 
                                    case 0x10927: 
                                    case 0x10928: 
                                    case 0x10929: 
                                    case 0x1092A: 
                                    case 0x1092B: 
                                    case 0x1092C: 
                                    case 0x1092D: 
                                    case 0x1092E: 
                                    case 0x1092F: 
                                    case 0x10930: 
                                    case 0x10931: 
                                    case 0x10932: 
                                    case 0x10933: 
                                    case 0x10934: 
                                    case 0x10935: 
                                    case 0x10936: 
                                    case 0x10937: 
                                    case 0x10938: 
                                    case 0x10939: goto _488;/* ['𐤠', '𐤹'] */

                                    case 0x10A00: goto _488;/* '𐨀' */


                                }
                            } else {
                                switch( input ) {
                                    case 0x10A10: 
                                    case 0x10A11: 
                                    case 0x10A12: 
                                    case 0x10A13: goto _488;/* ['𐨐', '𐨓'] */

                                    case 0x10A15: 
                                    case 0x10A16: 
                                    case 0x10A17: goto _488;/* ['𐨕', '𐨗'] */

                                    case 0x10A19: 
                                    case 0x10A1A: 
                                    case 0x10A1B: 
                                    case 0x10A1C: 
                                    case 0x10A1D: 
                                    case 0x10A1E: 
                                    case 0x10A1F: 
                                    case 0x10A20: 
                                    case 0x10A21: 
                                    case 0x10A22: 
                                    case 0x10A23: 
                                    case 0x10A24: 
                                    case 0x10A25: 
                                    case 0x10A26: 
                                    case 0x10A27: 
                                    case 0x10A28: 
                                    case 0x10A29: 
                                    case 0x10A2A: 
                                    case 0x10A2B: 
                                    case 0x10A2C: 
                                    case 0x10A2D: 
                                    case 0x10A2E: 
                                    case 0x10A2F: 
                                    case 0x10A30: 
                                    case 0x10A31: 
                                    case 0x10A32: 
                                    case 0x10A33: goto _488;/* ['𐨙', '𐨳'] */

                                    case 0x10A60: 
                                    case 0x10A61: 
                                    case 0x10A62: 
                                    case 0x10A63: 
                                    case 0x10A64: 
                                    case 0x10A65: 
                                    case 0x10A66: 
                                    case 0x10A67: 
                                    case 0x10A68: 
                                    case 0x10A69: 
                                    case 0x10A6A: 
                                    case 0x10A6B: 
                                    case 0x10A6C: 
                                    case 0x10A6D: 
                                    case 0x10A6E: 
                                    case 0x10A6F: 
                                    case 0x10A70: 
                                    case 0x10A71: 
                                    case 0x10A72: 
                                    case 0x10A73: 
                                    case 0x10A74: 
                                    case 0x10A75: 
                                    case 0x10A76: 
                                    case 0x10A77: 
                                    case 0x10A78: 
                                    case 0x10A79: 
                                    case 0x10A7A: 
                                    case 0x10A7B: 
                                    case 0x10A7C: goto _488;/* ['𐩠', '𐩼'] */


                                }
                            }
                        }
                    } else {
                        if( input < 0x12400 ) {
                            if( input < 0x10C00 ) {
                                if( input < 0x10B40 ) {
                                    if( input < 0x10B00 ) {

                                    } else if( input < 0x10B36 ) {
                                        goto _488;/* ['𐬀', '𐬵'] */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x10B40: 
                                        case 0x10B41: 
                                        case 0x10B42: 
                                        case 0x10B43: 
                                        case 0x10B44: 
                                        case 0x10B45: 
                                        case 0x10B46: 
                                        case 0x10B47: 
                                        case 0x10B48: 
                                        case 0x10B49: 
                                        case 0x10B4A: 
                                        case 0x10B4B: 
                                        case 0x10B4C: 
                                        case 0x10B4D: 
                                        case 0x10B4E: 
                                        case 0x10B4F: 
                                        case 0x10B50: 
                                        case 0x10B51: 
                                        case 0x10B52: 
                                        case 0x10B53: 
                                        case 0x10B54: 
                                        case 0x10B55: goto _488;/* ['𐭀', '𐭕'] */

                                        case 0x10B60: 
                                        case 0x10B61: 
                                        case 0x10B62: 
                                        case 0x10B63: 
                                        case 0x10B64: 
                                        case 0x10B65: 
                                        case 0x10B66: 
                                        case 0x10B67: 
                                        case 0x10B68: 
                                        case 0x10B69: 
                                        case 0x10B6A: 
                                        case 0x10B6B: 
                                        case 0x10B6C: 
                                        case 0x10B6D: 
                                        case 0x10B6E: 
                                        case 0x10B6F: 
                                        case 0x10B70: 
                                        case 0x10B71: 
                                        case 0x10B72: goto _488;/* ['𐭠', '𐭲'] */


                                    }
                                }
                            } else {
                                if( input < 0x11083 ) {
                                    if( input < 0x10C49 ) {
                                        goto _488;/* ['𐰀', '𐱈'] */

                                    } else if( input < 0x11003 ) {

                                    } else if( input < 0x11038 ) {
                                        goto _488;/* ['𑀃', '𑀷'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x110B0 ) {
                                        goto _488;/* ['𑂃', '𑂯'] */

                                    } else if( input < 0x12000 ) {

                                    } else if( input < 0x1236F ) {
                                        goto _488;/* ['𒀀', '𒍮'] */

                                    } else {

                                    }
                                }
                            }
                        } else {
                            if( input < 0x1B002 ) {
                                if( input < 0x1342F ) {
                                    if( input < 0x12463 ) {
                                        goto _488;/* ['𒐀', '𒑢'] */

                                    } else if( input < 0x13000 ) {

                                    } else {
                                        goto _488;/* ['𓀀', '𓐮'] */

                                    }
                                } else {
                                    if( input < 0x16800 ) {

                                    } else if( input < 0x16A39 ) {
                                        goto _488;/* ['𖠀', '𖨸'] */

                                    } else if( input < 0x1B000 ) {

                                    } else {
                                        goto _488;/* ['𛀀', '𛀁'] */

                                    }
                                }
                            } else {
                                if( input < 0x1D49D ) {
                                    if( input < 0x1D400 ) {

                                    } else if( input < 0x1D455 ) {
                                        goto _488;/* ['𝐀', '𝑔'] */

                                    } else if( input == 0x1D455 ) {

                                    } else {
                                        goto _488;/* ['𝑖', '𝒜'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1D49E: 
                                        case 0x1D49F: goto _488;/* ['𝒞', '𝒟'] */

                                        case 0x1D4A2: goto _488;/* '𝒢' */


                                    }
                                }
                            }
                        }
                    }
                } else {
                    if( input < 0x1D6A6 ) {
                        if( input < 0x1D50D ) {
                            switch( input ) {
                                case 0x1D4A5: 
                                case 0x1D4A6: goto _488;/* ['𝒥', '𝒦'] */

                                case 0x1D4A9: 
                                case 0x1D4AA: 
                                case 0x1D4AB: 
                                case 0x1D4AC: goto _488;/* ['𝒩', '𝒬'] */

                                case 0x1D4AE: 
                                case 0x1D4AF: 
                                case 0x1D4B0: 
                                case 0x1D4B1: 
                                case 0x1D4B2: 
                                case 0x1D4B3: 
                                case 0x1D4B4: 
                                case 0x1D4B5: 
                                case 0x1D4B6: 
                                case 0x1D4B7: 
                                case 0x1D4B8: 
                                case 0x1D4B9: goto _488;/* ['𝒮', '𝒹'] */

                                case 0x1D4BB: goto _488;/* '𝒻' */

                                case 0x1D4BD: 
                                case 0x1D4BE: 
                                case 0x1D4BF: 
                                case 0x1D4C0: 
                                case 0x1D4C1: 
                                case 0x1D4C2: 
                                case 0x1D4C3: goto _488;/* ['𝒽', '𝓃'] */

                                case 0x1D4C5: 
                                case 0x1D4C6: 
                                case 0x1D4C7: 
                                case 0x1D4C8: 
                                case 0x1D4C9: 
                                case 0x1D4CA: 
                                case 0x1D4CB: 
                                case 0x1D4CC: 
                                case 0x1D4CD: 
                                case 0x1D4CE: 
                                case 0x1D4CF: 
                                case 0x1D4D0: 
                                case 0x1D4D1: 
                                case 0x1D4D2: 
                                case 0x1D4D3: 
                                case 0x1D4D4: 
                                case 0x1D4D5: 
                                case 0x1D4D6: 
                                case 0x1D4D7: 
                                case 0x1D4D8: 
                                case 0x1D4D9: 
                                case 0x1D4DA: 
                                case 0x1D4DB: 
                                case 0x1D4DC: 
                                case 0x1D4DD: 
                                case 0x1D4DE: 
                                case 0x1D4DF: 
                                case 0x1D4E0: 
                                case 0x1D4E1: 
                                case 0x1D4E2: 
                                case 0x1D4E3: 
                                case 0x1D4E4: 
                                case 0x1D4E5: 
                                case 0x1D4E6: 
                                case 0x1D4E7: 
                                case 0x1D4E8: 
                                case 0x1D4E9: 
                                case 0x1D4EA: 
                                case 0x1D4EB: 
                                case 0x1D4EC: 
                                case 0x1D4ED: 
                                case 0x1D4EE: 
                                case 0x1D4EF: 
                                case 0x1D4F0: 
                                case 0x1D4F1: 
                                case 0x1D4F2: 
                                case 0x1D4F3: 
                                case 0x1D4F4: 
                                case 0x1D4F5: 
                                case 0x1D4F6: 
                                case 0x1D4F7: 
                                case 0x1D4F8: 
                                case 0x1D4F9: 
                                case 0x1D4FA: 
                                case 0x1D4FB: 
                                case 0x1D4FC: 
                                case 0x1D4FD: 
                                case 0x1D4FE: 
                                case 0x1D4FF: 
                                case 0x1D500: 
                                case 0x1D501: 
                                case 0x1D502: 
                                case 0x1D503: 
                                case 0x1D504: 
                                case 0x1D505: goto _488;/* ['𝓅', '𝔅'] */

                                case 0x1D507: 
                                case 0x1D508: 
                                case 0x1D509: 
                                case 0x1D50A: goto _488;/* ['𝔇', '𝔊'] */


                            }
                        } else {
                            if( input < 0x1D53F ) {
                                switch( input ) {
                                    case 0x1D50D: 
                                    case 0x1D50E: 
                                    case 0x1D50F: 
                                    case 0x1D510: 
                                    case 0x1D511: 
                                    case 0x1D512: 
                                    case 0x1D513: 
                                    case 0x1D514: goto _488;/* ['𝔍', '𝔔'] */

                                    case 0x1D516: 
                                    case 0x1D517: 
                                    case 0x1D518: 
                                    case 0x1D519: 
                                    case 0x1D51A: 
                                    case 0x1D51B: 
                                    case 0x1D51C: goto _488;/* ['𝔖', '𝔜'] */

                                    case 0x1D51E: 
                                    case 0x1D51F: 
                                    case 0x1D520: 
                                    case 0x1D521: 
                                    case 0x1D522: 
                                    case 0x1D523: 
                                    case 0x1D524: 
                                    case 0x1D525: 
                                    case 0x1D526: 
                                    case 0x1D527: 
                                    case 0x1D528: 
                                    case 0x1D529: 
                                    case 0x1D52A: 
                                    case 0x1D52B: 
                                    case 0x1D52C: 
                                    case 0x1D52D: 
                                    case 0x1D52E: 
                                    case 0x1D52F: 
                                    case 0x1D530: 
                                    case 0x1D531: 
                                    case 0x1D532: 
                                    case 0x1D533: 
                                    case 0x1D534: 
                                    case 0x1D535: 
                                    case 0x1D536: 
                                    case 0x1D537: 
                                    case 0x1D538: 
                                    case 0x1D539: goto _488;/* ['𝔞', '𝔹'] */

                                    case 0x1D53B: 
                                    case 0x1D53C: 
                                    case 0x1D53D: 
                                    case 0x1D53E: goto _488;/* ['𝔻', '𝔾'] */


                                }
                            } else {
                                if( input < 0x1D547 ) {
                                    switch( input ) {
                                        case 0x1D540: 
                                        case 0x1D541: 
                                        case 0x1D542: 
                                        case 0x1D543: 
                                        case 0x1D544: goto _488;/* ['𝕀', '𝕄'] */

                                        case 0x1D546: goto _488;/* '𝕆' */


                                    }
                                } else {
                                    if( input < 0x1D54A ) {

                                    } else if( input < 0x1D551 ) {
                                        goto _488;/* ['𝕊', '𝕐'] */

                                    } else if( input == 0x1D551 ) {

                                    } else {
                                        goto _488;/* ['𝕒', '𝚥'] */

                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0x1D770 ) {
                            if( input < 0x1D6FC ) {
                                switch( input ) {
                                    case 0x1D6A8: 
                                    case 0x1D6A9: 
                                    case 0x1D6AA: 
                                    case 0x1D6AB: 
                                    case 0x1D6AC: 
                                    case 0x1D6AD: 
                                    case 0x1D6AE: 
                                    case 0x1D6AF: 
                                    case 0x1D6B0: 
                                    case 0x1D6B1: 
                                    case 0x1D6B2: 
                                    case 0x1D6B3: 
                                    case 0x1D6B4: 
                                    case 0x1D6B5: 
                                    case 0x1D6B6: 
                                    case 0x1D6B7: 
                                    case 0x1D6B8: 
                                    case 0x1D6B9: 
                                    case 0x1D6BA: 
                                    case 0x1D6BB: 
                                    case 0x1D6BC: 
                                    case 0x1D6BD: 
                                    case 0x1D6BE: 
                                    case 0x1D6BF: 
                                    case 0x1D6C0: goto _488;/* ['𝚨', '𝛀'] */

                                    case 0x1D6C2: 
                                    case 0x1D6C3: 
                                    case 0x1D6C4: 
                                    case 0x1D6C5: 
                                    case 0x1D6C6: 
                                    case 0x1D6C7: 
                                    case 0x1D6C8: 
                                    case 0x1D6C9: 
                                    case 0x1D6CA: 
                                    case 0x1D6CB: 
                                    case 0x1D6CC: 
                                    case 0x1D6CD: 
                                    case 0x1D6CE: 
                                    case 0x1D6CF: 
                                    case 0x1D6D0: 
                                    case 0x1D6D1: 
                                    case 0x1D6D2: 
                                    case 0x1D6D3: 
                                    case 0x1D6D4: 
                                    case 0x1D6D5: 
                                    case 0x1D6D6: 
                                    case 0x1D6D7: 
                                    case 0x1D6D8: 
                                    case 0x1D6D9: 
                                    case 0x1D6DA: goto _488;/* ['𝛂', '𝛚'] */

                                    case 0x1D6DC: 
                                    case 0x1D6DD: 
                                    case 0x1D6DE: 
                                    case 0x1D6DF: 
                                    case 0x1D6E0: 
                                    case 0x1D6E1: 
                                    case 0x1D6E2: 
                                    case 0x1D6E3: 
                                    case 0x1D6E4: 
                                    case 0x1D6E5: 
                                    case 0x1D6E6: 
                                    case 0x1D6E7: 
                                    case 0x1D6E8: 
                                    case 0x1D6E9: 
                                    case 0x1D6EA: 
                                    case 0x1D6EB: 
                                    case 0x1D6EC: 
                                    case 0x1D6ED: 
                                    case 0x1D6EE: 
                                    case 0x1D6EF: 
                                    case 0x1D6F0: 
                                    case 0x1D6F1: 
                                    case 0x1D6F2: 
                                    case 0x1D6F3: 
                                    case 0x1D6F4: 
                                    case 0x1D6F5: 
                                    case 0x1D6F6: 
                                    case 0x1D6F7: 
                                    case 0x1D6F8: 
                                    case 0x1D6F9: 
                                    case 0x1D6FA: goto _488;/* ['𝛜', '𝛺'] */


                                }
                            } else {
                                if( input < 0x1D736 ) {
                                    switch( input ) {
                                        case 0x1D6FC: 
                                        case 0x1D6FD: 
                                        case 0x1D6FE: 
                                        case 0x1D6FF: 
                                        case 0x1D700: 
                                        case 0x1D701: 
                                        case 0x1D702: 
                                        case 0x1D703: 
                                        case 0x1D704: 
                                        case 0x1D705: 
                                        case 0x1D706: 
                                        case 0x1D707: 
                                        case 0x1D708: 
                                        case 0x1D709: 
                                        case 0x1D70A: 
                                        case 0x1D70B: 
                                        case 0x1D70C: 
                                        case 0x1D70D: 
                                        case 0x1D70E: 
                                        case 0x1D70F: 
                                        case 0x1D710: 
                                        case 0x1D711: 
                                        case 0x1D712: 
                                        case 0x1D713: 
                                        case 0x1D714: goto _488;/* ['𝛼', '𝜔'] */

                                        case 0x1D716: 
                                        case 0x1D717: 
                                        case 0x1D718: 
                                        case 0x1D719: 
                                        case 0x1D71A: 
                                        case 0x1D71B: 
                                        case 0x1D71C: 
                                        case 0x1D71D: 
                                        case 0x1D71E: 
                                        case 0x1D71F: 
                                        case 0x1D720: 
                                        case 0x1D721: 
                                        case 0x1D722: 
                                        case 0x1D723: 
                                        case 0x1D724: 
                                        case 0x1D725: 
                                        case 0x1D726: 
                                        case 0x1D727: 
                                        case 0x1D728: 
                                        case 0x1D729: 
                                        case 0x1D72A: 
                                        case 0x1D72B: 
                                        case 0x1D72C: 
                                        case 0x1D72D: 
                                        case 0x1D72E: 
                                        case 0x1D72F: 
                                        case 0x1D730: 
                                        case 0x1D731: 
                                        case 0x1D732: 
                                        case 0x1D733: 
                                        case 0x1D734: goto _488;/* ['𝜖', '𝜴'] */


                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1D736: 
                                        case 0x1D737: 
                                        case 0x1D738: 
                                        case 0x1D739: 
                                        case 0x1D73A: 
                                        case 0x1D73B: 
                                        case 0x1D73C: 
                                        case 0x1D73D: 
                                        case 0x1D73E: 
                                        case 0x1D73F: 
                                        case 0x1D740: 
                                        case 0x1D741: 
                                        case 0x1D742: 
                                        case 0x1D743: 
                                        case 0x1D744: 
                                        case 0x1D745: 
                                        case 0x1D746: 
                                        case 0x1D747: 
                                        case 0x1D748: 
                                        case 0x1D749: 
                                        case 0x1D74A: 
                                        case 0x1D74B: 
                                        case 0x1D74C: 
                                        case 0x1D74D: 
                                        case 0x1D74E: goto _488;/* ['𝜶', '𝝎'] */

                                        case 0x1D750: 
                                        case 0x1D751: 
                                        case 0x1D752: 
                                        case 0x1D753: 
                                        case 0x1D754: 
                                        case 0x1D755: 
                                        case 0x1D756: 
                                        case 0x1D757: 
                                        case 0x1D758: 
                                        case 0x1D759: 
                                        case 0x1D75A: 
                                        case 0x1D75B: 
                                        case 0x1D75C: 
                                        case 0x1D75D: 
                                        case 0x1D75E: 
                                        case 0x1D75F: 
                                        case 0x1D760: 
                                        case 0x1D761: 
                                        case 0x1D762: 
                                        case 0x1D763: 
                                        case 0x1D764: 
                                        case 0x1D765: 
                                        case 0x1D766: 
                                        case 0x1D767: 
                                        case 0x1D768: 
                                        case 0x1D769: 
                                        case 0x1D76A: 
                                        case 0x1D76B: 
                                        case 0x1D76C: 
                                        case 0x1D76D: 
                                        case 0x1D76E: goto _488;/* ['𝝐', '𝝮'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0x20000 ) {
                                switch( input ) {
                                    case 0x1D770: 
                                    case 0x1D771: 
                                    case 0x1D772: 
                                    case 0x1D773: 
                                    case 0x1D774: 
                                    case 0x1D775: 
                                    case 0x1D776: 
                                    case 0x1D777: 
                                    case 0x1D778: 
                                    case 0x1D779: 
                                    case 0x1D77A: 
                                    case 0x1D77B: 
                                    case 0x1D77C: 
                                    case 0x1D77D: 
                                    case 0x1D77E: 
                                    case 0x1D77F: 
                                    case 0x1D780: 
                                    case 0x1D781: 
                                    case 0x1D782: 
                                    case 0x1D783: 
                                    case 0x1D784: 
                                    case 0x1D785: 
                                    case 0x1D786: 
                                    case 0x1D787: 
                                    case 0x1D788: goto _488;/* ['𝝰', '𝞈'] */

                                    case 0x1D78A: 
                                    case 0x1D78B: 
                                    case 0x1D78C: 
                                    case 0x1D78D: 
                                    case 0x1D78E: 
                                    case 0x1D78F: 
                                    case 0x1D790: 
                                    case 0x1D791: 
                                    case 0x1D792: 
                                    case 0x1D793: 
                                    case 0x1D794: 
                                    case 0x1D795: 
                                    case 0x1D796: 
                                    case 0x1D797: 
                                    case 0x1D798: 
                                    case 0x1D799: 
                                    case 0x1D79A: 
                                    case 0x1D79B: 
                                    case 0x1D79C: 
                                    case 0x1D79D: 
                                    case 0x1D79E: 
                                    case 0x1D79F: 
                                    case 0x1D7A0: 
                                    case 0x1D7A1: 
                                    case 0x1D7A2: 
                                    case 0x1D7A3: 
                                    case 0x1D7A4: 
                                    case 0x1D7A5: 
                                    case 0x1D7A6: 
                                    case 0x1D7A7: 
                                    case 0x1D7A8: goto _488;/* ['𝞊', '𝞨'] */

                                    case 0x1D7AA: 
                                    case 0x1D7AB: 
                                    case 0x1D7AC: 
                                    case 0x1D7AD: 
                                    case 0x1D7AE: 
                                    case 0x1D7AF: 
                                    case 0x1D7B0: 
                                    case 0x1D7B1: 
                                    case 0x1D7B2: 
                                    case 0x1D7B3: 
                                    case 0x1D7B4: 
                                    case 0x1D7B5: 
                                    case 0x1D7B6: 
                                    case 0x1D7B7: 
                                    case 0x1D7B8: 
                                    case 0x1D7B9: 
                                    case 0x1D7BA: 
                                    case 0x1D7BB: 
                                    case 0x1D7BC: 
                                    case 0x1D7BD: 
                                    case 0x1D7BE: 
                                    case 0x1D7BF: 
                                    case 0x1D7C0: 
                                    case 0x1D7C1: 
                                    case 0x1D7C2: goto _488;/* ['𝞪', '𝟂'] */

                                    case 0x1D7C4: 
                                    case 0x1D7C5: 
                                    case 0x1D7C6: 
                                    case 0x1D7C7: 
                                    case 0x1D7C8: 
                                    case 0x1D7C9: 
                                    case 0x1D7CA: 
                                    case 0x1D7CB: goto _488;/* ['𝟄', '𝟋'] */


                                }
                            } else {
                                if( input < 0x2B740 ) {
                                    if( input < 0x2A6D7 ) {
                                        goto _488;/* ['𠀀', '𪛖'] */

                                    } else if( input < 0x2A700 ) {

                                    } else if( input < 0x2B735 ) {
                                        goto _488;/* ['𪜀', '𫜴'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x2B81E ) {
                                        goto _488;/* ['𫝀', '𫠝'] */

                                    } else if( input < 0x2F800 ) {

                                    } else if( input < 0x2FA1E ) {
                                        goto _488;/* ['丽', '𪘀'] */

                                    } else {

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    __quex_debug_drop_out(455);

goto _490; /* TERMINAL_FAILURE */

_455:


    ++(me->buffer._input_p);
    goto _484;
#   define __QUEX_DEBUG_MAP_STATE_KEY_TO_STATE(X) ( \
             (X) == 0 ? 458 :    \
             (X) == 1 ? 474 :    \
             (X) == 2 ? 466 :    \
             (X) == 3 ? 471 : 0)

    __quex_assert_no_passage();
_486: /* (458 from 466) (458 from 455) */
    state_key = 0;
    __quex_debug("state_key = 0\n");
    goto _482;
_488: /* (471 from 455) (471 from 466) */
    state_key = 3;
    __quex_debug("state_key = 3\n");
    goto _482;
_491: /* (474 from 466) (474 from 458) */
    state_key = 1;
    __quex_debug("state_key = 1\n");
    goto _482;
_487: /* (466 from 455) */
    state_key = 2;
    __quex_debug("state_key = 2\n");

_482: /* (458 from 458) (474 from 474) (466 from 466) (471 from 471) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_template_state(482, state_key);
    if( input < 0x1975 ) {
        if( input < 0xC0E ) {
            if( input < 0x9D8 ) {
                if( input < 0x5C0 ) {
                    if( input < 0x2EC ) {
                        if( input < 0xB8 ) {
                            switch( input ) {
                                case 0x2E: QUEX_GOTO_STATE(template_482_target_0[state_key]);/* '.' */

                                case 0x30: 
                                case 0x31: 
                                case 0x32: 
                                case 0x33: 
                                case 0x34: 
                                case 0x35: 
                                case 0x36: 
                                case 0x37: 
                                case 0x38: 
                                case 0x39: goto _482;/* ['0', '9'] */

                                case 0x41: 
                                case 0x42: 
                                case 0x43: 
                                case 0x44: 
                                case 0x45: 
                                case 0x46: 
                                case 0x47: 
                                case 0x48: 
                                case 0x49: 
                                case 0x4A: 
                                case 0x4B: 
                                case 0x4C: 
                                case 0x4D: 
                                case 0x4E: 
                                case 0x4F: 
                                case 0x50: 
                                case 0x51: 
                                case 0x52: 
                                case 0x53: 
                                case 0x54: 
                                case 0x55: 
                                case 0x56: 
                                case 0x57: 
                                case 0x58: 
                                case 0x59: 
                                case 0x5A: goto _482;/* ['A', 'Z'] */

                                case 0x5F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '_' */

                                case 0x61: 
                                case 0x62: 
                                case 0x63: 
                                case 0x64: 
                                case 0x65: 
                                case 0x66: 
                                case 0x67: 
                                case 0x68: 
                                case 0x69: 
                                case 0x6A: 
                                case 0x6B: 
                                case 0x6C: 
                                case 0x6D: 
                                case 0x6E: 
                                case 0x6F: 
                                case 0x70: 
                                case 0x71: 
                                case 0x72: 
                                case 0x73: 
                                case 0x74: 
                                case 0x75: 
                                case 0x76: 
                                case 0x77: 
                                case 0x78: 
                                case 0x79: 
                                case 0x7A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['a', 'z'] */

                                case 0xAA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ª' */

                                case 0xB5: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'µ' */

                                case 0xB7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '·' */


                            }
                        } else {
                            if( input < 0xFE ) {
                                switch( input ) {
                                    case 0xBA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'º' */

                                    case 0xC0: 
                                    case 0xC1: 
                                    case 0xC2: 
                                    case 0xC3: 
                                    case 0xC4: 
                                    case 0xC5: 
                                    case 0xC6: 
                                    case 0xC7: 
                                    case 0xC8: 
                                    case 0xC9: 
                                    case 0xCA: 
                                    case 0xCB: 
                                    case 0xCC: 
                                    case 0xCD: 
                                    case 0xCE: 
                                    case 0xCF: 
                                    case 0xD0: 
                                    case 0xD1: 
                                    case 0xD2: 
                                    case 0xD3: 
                                    case 0xD4: 
                                    case 0xD5: 
                                    case 0xD6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['À', 'Ö'] */

                                    case 0xD8: 
                                    case 0xD9: 
                                    case 0xDA: 
                                    case 0xDB: 
                                    case 0xDC: 
                                    case 0xDD: 
                                    case 0xDE: 
                                    case 0xDF: 
                                    case 0xE0: 
                                    case 0xE1: 
                                    case 0xE2: 
                                    case 0xE3: 
                                    case 0xE4: 
                                    case 0xE5: 
                                    case 0xE6: 
                                    case 0xE7: 
                                    case 0xE8: 
                                    case 0xE9: 
                                    case 0xEA: 
                                    case 0xEB: 
                                    case 0xEC: 
                                    case 0xED: 
                                    case 0xEE: 
                                    case 0xEF: 
                                    case 0xF0: 
                                    case 0xF1: 
                                    case 0xF2: 
                                    case 0xF3: 
                                    case 0xF4: 
                                    case 0xF5: 
                                    case 0xF6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ø', 'ö'] */

                                    case 0xF8: 
                                    case 0xF9: 
                                    case 0xFA: 
                                    case 0xFB: 
                                    case 0xFC: 
                                    case 0xFD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ø', 'ý'] */


                                }
                            } else {
                                if( input < 0x2C6 ) {
                                    if( input >= 0x2C2 ) {

                                    } else if( input >= 0x100 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ā', 'ˁ'] */

                                    } else if( input == 0xFF ) {
                                        QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 482, 492);/* 'ÿ' */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x2C6: 
                                        case 0x2C7: 
                                        case 0x2C8: 
                                        case 0x2C9: 
                                        case 0x2CA: 
                                        case 0x2CB: 
                                        case 0x2CC: 
                                        case 0x2CD: 
                                        case 0x2CE: 
                                        case 0x2CF: 
                                        case 0x2D0: 
                                        case 0x2D1: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ˆ', 'ˑ'] */

                                        case 0x2E0: 
                                        case 0x2E1: 
                                        case 0x2E2: 
                                        case 0x2E3: 
                                        case 0x2E4: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ˠ', 'ˤ'] */


                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0x3A3 ) {
                            if( input < 0x37B ) {
                                if( input < 0x300 ) {
                                    switch( input ) {
                                        case 0x2EC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ˬ' */

                                        case 0x2EE: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ˮ' */


                                    }
                                } else {
                                    if( input < 0x375 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['̀', 'ʹ'] */

                                    } else if( input == 0x375 ) {

                                    } else if( input < 0x378 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ͷ', 'ͷ'] */

                                    } else {

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x37B: 
                                    case 0x37C: 
                                    case 0x37D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ͻ', 'ͽ'] */

                                    case 0x386: 
                                    case 0x387: 
                                    case 0x388: 
                                    case 0x389: 
                                    case 0x38A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ά', 'Ί'] */

                                    case 0x38C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'Ό' */

                                    case 0x38E: 
                                    case 0x38F: 
                                    case 0x390: 
                                    case 0x391: 
                                    case 0x392: 
                                    case 0x393: 
                                    case 0x394: 
                                    case 0x395: 
                                    case 0x396: 
                                    case 0x397: 
                                    case 0x398: 
                                    case 0x399: 
                                    case 0x39A: 
                                    case 0x39B: 
                                    case 0x39C: 
                                    case 0x39D: 
                                    case 0x39E: 
                                    case 0x39F: 
                                    case 0x3A0: 
                                    case 0x3A1: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ύ', 'Ρ'] */


                                }
                            }
                        } else {
                            if( input < 0x531 ) {
                                if( input < 0x483 ) {
                                    if( input < 0x3F6 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Σ', 'ϵ'] */

                                    } else if( input == 0x3F6 ) {

                                    } else if( input < 0x482 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ϸ', 'ҁ'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x488 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['҃', '҇'] */

                                    } else if( input < 0x48A ) {

                                    } else if( input < 0x528 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ҋ', 'ԧ'] */

                                    } else {

                                    }
                                }
                            } else {
                                if( input < 0x561 ) {
                                    switch( input ) {
                                        case 0x531: 
                                        case 0x532: 
                                        case 0x533: 
                                        case 0x534: 
                                        case 0x535: 
                                        case 0x536: 
                                        case 0x537: 
                                        case 0x538: 
                                        case 0x539: 
                                        case 0x53A: 
                                        case 0x53B: 
                                        case 0x53C: 
                                        case 0x53D: 
                                        case 0x53E: 
                                        case 0x53F: 
                                        case 0x540: 
                                        case 0x541: 
                                        case 0x542: 
                                        case 0x543: 
                                        case 0x544: 
                                        case 0x545: 
                                        case 0x546: 
                                        case 0x547: 
                                        case 0x548: 
                                        case 0x549: 
                                        case 0x54A: 
                                        case 0x54B: 
                                        case 0x54C: 
                                        case 0x54D: 
                                        case 0x54E: 
                                        case 0x54F: 
                                        case 0x550: 
                                        case 0x551: 
                                        case 0x552: 
                                        case 0x553: 
                                        case 0x554: 
                                        case 0x555: 
                                        case 0x556: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ա', 'Ֆ'] */

                                        case 0x559: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ՙ' */


                                    }
                                } else {
                                    if( input < 0x588 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ա', 'և'] */

                                    } else if( input < 0x591 ) {

                                    } else if( input < 0x5BE ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['֑', 'ֽ'] */

                                    } else if( input == 0x5BE ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ֿ' */

                                    }
                                }
                            }
                        }
                    }
                } else {
                    if( input < 0x800 ) {
                        if( input < 0x6D4 ) {
                            if( input < 0x5EB ) {
                                switch( input ) {
                                    case 0x5C1: 
                                    case 0x5C2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ׁ', 'ׂ'] */

                                    case 0x5C4: 
                                    case 0x5C5: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ׄ', 'ׅ'] */

                                    case 0x5C7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ׇ' */

                                    case 0x5D0: 
                                    case 0x5D1: 
                                    case 0x5D2: 
                                    case 0x5D3: 
                                    case 0x5D4: 
                                    case 0x5D5: 
                                    case 0x5D6: 
                                    case 0x5D7: 
                                    case 0x5D8: 
                                    case 0x5D9: 
                                    case 0x5DA: 
                                    case 0x5DB: 
                                    case 0x5DC: 
                                    case 0x5DD: 
                                    case 0x5DE: 
                                    case 0x5DF: 
                                    case 0x5E0: 
                                    case 0x5E1: 
                                    case 0x5E2: 
                                    case 0x5E3: 
                                    case 0x5E4: 
                                    case 0x5E5: 
                                    case 0x5E6: 
                                    case 0x5E7: 
                                    case 0x5E8: 
                                    case 0x5E9: 
                                    case 0x5EA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['א', 'ת'] */


                                }
                            } else {
                                if( input < 0x61B ) {
                                    switch( input ) {
                                        case 0x5F0: 
                                        case 0x5F1: 
                                        case 0x5F2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['װ', 'ײ'] */

                                        case 0x610: 
                                        case 0x611: 
                                        case 0x612: 
                                        case 0x613: 
                                        case 0x614: 
                                        case 0x615: 
                                        case 0x616: 
                                        case 0x617: 
                                        case 0x618: 
                                        case 0x619: 
                                        case 0x61A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ؐ', 'ؚ'] */


                                    }
                                } else {
                                    if( input < 0x620 ) {

                                    } else if( input < 0x66A ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ؠ', '٩'] */

                                    } else if( input < 0x66E ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ٮ', 'ۓ'] */

                                    }
                                }
                            }
                        } else {
                            if( input < 0x700 ) {
                                switch( input ) {
                                    case 0x6D5: 
                                    case 0x6D6: 
                                    case 0x6D7: 
                                    case 0x6D8: 
                                    case 0x6D9: 
                                    case 0x6DA: 
                                    case 0x6DB: 
                                    case 0x6DC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ە', 'ۜ'] */

                                    case 0x6DF: 
                                    case 0x6E0: 
                                    case 0x6E1: 
                                    case 0x6E2: 
                                    case 0x6E3: 
                                    case 0x6E4: 
                                    case 0x6E5: 
                                    case 0x6E6: 
                                    case 0x6E7: 
                                    case 0x6E8: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['۟', 'ۨ'] */

                                    case 0x6EA: 
                                    case 0x6EB: 
                                    case 0x6EC: 
                                    case 0x6ED: 
                                    case 0x6EE: 
                                    case 0x6EF: 
                                    case 0x6F0: 
                                    case 0x6F1: 
                                    case 0x6F2: 
                                    case 0x6F3: 
                                    case 0x6F4: 
                                    case 0x6F5: 
                                    case 0x6F6: 
                                    case 0x6F7: 
                                    case 0x6F8: 
                                    case 0x6F9: 
                                    case 0x6FA: 
                                    case 0x6FB: 
                                    case 0x6FC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['۪', 'ۼ'] */

                                    case 0x6FF: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ۿ' */


                                }
                            } else {
                                if( input < 0x7B2 ) {
                                    if( input < 0x710 ) {

                                    } else if( input < 0x74B ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ܐ', '݊'] */

                                    } else if( input < 0x74D ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ݍ', 'ޱ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x7C0: 
                                        case 0x7C1: 
                                        case 0x7C2: 
                                        case 0x7C3: 
                                        case 0x7C4: 
                                        case 0x7C5: 
                                        case 0x7C6: 
                                        case 0x7C7: 
                                        case 0x7C8: 
                                        case 0x7C9: 
                                        case 0x7CA: 
                                        case 0x7CB: 
                                        case 0x7CC: 
                                        case 0x7CD: 
                                        case 0x7CE: 
                                        case 0x7CF: 
                                        case 0x7D0: 
                                        case 0x7D1: 
                                        case 0x7D2: 
                                        case 0x7D3: 
                                        case 0x7D4: 
                                        case 0x7D5: 
                                        case 0x7D6: 
                                        case 0x7D7: 
                                        case 0x7D8: 
                                        case 0x7D9: 
                                        case 0x7DA: 
                                        case 0x7DB: 
                                        case 0x7DC: 
                                        case 0x7DD: 
                                        case 0x7DE: 
                                        case 0x7DF: 
                                        case 0x7E0: 
                                        case 0x7E1: 
                                        case 0x7E2: 
                                        case 0x7E3: 
                                        case 0x7E4: 
                                        case 0x7E5: 
                                        case 0x7E6: 
                                        case 0x7E7: 
                                        case 0x7E8: 
                                        case 0x7E9: 
                                        case 0x7EA: 
                                        case 0x7EB: 
                                        case 0x7EC: 
                                        case 0x7ED: 
                                        case 0x7EE: 
                                        case 0x7EF: 
                                        case 0x7F0: 
                                        case 0x7F1: 
                                        case 0x7F2: 
                                        case 0x7F3: 
                                        case 0x7F4: 
                                        case 0x7F5: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['߀', 'ߵ'] */

                                        case 0x7FA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ߺ' */


                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0x98F ) {
                            if( input < 0x971 ) {
                                if( input < 0x900 ) {
                                    if( input < 0x82E ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ࠀ', '࠭'] */

                                    } else if( input < 0x840 ) {

                                    } else if( input < 0x85C ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ࡀ', '࡛'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x964 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ऀ', 'ॣ'] */

                                    } else if( input < 0x966 ) {

                                    } else if( input < 0x970 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['०', '९'] */

                                    } else {

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x971: 
                                    case 0x972: 
                                    case 0x973: 
                                    case 0x974: 
                                    case 0x975: 
                                    case 0x976: 
                                    case 0x977: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ॱ', 'ॷ'] */

                                    case 0x979: 
                                    case 0x97A: 
                                    case 0x97B: 
                                    case 0x97C: 
                                    case 0x97D: 
                                    case 0x97E: 
                                    case 0x97F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ॹ', 'ॿ'] */

                                    case 0x981: 
                                    case 0x982: 
                                    case 0x983: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ঁ', 'ঃ'] */

                                    case 0x985: 
                                    case 0x986: 
                                    case 0x987: 
                                    case 0x988: 
                                    case 0x989: 
                                    case 0x98A: 
                                    case 0x98B: 
                                    case 0x98C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['অ', 'ঌ'] */


                                }
                            }
                        } else {
                            switch( input ) {
                                case 0x98F: 
                                case 0x990: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['এ', 'ঐ'] */

                                case 0x993: 
                                case 0x994: 
                                case 0x995: 
                                case 0x996: 
                                case 0x997: 
                                case 0x998: 
                                case 0x999: 
                                case 0x99A: 
                                case 0x99B: 
                                case 0x99C: 
                                case 0x99D: 
                                case 0x99E: 
                                case 0x99F: 
                                case 0x9A0: 
                                case 0x9A1: 
                                case 0x9A2: 
                                case 0x9A3: 
                                case 0x9A4: 
                                case 0x9A5: 
                                case 0x9A6: 
                                case 0x9A7: 
                                case 0x9A8: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ও', 'ন'] */

                                case 0x9AA: 
                                case 0x9AB: 
                                case 0x9AC: 
                                case 0x9AD: 
                                case 0x9AE: 
                                case 0x9AF: 
                                case 0x9B0: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['প', 'র'] */

                                case 0x9B2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ল' */

                                case 0x9B6: 
                                case 0x9B7: 
                                case 0x9B8: 
                                case 0x9B9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['শ', 'হ'] */

                                case 0x9BC: 
                                case 0x9BD: 
                                case 0x9BE: 
                                case 0x9BF: 
                                case 0x9C0: 
                                case 0x9C1: 
                                case 0x9C2: 
                                case 0x9C3: 
                                case 0x9C4: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['়', 'ৄ'] */

                                case 0x9C7: 
                                case 0x9C8: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ে', 'ৈ'] */

                                case 0x9CB: 
                                case 0x9CC: 
                                case 0x9CD: 
                                case 0x9CE: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ো', 'ৎ'] */

                                case 0x9D7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ৗ' */


                            }
                        }
                    }
                }
            } else {
                if( input < 0xB01 ) {
                    switch( input ) {
                        case 0x9DC: 
                        case 0x9DD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ড়', 'ঢ়'] */

                        case 0x9DF: 
                        case 0x9E0: 
                        case 0x9E1: 
                        case 0x9E2: 
                        case 0x9E3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['য়', 'ৣ'] */

                        case 0x9E6: 
                        case 0x9E7: 
                        case 0x9E8: 
                        case 0x9E9: 
                        case 0x9EA: 
                        case 0x9EB: 
                        case 0x9EC: 
                        case 0x9ED: 
                        case 0x9EE: 
                        case 0x9EF: 
                        case 0x9F0: 
                        case 0x9F1: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['০', 'ৱ'] */

                        case 0xA01: 
                        case 0xA02: 
                        case 0xA03: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਁ', 'ਃ'] */

                        case 0xA05: 
                        case 0xA06: 
                        case 0xA07: 
                        case 0xA08: 
                        case 0xA09: 
                        case 0xA0A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਅ', 'ਊ'] */

                        case 0xA0F: 
                        case 0xA10: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਏ', 'ਐ'] */

                        case 0xA13: 
                        case 0xA14: 
                        case 0xA15: 
                        case 0xA16: 
                        case 0xA17: 
                        case 0xA18: 
                        case 0xA19: 
                        case 0xA1A: 
                        case 0xA1B: 
                        case 0xA1C: 
                        case 0xA1D: 
                        case 0xA1E: 
                        case 0xA1F: 
                        case 0xA20: 
                        case 0xA21: 
                        case 0xA22: 
                        case 0xA23: 
                        case 0xA24: 
                        case 0xA25: 
                        case 0xA26: 
                        case 0xA27: 
                        case 0xA28: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਓ', 'ਨ'] */

                        case 0xA2A: 
                        case 0xA2B: 
                        case 0xA2C: 
                        case 0xA2D: 
                        case 0xA2E: 
                        case 0xA2F: 
                        case 0xA30: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਪ', 'ਰ'] */

                        case 0xA32: 
                        case 0xA33: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਲ', 'ਲ਼'] */

                        case 0xA35: 
                        case 0xA36: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਵ', 'ਸ਼'] */

                        case 0xA38: 
                        case 0xA39: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਸ', 'ਹ'] */

                        case 0xA3C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '਼' */

                        case 0xA3E: 
                        case 0xA3F: 
                        case 0xA40: 
                        case 0xA41: 
                        case 0xA42: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਾ', 'ੂ'] */

                        case 0xA47: 
                        case 0xA48: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ੇ', 'ੈ'] */

                        case 0xA4B: 
                        case 0xA4C: 
                        case 0xA4D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ੋ', '੍'] */

                        case 0xA51: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ੑ' */

                        case 0xA59: 
                        case 0xA5A: 
                        case 0xA5B: 
                        case 0xA5C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ਖ਼', 'ੜ'] */

                        case 0xA5E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ਫ਼' */

                        case 0xA66: 
                        case 0xA67: 
                        case 0xA68: 
                        case 0xA69: 
                        case 0xA6A: 
                        case 0xA6B: 
                        case 0xA6C: 
                        case 0xA6D: 
                        case 0xA6E: 
                        case 0xA6F: 
                        case 0xA70: 
                        case 0xA71: 
                        case 0xA72: 
                        case 0xA73: 
                        case 0xA74: 
                        case 0xA75: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['੦', 'ੵ'] */

                        case 0xA81: 
                        case 0xA82: 
                        case 0xA83: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ઁ', 'ઃ'] */

                        case 0xA85: 
                        case 0xA86: 
                        case 0xA87: 
                        case 0xA88: 
                        case 0xA89: 
                        case 0xA8A: 
                        case 0xA8B: 
                        case 0xA8C: 
                        case 0xA8D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['અ', 'ઍ'] */

                        case 0xA8F: 
                        case 0xA90: 
                        case 0xA91: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['એ', 'ઑ'] */

                        case 0xA93: 
                        case 0xA94: 
                        case 0xA95: 
                        case 0xA96: 
                        case 0xA97: 
                        case 0xA98: 
                        case 0xA99: 
                        case 0xA9A: 
                        case 0xA9B: 
                        case 0xA9C: 
                        case 0xA9D: 
                        case 0xA9E: 
                        case 0xA9F: 
                        case 0xAA0: 
                        case 0xAA1: 
                        case 0xAA2: 
                        case 0xAA3: 
                        case 0xAA4: 
                        case 0xAA5: 
                        case 0xAA6: 
                        case 0xAA7: 
                        case 0xAA8: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ઓ', 'ન'] */

                        case 0xAAA: 
                        case 0xAAB: 
                        case 0xAAC: 
                        case 0xAAD: 
                        case 0xAAE: 
                        case 0xAAF: 
                        case 0xAB0: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['પ', 'ર'] */

                        case 0xAB2: 
                        case 0xAB3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['લ', 'ળ'] */

                        case 0xAB5: 
                        case 0xAB6: 
                        case 0xAB7: 
                        case 0xAB8: 
                        case 0xAB9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['વ', 'હ'] */

                        case 0xABC: 
                        case 0xABD: 
                        case 0xABE: 
                        case 0xABF: 
                        case 0xAC0: 
                        case 0xAC1: 
                        case 0xAC2: 
                        case 0xAC3: 
                        case 0xAC4: 
                        case 0xAC5: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['઼', 'ૅ'] */

                        case 0xAC7: 
                        case 0xAC8: 
                        case 0xAC9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ે', 'ૉ'] */

                        case 0xACB: 
                        case 0xACC: 
                        case 0xACD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ો', '્'] */

                        case 0xAD0: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ૐ' */

                        case 0xAE0: 
                        case 0xAE1: 
                        case 0xAE2: 
                        case 0xAE3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ૠ', 'ૣ'] */

                        case 0xAE6: 
                        case 0xAE7: 
                        case 0xAE8: 
                        case 0xAE9: 
                        case 0xAEA: 
                        case 0xAEB: 
                        case 0xAEC: 
                        case 0xAED: 
                        case 0xAEE: 
                        case 0xAEF: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['૦', '૯'] */


                    }
                } else {
                    switch( input ) {
                        case 0xB01: 
                        case 0xB02: 
                        case 0xB03: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ଁ', 'ଃ'] */

                        case 0xB05: 
                        case 0xB06: 
                        case 0xB07: 
                        case 0xB08: 
                        case 0xB09: 
                        case 0xB0A: 
                        case 0xB0B: 
                        case 0xB0C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ଅ', 'ଌ'] */

                        case 0xB0F: 
                        case 0xB10: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ଏ', 'ଐ'] */

                        case 0xB13: 
                        case 0xB14: 
                        case 0xB15: 
                        case 0xB16: 
                        case 0xB17: 
                        case 0xB18: 
                        case 0xB19: 
                        case 0xB1A: 
                        case 0xB1B: 
                        case 0xB1C: 
                        case 0xB1D: 
                        case 0xB1E: 
                        case 0xB1F: 
                        case 0xB20: 
                        case 0xB21: 
                        case 0xB22: 
                        case 0xB23: 
                        case 0xB24: 
                        case 0xB25: 
                        case 0xB26: 
                        case 0xB27: 
                        case 0xB28: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ଓ', 'ନ'] */

                        case 0xB2A: 
                        case 0xB2B: 
                        case 0xB2C: 
                        case 0xB2D: 
                        case 0xB2E: 
                        case 0xB2F: 
                        case 0xB30: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ପ', 'ର'] */

                        case 0xB32: 
                        case 0xB33: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ଲ', 'ଳ'] */

                        case 0xB35: 
                        case 0xB36: 
                        case 0xB37: 
                        case 0xB38: 
                        case 0xB39: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ଵ', 'ହ'] */

                        case 0xB3C: 
                        case 0xB3D: 
                        case 0xB3E: 
                        case 0xB3F: 
                        case 0xB40: 
                        case 0xB41: 
                        case 0xB42: 
                        case 0xB43: 
                        case 0xB44: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['଼', 'ୄ'] */

                        case 0xB47: 
                        case 0xB48: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['େ', 'ୈ'] */

                        case 0xB4B: 
                        case 0xB4C: 
                        case 0xB4D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ୋ', '୍'] */

                        case 0xB56: 
                        case 0xB57: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ୖ', 'ୗ'] */

                        case 0xB5C: 
                        case 0xB5D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ଡ଼', 'ଢ଼'] */

                        case 0xB5F: 
                        case 0xB60: 
                        case 0xB61: 
                        case 0xB62: 
                        case 0xB63: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ୟ', 'ୣ'] */

                        case 0xB66: 
                        case 0xB67: 
                        case 0xB68: 
                        case 0xB69: 
                        case 0xB6A: 
                        case 0xB6B: 
                        case 0xB6C: 
                        case 0xB6D: 
                        case 0xB6E: 
                        case 0xB6F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['୦', '୯'] */

                        case 0xB71: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ୱ' */

                        case 0xB82: 
                        case 0xB83: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ஂ', 'ஃ'] */

                        case 0xB85: 
                        case 0xB86: 
                        case 0xB87: 
                        case 0xB88: 
                        case 0xB89: 
                        case 0xB8A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['அ', 'ஊ'] */

                        case 0xB8E: 
                        case 0xB8F: 
                        case 0xB90: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['எ', 'ஐ'] */

                        case 0xB92: 
                        case 0xB93: 
                        case 0xB94: 
                        case 0xB95: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ஒ', 'க'] */

                        case 0xB99: 
                        case 0xB9A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ங', 'ச'] */

                        case 0xB9C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ஜ' */

                        case 0xB9E: 
                        case 0xB9F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ஞ', 'ட'] */

                        case 0xBA3: 
                        case 0xBA4: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ண', 'த'] */

                        case 0xBA8: 
                        case 0xBA9: 
                        case 0xBAA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ந', 'ப'] */

                        case 0xBAE: 
                        case 0xBAF: 
                        case 0xBB0: 
                        case 0xBB1: 
                        case 0xBB2: 
                        case 0xBB3: 
                        case 0xBB4: 
                        case 0xBB5: 
                        case 0xBB6: 
                        case 0xBB7: 
                        case 0xBB8: 
                        case 0xBB9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ம', 'ஹ'] */

                        case 0xBBE: 
                        case 0xBBF: 
                        case 0xBC0: 
                        case 0xBC1: 
                        case 0xBC2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ா', 'ூ'] */

                        case 0xBC6: 
                        case 0xBC7: 
                        case 0xBC8: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ெ', 'ை'] */

                        case 0xBCA: 
                        case 0xBCB: 
                        case 0xBCC: 
                        case 0xBCD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ொ', '்'] */

                        case 0xBD0: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ௐ' */

                        case 0xBD7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ௗ' */

                        case 0xBE6: 
                        case 0xBE7: 
                        case 0xBE8: 
                        case 0xBE9: 
                        case 0xBEA: 
                        case 0xBEB: 
                        case 0xBEC: 
                        case 0xBED: 
                        case 0xBEE: 
                        case 0xBEF: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['௦', '௯'] */

                        case 0xC01: 
                        case 0xC02: 
                        case 0xC03: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ఁ', 'ః'] */

                        case 0xC05: 
                        case 0xC06: 
                        case 0xC07: 
                        case 0xC08: 
                        case 0xC09: 
                        case 0xC0A: 
                        case 0xC0B: 
                        case 0xC0C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['అ', 'ఌ'] */


                    }
                }
            }
        } else {
            if( input < 0xECE ) {
                if( input < 0xD58 ) {
                    if( input < 0xCB5 ) {
                        switch( input ) {
                            case 0xC0E: 
                            case 0xC0F: 
                            case 0xC10: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ఎ', 'ఐ'] */

                            case 0xC12: 
                            case 0xC13: 
                            case 0xC14: 
                            case 0xC15: 
                            case 0xC16: 
                            case 0xC17: 
                            case 0xC18: 
                            case 0xC19: 
                            case 0xC1A: 
                            case 0xC1B: 
                            case 0xC1C: 
                            case 0xC1D: 
                            case 0xC1E: 
                            case 0xC1F: 
                            case 0xC20: 
                            case 0xC21: 
                            case 0xC22: 
                            case 0xC23: 
                            case 0xC24: 
                            case 0xC25: 
                            case 0xC26: 
                            case 0xC27: 
                            case 0xC28: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ఒ', 'న'] */

                            case 0xC2A: 
                            case 0xC2B: 
                            case 0xC2C: 
                            case 0xC2D: 
                            case 0xC2E: 
                            case 0xC2F: 
                            case 0xC30: 
                            case 0xC31: 
                            case 0xC32: 
                            case 0xC33: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ప', 'ళ'] */

                            case 0xC35: 
                            case 0xC36: 
                            case 0xC37: 
                            case 0xC38: 
                            case 0xC39: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['వ', 'హ'] */

                            case 0xC3D: 
                            case 0xC3E: 
                            case 0xC3F: 
                            case 0xC40: 
                            case 0xC41: 
                            case 0xC42: 
                            case 0xC43: 
                            case 0xC44: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ఽ', 'ౄ'] */

                            case 0xC46: 
                            case 0xC47: 
                            case 0xC48: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ె', 'ై'] */

                            case 0xC4A: 
                            case 0xC4B: 
                            case 0xC4C: 
                            case 0xC4D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ొ', '్'] */

                            case 0xC55: 
                            case 0xC56: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ౕ', 'ౖ'] */

                            case 0xC58: 
                            case 0xC59: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ౘ', 'ౙ'] */

                            case 0xC60: 
                            case 0xC61: 
                            case 0xC62: 
                            case 0xC63: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ౠ', 'ౣ'] */

                            case 0xC66: 
                            case 0xC67: 
                            case 0xC68: 
                            case 0xC69: 
                            case 0xC6A: 
                            case 0xC6B: 
                            case 0xC6C: 
                            case 0xC6D: 
                            case 0xC6E: 
                            case 0xC6F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['౦', '౯'] */

                            case 0xC82: 
                            case 0xC83: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ಂ', 'ಃ'] */

                            case 0xC85: 
                            case 0xC86: 
                            case 0xC87: 
                            case 0xC88: 
                            case 0xC89: 
                            case 0xC8A: 
                            case 0xC8B: 
                            case 0xC8C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ಅ', 'ಌ'] */

                            case 0xC8E: 
                            case 0xC8F: 
                            case 0xC90: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ಎ', 'ಐ'] */

                            case 0xC92: 
                            case 0xC93: 
                            case 0xC94: 
                            case 0xC95: 
                            case 0xC96: 
                            case 0xC97: 
                            case 0xC98: 
                            case 0xC99: 
                            case 0xC9A: 
                            case 0xC9B: 
                            case 0xC9C: 
                            case 0xC9D: 
                            case 0xC9E: 
                            case 0xC9F: 
                            case 0xCA0: 
                            case 0xCA1: 
                            case 0xCA2: 
                            case 0xCA3: 
                            case 0xCA4: 
                            case 0xCA5: 
                            case 0xCA6: 
                            case 0xCA7: 
                            case 0xCA8: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ಒ', 'ನ'] */

                            case 0xCAA: 
                            case 0xCAB: 
                            case 0xCAC: 
                            case 0xCAD: 
                            case 0xCAE: 
                            case 0xCAF: 
                            case 0xCB0: 
                            case 0xCB1: 
                            case 0xCB2: 
                            case 0xCB3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ಪ', 'ಳ'] */


                        }
                    } else {
                        switch( input ) {
                            case 0xCB5: 
                            case 0xCB6: 
                            case 0xCB7: 
                            case 0xCB8: 
                            case 0xCB9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ವ', 'ಹ'] */

                            case 0xCBC: 
                            case 0xCBD: 
                            case 0xCBE: 
                            case 0xCBF: 
                            case 0xCC0: 
                            case 0xCC1: 
                            case 0xCC2: 
                            case 0xCC3: 
                            case 0xCC4: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['಼', 'ೄ'] */

                            case 0xCC6: 
                            case 0xCC7: 
                            case 0xCC8: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ೆ', 'ೈ'] */

                            case 0xCCA: 
                            case 0xCCB: 
                            case 0xCCC: 
                            case 0xCCD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ೊ', '್'] */

                            case 0xCD5: 
                            case 0xCD6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ೕ', 'ೖ'] */

                            case 0xCDE: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ೞ' */

                            case 0xCE0: 
                            case 0xCE1: 
                            case 0xCE2: 
                            case 0xCE3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ೠ', 'ೣ'] */

                            case 0xCE6: 
                            case 0xCE7: 
                            case 0xCE8: 
                            case 0xCE9: 
                            case 0xCEA: 
                            case 0xCEB: 
                            case 0xCEC: 
                            case 0xCED: 
                            case 0xCEE: 
                            case 0xCEF: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['೦', '೯'] */

                            case 0xCF1: 
                            case 0xCF2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ೱ', 'ೲ'] */

                            case 0xD02: 
                            case 0xD03: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ം', 'ഃ'] */

                            case 0xD05: 
                            case 0xD06: 
                            case 0xD07: 
                            case 0xD08: 
                            case 0xD09: 
                            case 0xD0A: 
                            case 0xD0B: 
                            case 0xD0C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['അ', 'ഌ'] */

                            case 0xD0E: 
                            case 0xD0F: 
                            case 0xD10: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['എ', 'ഐ'] */

                            case 0xD12: 
                            case 0xD13: 
                            case 0xD14: 
                            case 0xD15: 
                            case 0xD16: 
                            case 0xD17: 
                            case 0xD18: 
                            case 0xD19: 
                            case 0xD1A: 
                            case 0xD1B: 
                            case 0xD1C: 
                            case 0xD1D: 
                            case 0xD1E: 
                            case 0xD1F: 
                            case 0xD20: 
                            case 0xD21: 
                            case 0xD22: 
                            case 0xD23: 
                            case 0xD24: 
                            case 0xD25: 
                            case 0xD26: 
                            case 0xD27: 
                            case 0xD28: 
                            case 0xD29: 
                            case 0xD2A: 
                            case 0xD2B: 
                            case 0xD2C: 
                            case 0xD2D: 
                            case 0xD2E: 
                            case 0xD2F: 
                            case 0xD30: 
                            case 0xD31: 
                            case 0xD32: 
                            case 0xD33: 
                            case 0xD34: 
                            case 0xD35: 
                            case 0xD36: 
                            case 0xD37: 
                            case 0xD38: 
                            case 0xD39: 
                            case 0xD3A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ഒ', 'ഺ'] */

                            case 0xD3D: 
                            case 0xD3E: 
                            case 0xD3F: 
                            case 0xD40: 
                            case 0xD41: 
                            case 0xD42: 
                            case 0xD43: 
                            case 0xD44: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ഽ', 'ൄ'] */

                            case 0xD46: 
                            case 0xD47: 
                            case 0xD48: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['െ', 'ൈ'] */

                            case 0xD4A: 
                            case 0xD4B: 
                            case 0xD4C: 
                            case 0xD4D: 
                            case 0xD4E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ൊ', 'ൎ'] */

                            case 0xD57: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ൗ' */


                        }
                    }
                } else {
                    if( input < 0xE50 ) {
                        if( input < 0xDBE ) {
                            switch( input ) {
                                case 0xD60: 
                                case 0xD61: 
                                case 0xD62: 
                                case 0xD63: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ൠ', 'ൣ'] */

                                case 0xD66: 
                                case 0xD67: 
                                case 0xD68: 
                                case 0xD69: 
                                case 0xD6A: 
                                case 0xD6B: 
                                case 0xD6C: 
                                case 0xD6D: 
                                case 0xD6E: 
                                case 0xD6F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['൦', '൯'] */

                                case 0xD7A: 
                                case 0xD7B: 
                                case 0xD7C: 
                                case 0xD7D: 
                                case 0xD7E: 
                                case 0xD7F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ൺ', 'ൿ'] */

                                case 0xD82: 
                                case 0xD83: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ං', 'ඃ'] */

                                case 0xD85: 
                                case 0xD86: 
                                case 0xD87: 
                                case 0xD88: 
                                case 0xD89: 
                                case 0xD8A: 
                                case 0xD8B: 
                                case 0xD8C: 
                                case 0xD8D: 
                                case 0xD8E: 
                                case 0xD8F: 
                                case 0xD90: 
                                case 0xD91: 
                                case 0xD92: 
                                case 0xD93: 
                                case 0xD94: 
                                case 0xD95: 
                                case 0xD96: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['අ', 'ඖ'] */

                                case 0xD9A: 
                                case 0xD9B: 
                                case 0xD9C: 
                                case 0xD9D: 
                                case 0xD9E: 
                                case 0xD9F: 
                                case 0xDA0: 
                                case 0xDA1: 
                                case 0xDA2: 
                                case 0xDA3: 
                                case 0xDA4: 
                                case 0xDA5: 
                                case 0xDA6: 
                                case 0xDA7: 
                                case 0xDA8: 
                                case 0xDA9: 
                                case 0xDAA: 
                                case 0xDAB: 
                                case 0xDAC: 
                                case 0xDAD: 
                                case 0xDAE: 
                                case 0xDAF: 
                                case 0xDB0: 
                                case 0xDB1: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ක', 'න'] */

                                case 0xDB3: 
                                case 0xDB4: 
                                case 0xDB5: 
                                case 0xDB6: 
                                case 0xDB7: 
                                case 0xDB8: 
                                case 0xDB9: 
                                case 0xDBA: 
                                case 0xDBB: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ඳ', 'ර'] */

                                case 0xDBD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ල' */


                            }
                        } else {
                            switch( input ) {
                                case 0xDC0: 
                                case 0xDC1: 
                                case 0xDC2: 
                                case 0xDC3: 
                                case 0xDC4: 
                                case 0xDC5: 
                                case 0xDC6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ව', 'ෆ'] */

                                case 0xDCA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '්' */

                                case 0xDCF: 
                                case 0xDD0: 
                                case 0xDD1: 
                                case 0xDD2: 
                                case 0xDD3: 
                                case 0xDD4: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ා', 'ු'] */

                                case 0xDD6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ූ' */

                                case 0xDD8: 
                                case 0xDD9: 
                                case 0xDDA: 
                                case 0xDDB: 
                                case 0xDDC: 
                                case 0xDDD: 
                                case 0xDDE: 
                                case 0xDDF: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ෘ', 'ෟ'] */

                                case 0xDF2: 
                                case 0xDF3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ෲ', 'ෳ'] */

                                case 0xE01: 
                                case 0xE02: 
                                case 0xE03: 
                                case 0xE04: 
                                case 0xE05: 
                                case 0xE06: 
                                case 0xE07: 
                                case 0xE08: 
                                case 0xE09: 
                                case 0xE0A: 
                                case 0xE0B: 
                                case 0xE0C: 
                                case 0xE0D: 
                                case 0xE0E: 
                                case 0xE0F: 
                                case 0xE10: 
                                case 0xE11: 
                                case 0xE12: 
                                case 0xE13: 
                                case 0xE14: 
                                case 0xE15: 
                                case 0xE16: 
                                case 0xE17: 
                                case 0xE18: 
                                case 0xE19: 
                                case 0xE1A: 
                                case 0xE1B: 
                                case 0xE1C: 
                                case 0xE1D: 
                                case 0xE1E: 
                                case 0xE1F: 
                                case 0xE20: 
                                case 0xE21: 
                                case 0xE22: 
                                case 0xE23: 
                                case 0xE24: 
                                case 0xE25: 
                                case 0xE26: 
                                case 0xE27: 
                                case 0xE28: 
                                case 0xE29: 
                                case 0xE2A: 
                                case 0xE2B: 
                                case 0xE2C: 
                                case 0xE2D: 
                                case 0xE2E: 
                                case 0xE2F: 
                                case 0xE30: 
                                case 0xE31: 
                                case 0xE32: 
                                case 0xE33: 
                                case 0xE34: 
                                case 0xE35: 
                                case 0xE36: 
                                case 0xE37: 
                                case 0xE38: 
                                case 0xE39: 
                                case 0xE3A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ก', 'ฺ'] */

                                case 0xE40: 
                                case 0xE41: 
                                case 0xE42: 
                                case 0xE43: 
                                case 0xE44: 
                                case 0xE45: 
                                case 0xE46: 
                                case 0xE47: 
                                case 0xE48: 
                                case 0xE49: 
                                case 0xE4A: 
                                case 0xE4B: 
                                case 0xE4C: 
                                case 0xE4D: 
                                case 0xE4E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['เ', '๎'] */


                            }
                        }
                    } else {
                        switch( input ) {
                            case 0xE50: 
                            case 0xE51: 
                            case 0xE52: 
                            case 0xE53: 
                            case 0xE54: 
                            case 0xE55: 
                            case 0xE56: 
                            case 0xE57: 
                            case 0xE58: 
                            case 0xE59: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['๐', '๙'] */

                            case 0xE81: 
                            case 0xE82: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ກ', 'ຂ'] */

                            case 0xE84: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ຄ' */

                            case 0xE87: 
                            case 0xE88: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ງ', 'ຈ'] */

                            case 0xE8A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ຊ' */

                            case 0xE8D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ຍ' */

                            case 0xE94: 
                            case 0xE95: 
                            case 0xE96: 
                            case 0xE97: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ດ', 'ທ'] */

                            case 0xE99: 
                            case 0xE9A: 
                            case 0xE9B: 
                            case 0xE9C: 
                            case 0xE9D: 
                            case 0xE9E: 
                            case 0xE9F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ນ', 'ຟ'] */

                            case 0xEA1: 
                            case 0xEA2: 
                            case 0xEA3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ມ', 'ຣ'] */

                            case 0xEA5: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ລ' */

                            case 0xEA7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ວ' */

                            case 0xEAA: 
                            case 0xEAB: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ສ', 'ຫ'] */

                            case 0xEAD: 
                            case 0xEAE: 
                            case 0xEAF: 
                            case 0xEB0: 
                            case 0xEB1: 
                            case 0xEB2: 
                            case 0xEB3: 
                            case 0xEB4: 
                            case 0xEB5: 
                            case 0xEB6: 
                            case 0xEB7: 
                            case 0xEB8: 
                            case 0xEB9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ອ', 'ູ'] */

                            case 0xEBB: 
                            case 0xEBC: 
                            case 0xEBD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ົ', 'ຽ'] */

                            case 0xEC0: 
                            case 0xEC1: 
                            case 0xEC2: 
                            case 0xEC3: 
                            case 0xEC4: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ເ', 'ໄ'] */

                            case 0xEC6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ໆ' */

                            case 0xEC8: 
                            case 0xEC9: 
                            case 0xECA: 
                            case 0xECB: 
                            case 0xECC: 
                            case 0xECD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['່', 'ໍ'] */


                        }
                    }
                }
            } else {
                if( input < 0x1311 ) {
                    if( input < 0x10A0 ) {
                        if( input < 0xF3A ) {
                            switch( input ) {
                                case 0xED0: 
                                case 0xED1: 
                                case 0xED2: 
                                case 0xED3: 
                                case 0xED4: 
                                case 0xED5: 
                                case 0xED6: 
                                case 0xED7: 
                                case 0xED8: 
                                case 0xED9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['໐', '໙'] */

                                case 0xEDC: 
                                case 0xEDD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ໜ', 'ໝ'] */

                                case 0xF00: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ༀ' */

                                case 0xF18: 
                                case 0xF19: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['༘', '༙'] */

                                case 0xF20: 
                                case 0xF21: 
                                case 0xF22: 
                                case 0xF23: 
                                case 0xF24: 
                                case 0xF25: 
                                case 0xF26: 
                                case 0xF27: 
                                case 0xF28: 
                                case 0xF29: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['༠', '༩'] */

                                case 0xF35: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '༵' */

                                case 0xF37: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '༷' */

                                case 0xF39: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '༹' */


                            }
                        } else {
                            if( input < 0xF98 ) {
                                switch( input ) {
                                    case 0xF3E: 
                                    case 0xF3F: 
                                    case 0xF40: 
                                    case 0xF41: 
                                    case 0xF42: 
                                    case 0xF43: 
                                    case 0xF44: 
                                    case 0xF45: 
                                    case 0xF46: 
                                    case 0xF47: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['༾', 'ཇ'] */

                                    case 0xF49: 
                                    case 0xF4A: 
                                    case 0xF4B: 
                                    case 0xF4C: 
                                    case 0xF4D: 
                                    case 0xF4E: 
                                    case 0xF4F: 
                                    case 0xF50: 
                                    case 0xF51: 
                                    case 0xF52: 
                                    case 0xF53: 
                                    case 0xF54: 
                                    case 0xF55: 
                                    case 0xF56: 
                                    case 0xF57: 
                                    case 0xF58: 
                                    case 0xF59: 
                                    case 0xF5A: 
                                    case 0xF5B: 
                                    case 0xF5C: 
                                    case 0xF5D: 
                                    case 0xF5E: 
                                    case 0xF5F: 
                                    case 0xF60: 
                                    case 0xF61: 
                                    case 0xF62: 
                                    case 0xF63: 
                                    case 0xF64: 
                                    case 0xF65: 
                                    case 0xF66: 
                                    case 0xF67: 
                                    case 0xF68: 
                                    case 0xF69: 
                                    case 0xF6A: 
                                    case 0xF6B: 
                                    case 0xF6C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ཉ', 'ཬ'] */

                                    case 0xF71: 
                                    case 0xF72: 
                                    case 0xF73: 
                                    case 0xF74: 
                                    case 0xF75: 
                                    case 0xF76: 
                                    case 0xF77: 
                                    case 0xF78: 
                                    case 0xF79: 
                                    case 0xF7A: 
                                    case 0xF7B: 
                                    case 0xF7C: 
                                    case 0xF7D: 
                                    case 0xF7E: 
                                    case 0xF7F: 
                                    case 0xF80: 
                                    case 0xF81: 
                                    case 0xF82: 
                                    case 0xF83: 
                                    case 0xF84: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ཱ', '྄'] */

                                    case 0xF86: 
                                    case 0xF87: 
                                    case 0xF88: 
                                    case 0xF89: 
                                    case 0xF8A: 
                                    case 0xF8B: 
                                    case 0xF8C: 
                                    case 0xF8D: 
                                    case 0xF8E: 
                                    case 0xF8F: 
                                    case 0xF90: 
                                    case 0xF91: 
                                    case 0xF92: 
                                    case 0xF93: 
                                    case 0xF94: 
                                    case 0xF95: 
                                    case 0xF96: 
                                    case 0xF97: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['྆', 'ྗ'] */


                                }
                            } else {
                                if( input < 0xFC7 ) {
                                    switch( input ) {
                                        case 0xF99: 
                                        case 0xF9A: 
                                        case 0xF9B: 
                                        case 0xF9C: 
                                        case 0xF9D: 
                                        case 0xF9E: 
                                        case 0xF9F: 
                                        case 0xFA0: 
                                        case 0xFA1: 
                                        case 0xFA2: 
                                        case 0xFA3: 
                                        case 0xFA4: 
                                        case 0xFA5: 
                                        case 0xFA6: 
                                        case 0xFA7: 
                                        case 0xFA8: 
                                        case 0xFA9: 
                                        case 0xFAA: 
                                        case 0xFAB: 
                                        case 0xFAC: 
                                        case 0xFAD: 
                                        case 0xFAE: 
                                        case 0xFAF: 
                                        case 0xFB0: 
                                        case 0xFB1: 
                                        case 0xFB2: 
                                        case 0xFB3: 
                                        case 0xFB4: 
                                        case 0xFB5: 
                                        case 0xFB6: 
                                        case 0xFB7: 
                                        case 0xFB8: 
                                        case 0xFB9: 
                                        case 0xFBA: 
                                        case 0xFBB: 
                                        case 0xFBC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ྙ', 'ྼ'] */

                                        case 0xFC6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '࿆' */


                                    }
                                } else {
                                    if( input < 0x1000 ) {

                                    } else if( input < 0x104A ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['က', '၉'] */

                                    } else if( input < 0x1050 ) {

                                    } else if( input < 0x109E ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ၐ', 'ႝ'] */

                                    } else {

                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0x1260 ) {
                            if( input < 0x124A ) {
                                if( input < 0x10FC ) {
                                    if( input < 0x10C6 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ⴀ', 'Ⴥ'] */

                                    } else if( input < 0x10D0 ) {

                                    } else if( input < 0x10FB ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ა', 'ჺ'] */

                                    } else {

                                    }
                                } else {
                                    if( input == 0x10FC ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ჼ' */

                                    } else if( input < 0x1100 ) {

                                    } else if( input < 0x1249 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᄀ', 'ቈ'] */

                                    } else {

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x124A: 
                                    case 0x124B: 
                                    case 0x124C: 
                                    case 0x124D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ቊ', 'ቍ'] */

                                    case 0x1250: 
                                    case 0x1251: 
                                    case 0x1252: 
                                    case 0x1253: 
                                    case 0x1254: 
                                    case 0x1255: 
                                    case 0x1256: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ቐ', 'ቖ'] */

                                    case 0x1258: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ቘ' */

                                    case 0x125A: 
                                    case 0x125B: 
                                    case 0x125C: 
                                    case 0x125D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ቚ', 'ቝ'] */


                                }
                            }
                        } else {
                            if( input < 0x12B8 ) {
                                switch( input ) {
                                    case 0x1260: 
                                    case 0x1261: 
                                    case 0x1262: 
                                    case 0x1263: 
                                    case 0x1264: 
                                    case 0x1265: 
                                    case 0x1266: 
                                    case 0x1267: 
                                    case 0x1268: 
                                    case 0x1269: 
                                    case 0x126A: 
                                    case 0x126B: 
                                    case 0x126C: 
                                    case 0x126D: 
                                    case 0x126E: 
                                    case 0x126F: 
                                    case 0x1270: 
                                    case 0x1271: 
                                    case 0x1272: 
                                    case 0x1273: 
                                    case 0x1274: 
                                    case 0x1275: 
                                    case 0x1276: 
                                    case 0x1277: 
                                    case 0x1278: 
                                    case 0x1279: 
                                    case 0x127A: 
                                    case 0x127B: 
                                    case 0x127C: 
                                    case 0x127D: 
                                    case 0x127E: 
                                    case 0x127F: 
                                    case 0x1280: 
                                    case 0x1281: 
                                    case 0x1282: 
                                    case 0x1283: 
                                    case 0x1284: 
                                    case 0x1285: 
                                    case 0x1286: 
                                    case 0x1287: 
                                    case 0x1288: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['በ', 'ኈ'] */

                                    case 0x128A: 
                                    case 0x128B: 
                                    case 0x128C: 
                                    case 0x128D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ኊ', 'ኍ'] */

                                    case 0x1290: 
                                    case 0x1291: 
                                    case 0x1292: 
                                    case 0x1293: 
                                    case 0x1294: 
                                    case 0x1295: 
                                    case 0x1296: 
                                    case 0x1297: 
                                    case 0x1298: 
                                    case 0x1299: 
                                    case 0x129A: 
                                    case 0x129B: 
                                    case 0x129C: 
                                    case 0x129D: 
                                    case 0x129E: 
                                    case 0x129F: 
                                    case 0x12A0: 
                                    case 0x12A1: 
                                    case 0x12A2: 
                                    case 0x12A3: 
                                    case 0x12A4: 
                                    case 0x12A5: 
                                    case 0x12A6: 
                                    case 0x12A7: 
                                    case 0x12A8: 
                                    case 0x12A9: 
                                    case 0x12AA: 
                                    case 0x12AB: 
                                    case 0x12AC: 
                                    case 0x12AD: 
                                    case 0x12AE: 
                                    case 0x12AF: 
                                    case 0x12B0: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ነ', 'ኰ'] */

                                    case 0x12B2: 
                                    case 0x12B3: 
                                    case 0x12B4: 
                                    case 0x12B5: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ኲ', 'ኵ'] */


                                }
                            } else {
                                switch( input ) {
                                    case 0x12B8: 
                                    case 0x12B9: 
                                    case 0x12BA: 
                                    case 0x12BB: 
                                    case 0x12BC: 
                                    case 0x12BD: 
                                    case 0x12BE: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ኸ', 'ኾ'] */

                                    case 0x12C0: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ዀ' */

                                    case 0x12C2: 
                                    case 0x12C3: 
                                    case 0x12C4: 
                                    case 0x12C5: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ዂ', 'ዅ'] */

                                    case 0x12C8: 
                                    case 0x12C9: 
                                    case 0x12CA: 
                                    case 0x12CB: 
                                    case 0x12CC: 
                                    case 0x12CD: 
                                    case 0x12CE: 
                                    case 0x12CF: 
                                    case 0x12D0: 
                                    case 0x12D1: 
                                    case 0x12D2: 
                                    case 0x12D3: 
                                    case 0x12D4: 
                                    case 0x12D5: 
                                    case 0x12D6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ወ', 'ዖ'] */

                                    case 0x12D8: 
                                    case 0x12D9: 
                                    case 0x12DA: 
                                    case 0x12DB: 
                                    case 0x12DC: 
                                    case 0x12DD: 
                                    case 0x12DE: 
                                    case 0x12DF: 
                                    case 0x12E0: 
                                    case 0x12E1: 
                                    case 0x12E2: 
                                    case 0x12E3: 
                                    case 0x12E4: 
                                    case 0x12E5: 
                                    case 0x12E6: 
                                    case 0x12E7: 
                                    case 0x12E8: 
                                    case 0x12E9: 
                                    case 0x12EA: 
                                    case 0x12EB: 
                                    case 0x12EC: 
                                    case 0x12ED: 
                                    case 0x12EE: 
                                    case 0x12EF: 
                                    case 0x12F0: 
                                    case 0x12F1: 
                                    case 0x12F2: 
                                    case 0x12F3: 
                                    case 0x12F4: 
                                    case 0x12F5: 
                                    case 0x12F6: 
                                    case 0x12F7: 
                                    case 0x12F8: 
                                    case 0x12F9: 
                                    case 0x12FA: 
                                    case 0x12FB: 
                                    case 0x12FC: 
                                    case 0x12FD: 
                                    case 0x12FE: 
                                    case 0x12FF: 
                                    case 0x1300: 
                                    case 0x1301: 
                                    case 0x1302: 
                                    case 0x1303: 
                                    case 0x1304: 
                                    case 0x1305: 
                                    case 0x1306: 
                                    case 0x1307: 
                                    case 0x1308: 
                                    case 0x1309: 
                                    case 0x130A: 
                                    case 0x130B: 
                                    case 0x130C: 
                                    case 0x130D: 
                                    case 0x130E: 
                                    case 0x130F: 
                                    case 0x1310: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ዘ', 'ጐ'] */


                                }
                            }
                        }
                    }
                } else {
                    if( input < 0x176E ) {
                        if( input < 0x1680 ) {
                            if( input < 0x1372 ) {
                                switch( input ) {
                                    case 0x1312: 
                                    case 0x1313: 
                                    case 0x1314: 
                                    case 0x1315: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ጒ', 'ጕ'] */

                                    case 0x1318: 
                                    case 0x1319: 
                                    case 0x131A: 
                                    case 0x131B: 
                                    case 0x131C: 
                                    case 0x131D: 
                                    case 0x131E: 
                                    case 0x131F: 
                                    case 0x1320: 
                                    case 0x1321: 
                                    case 0x1322: 
                                    case 0x1323: 
                                    case 0x1324: 
                                    case 0x1325: 
                                    case 0x1326: 
                                    case 0x1327: 
                                    case 0x1328: 
                                    case 0x1329: 
                                    case 0x132A: 
                                    case 0x132B: 
                                    case 0x132C: 
                                    case 0x132D: 
                                    case 0x132E: 
                                    case 0x132F: 
                                    case 0x1330: 
                                    case 0x1331: 
                                    case 0x1332: 
                                    case 0x1333: 
                                    case 0x1334: 
                                    case 0x1335: 
                                    case 0x1336: 
                                    case 0x1337: 
                                    case 0x1338: 
                                    case 0x1339: 
                                    case 0x133A: 
                                    case 0x133B: 
                                    case 0x133C: 
                                    case 0x133D: 
                                    case 0x133E: 
                                    case 0x133F: 
                                    case 0x1340: 
                                    case 0x1341: 
                                    case 0x1342: 
                                    case 0x1343: 
                                    case 0x1344: 
                                    case 0x1345: 
                                    case 0x1346: 
                                    case 0x1347: 
                                    case 0x1348: 
                                    case 0x1349: 
                                    case 0x134A: 
                                    case 0x134B: 
                                    case 0x134C: 
                                    case 0x134D: 
                                    case 0x134E: 
                                    case 0x134F: 
                                    case 0x1350: 
                                    case 0x1351: 
                                    case 0x1352: 
                                    case 0x1353: 
                                    case 0x1354: 
                                    case 0x1355: 
                                    case 0x1356: 
                                    case 0x1357: 
                                    case 0x1358: 
                                    case 0x1359: 
                                    case 0x135A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ጘ', 'ፚ'] */

                                    case 0x135D: 
                                    case 0x135E: 
                                    case 0x135F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['፝', '፟'] */

                                    case 0x1369: 
                                    case 0x136A: 
                                    case 0x136B: 
                                    case 0x136C: 
                                    case 0x136D: 
                                    case 0x136E: 
                                    case 0x136F: 
                                    case 0x1370: 
                                    case 0x1371: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['፩', '፱'] */


                                }
                            } else {
                                if( input < 0x13F5 ) {
                                    if( input < 0x1380 ) {

                                    } else if( input < 0x1390 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᎀ', 'ᎏ'] */

                                    } else if( input < 0x13A0 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ꭰ', 'Ᏼ'] */

                                    }
                                } else {
                                    if( input < 0x1401 ) {

                                    } else if( input < 0x166D ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᐁ', 'ᙬ'] */

                                    } else if( input < 0x166F ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᙯ', 'ᙿ'] */

                                    }
                                }
                            }
                        } else {
                            if( input < 0x170D ) {
                                if( input < 0x16EB ) {
                                    if( input == 0x1680 ) {

                                    } else if( input < 0x169B ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᚁ', 'ᚚ'] */

                                    } else if( input < 0x16A0 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᚠ', 'ᛪ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x16EE: 
                                        case 0x16EF: 
                                        case 0x16F0: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᛮ', 'ᛰ'] */

                                        case 0x1700: 
                                        case 0x1701: 
                                        case 0x1702: 
                                        case 0x1703: 
                                        case 0x1704: 
                                        case 0x1705: 
                                        case 0x1706: 
                                        case 0x1707: 
                                        case 0x1708: 
                                        case 0x1709: 
                                        case 0x170A: 
                                        case 0x170B: 
                                        case 0x170C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᜀ', 'ᜌ'] */


                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x170E: 
                                    case 0x170F: 
                                    case 0x1710: 
                                    case 0x1711: 
                                    case 0x1712: 
                                    case 0x1713: 
                                    case 0x1714: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᜎ', '᜔'] */

                                    case 0x1720: 
                                    case 0x1721: 
                                    case 0x1722: 
                                    case 0x1723: 
                                    case 0x1724: 
                                    case 0x1725: 
                                    case 0x1726: 
                                    case 0x1727: 
                                    case 0x1728: 
                                    case 0x1729: 
                                    case 0x172A: 
                                    case 0x172B: 
                                    case 0x172C: 
                                    case 0x172D: 
                                    case 0x172E: 
                                    case 0x172F: 
                                    case 0x1730: 
                                    case 0x1731: 
                                    case 0x1732: 
                                    case 0x1733: 
                                    case 0x1734: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᜠ', '᜴'] */

                                    case 0x1740: 
                                    case 0x1741: 
                                    case 0x1742: 
                                    case 0x1743: 
                                    case 0x1744: 
                                    case 0x1745: 
                                    case 0x1746: 
                                    case 0x1747: 
                                    case 0x1748: 
                                    case 0x1749: 
                                    case 0x174A: 
                                    case 0x174B: 
                                    case 0x174C: 
                                    case 0x174D: 
                                    case 0x174E: 
                                    case 0x174F: 
                                    case 0x1750: 
                                    case 0x1751: 
                                    case 0x1752: 
                                    case 0x1753: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᝀ', 'ᝓ'] */

                                    case 0x1760: 
                                    case 0x1761: 
                                    case 0x1762: 
                                    case 0x1763: 
                                    case 0x1764: 
                                    case 0x1765: 
                                    case 0x1766: 
                                    case 0x1767: 
                                    case 0x1768: 
                                    case 0x1769: 
                                    case 0x176A: 
                                    case 0x176B: 
                                    case 0x176C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᝠ', 'ᝬ'] */


                                }
                            }
                        }
                    } else {
                        if( input < 0x1810 ) {
                            switch( input ) {
                                case 0x176E: 
                                case 0x176F: 
                                case 0x1770: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᝮ', 'ᝰ'] */

                                case 0x1772: 
                                case 0x1773: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᝲ', 'ᝳ'] */

                                case 0x1780: 
                                case 0x1781: 
                                case 0x1782: 
                                case 0x1783: 
                                case 0x1784: 
                                case 0x1785: 
                                case 0x1786: 
                                case 0x1787: 
                                case 0x1788: 
                                case 0x1789: 
                                case 0x178A: 
                                case 0x178B: 
                                case 0x178C: 
                                case 0x178D: 
                                case 0x178E: 
                                case 0x178F: 
                                case 0x1790: 
                                case 0x1791: 
                                case 0x1792: 
                                case 0x1793: 
                                case 0x1794: 
                                case 0x1795: 
                                case 0x1796: 
                                case 0x1797: 
                                case 0x1798: 
                                case 0x1799: 
                                case 0x179A: 
                                case 0x179B: 
                                case 0x179C: 
                                case 0x179D: 
                                case 0x179E: 
                                case 0x179F: 
                                case 0x17A0: 
                                case 0x17A1: 
                                case 0x17A2: 
                                case 0x17A3: 
                                case 0x17A4: 
                                case 0x17A5: 
                                case 0x17A6: 
                                case 0x17A7: 
                                case 0x17A8: 
                                case 0x17A9: 
                                case 0x17AA: 
                                case 0x17AB: 
                                case 0x17AC: 
                                case 0x17AD: 
                                case 0x17AE: 
                                case 0x17AF: 
                                case 0x17B0: 
                                case 0x17B1: 
                                case 0x17B2: 
                                case 0x17B3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ក', 'ឳ'] */

                                case 0x17B6: 
                                case 0x17B7: 
                                case 0x17B8: 
                                case 0x17B9: 
                                case 0x17BA: 
                                case 0x17BB: 
                                case 0x17BC: 
                                case 0x17BD: 
                                case 0x17BE: 
                                case 0x17BF: 
                                case 0x17C0: 
                                case 0x17C1: 
                                case 0x17C2: 
                                case 0x17C3: 
                                case 0x17C4: 
                                case 0x17C5: 
                                case 0x17C6: 
                                case 0x17C7: 
                                case 0x17C8: 
                                case 0x17C9: 
                                case 0x17CA: 
                                case 0x17CB: 
                                case 0x17CC: 
                                case 0x17CD: 
                                case 0x17CE: 
                                case 0x17CF: 
                                case 0x17D0: 
                                case 0x17D1: 
                                case 0x17D2: 
                                case 0x17D3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ា', '៓'] */

                                case 0x17D7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ៗ' */

                                case 0x17DC: 
                                case 0x17DD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ៜ', '៝'] */

                                case 0x17E0: 
                                case 0x17E1: 
                                case 0x17E2: 
                                case 0x17E3: 
                                case 0x17E4: 
                                case 0x17E5: 
                                case 0x17E6: 
                                case 0x17E7: 
                                case 0x17E8: 
                                case 0x17E9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['០', '៩'] */

                                case 0x180B: 
                                case 0x180C: 
                                case 0x180D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᠋', '᠍'] */


                            }
                        } else {
                            if( input < 0x1900 ) {
                                if( input < 0x1880 ) {
                                    if( input < 0x181A ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᠐', '᠙'] */

                                    } else if( input < 0x1820 ) {

                                    } else if( input < 0x1878 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᠠ', 'ᡷ'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x18AB ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᢀ', 'ᢪ'] */

                                    } else if( input < 0x18B0 ) {

                                    } else if( input < 0x18F6 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᢰ', 'ᣵ'] */

                                    } else {

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x1900: 
                                    case 0x1901: 
                                    case 0x1902: 
                                    case 0x1903: 
                                    case 0x1904: 
                                    case 0x1905: 
                                    case 0x1906: 
                                    case 0x1907: 
                                    case 0x1908: 
                                    case 0x1909: 
                                    case 0x190A: 
                                    case 0x190B: 
                                    case 0x190C: 
                                    case 0x190D: 
                                    case 0x190E: 
                                    case 0x190F: 
                                    case 0x1910: 
                                    case 0x1911: 
                                    case 0x1912: 
                                    case 0x1913: 
                                    case 0x1914: 
                                    case 0x1915: 
                                    case 0x1916: 
                                    case 0x1917: 
                                    case 0x1918: 
                                    case 0x1919: 
                                    case 0x191A: 
                                    case 0x191B: 
                                    case 0x191C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᤀ', 'ᤜ'] */

                                    case 0x1920: 
                                    case 0x1921: 
                                    case 0x1922: 
                                    case 0x1923: 
                                    case 0x1924: 
                                    case 0x1925: 
                                    case 0x1926: 
                                    case 0x1927: 
                                    case 0x1928: 
                                    case 0x1929: 
                                    case 0x192A: 
                                    case 0x192B: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᤠ', 'ᤫ'] */

                                    case 0x1930: 
                                    case 0x1931: 
                                    case 0x1932: 
                                    case 0x1933: 
                                    case 0x1934: 
                                    case 0x1935: 
                                    case 0x1936: 
                                    case 0x1937: 
                                    case 0x1938: 
                                    case 0x1939: 
                                    case 0x193A: 
                                    case 0x193B: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᤰ', '᤻'] */

                                    case 0x1946: 
                                    case 0x1947: 
                                    case 0x1948: 
                                    case 0x1949: 
                                    case 0x194A: 
                                    case 0x194B: 
                                    case 0x194C: 
                                    case 0x194D: 
                                    case 0x194E: 
                                    case 0x194F: 
                                    case 0x1950: 
                                    case 0x1951: 
                                    case 0x1952: 
                                    case 0x1953: 
                                    case 0x1954: 
                                    case 0x1955: 
                                    case 0x1956: 
                                    case 0x1957: 
                                    case 0x1958: 
                                    case 0x1959: 
                                    case 0x195A: 
                                    case 0x195B: 
                                    case 0x195C: 
                                    case 0x195D: 
                                    case 0x195E: 
                                    case 0x195F: 
                                    case 0x1960: 
                                    case 0x1961: 
                                    case 0x1962: 
                                    case 0x1963: 
                                    case 0x1964: 
                                    case 0x1965: 
                                    case 0x1966: 
                                    case 0x1967: 
                                    case 0x1968: 
                                    case 0x1969: 
                                    case 0x196A: 
                                    case 0x196B: 
                                    case 0x196C: 
                                    case 0x196D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᥆', 'ᥭ'] */

                                    case 0x1970: 
                                    case 0x1971: 
                                    case 0x1972: 
                                    case 0x1973: 
                                    case 0x1974: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᥰ', 'ᥴ'] */


                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        if( input < 0xABEB ) {
            if( input < 0x2CE5 ) {
                if( input < 0x1FBE ) {
                    if( input < 0x1C38 ) {
                        if( input < 0x1A9A ) {
                            if( input < 0x1A1C ) {
                                if( input < 0x19CA ) {
                                    if( input < 0x1980 ) {

                                    } else if( input < 0x19AC ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᦀ', 'ᦫ'] */

                                    } else if( input < 0x19B0 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᦰ', 'ᧉ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x19D0: 
                                        case 0x19D1: 
                                        case 0x19D2: 
                                        case 0x19D3: 
                                        case 0x19D4: 
                                        case 0x19D5: 
                                        case 0x19D6: 
                                        case 0x19D7: 
                                        case 0x19D8: 
                                        case 0x19D9: 
                                        case 0x19DA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᧐', '᧚'] */

                                        case 0x1A00: 
                                        case 0x1A01: 
                                        case 0x1A02: 
                                        case 0x1A03: 
                                        case 0x1A04: 
                                        case 0x1A05: 
                                        case 0x1A06: 
                                        case 0x1A07: 
                                        case 0x1A08: 
                                        case 0x1A09: 
                                        case 0x1A0A: 
                                        case 0x1A0B: 
                                        case 0x1A0C: 
                                        case 0x1A0D: 
                                        case 0x1A0E: 
                                        case 0x1A0F: 
                                        case 0x1A10: 
                                        case 0x1A11: 
                                        case 0x1A12: 
                                        case 0x1A13: 
                                        case 0x1A14: 
                                        case 0x1A15: 
                                        case 0x1A16: 
                                        case 0x1A17: 
                                        case 0x1A18: 
                                        case 0x1A19: 
                                        case 0x1A1A: 
                                        case 0x1A1B: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᨀ', 'ᨛ'] */


                                    }
                                }
                            } else {
                                if( input < 0x1A7D ) {
                                    if( input < 0x1A20 ) {

                                    } else if( input < 0x1A5F ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᨠ', 'ᩞ'] */

                                    } else if( input == 0x1A5F ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᩠', '᩼'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1A7F: 
                                        case 0x1A80: 
                                        case 0x1A81: 
                                        case 0x1A82: 
                                        case 0x1A83: 
                                        case 0x1A84: 
                                        case 0x1A85: 
                                        case 0x1A86: 
                                        case 0x1A87: 
                                        case 0x1A88: 
                                        case 0x1A89: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᩿', '᪉'] */

                                        case 0x1A90: 
                                        case 0x1A91: 
                                        case 0x1A92: 
                                        case 0x1A93: 
                                        case 0x1A94: 
                                        case 0x1A95: 
                                        case 0x1A96: 
                                        case 0x1A97: 
                                        case 0x1A98: 
                                        case 0x1A99: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᪐', '᪙'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0x1B74 ) {
                                switch( input ) {
                                    case 0x1AA7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ᪧ' */

                                    case 0x1B00: 
                                    case 0x1B01: 
                                    case 0x1B02: 
                                    case 0x1B03: 
                                    case 0x1B04: 
                                    case 0x1B05: 
                                    case 0x1B06: 
                                    case 0x1B07: 
                                    case 0x1B08: 
                                    case 0x1B09: 
                                    case 0x1B0A: 
                                    case 0x1B0B: 
                                    case 0x1B0C: 
                                    case 0x1B0D: 
                                    case 0x1B0E: 
                                    case 0x1B0F: 
                                    case 0x1B10: 
                                    case 0x1B11: 
                                    case 0x1B12: 
                                    case 0x1B13: 
                                    case 0x1B14: 
                                    case 0x1B15: 
                                    case 0x1B16: 
                                    case 0x1B17: 
                                    case 0x1B18: 
                                    case 0x1B19: 
                                    case 0x1B1A: 
                                    case 0x1B1B: 
                                    case 0x1B1C: 
                                    case 0x1B1D: 
                                    case 0x1B1E: 
                                    case 0x1B1F: 
                                    case 0x1B20: 
                                    case 0x1B21: 
                                    case 0x1B22: 
                                    case 0x1B23: 
                                    case 0x1B24: 
                                    case 0x1B25: 
                                    case 0x1B26: 
                                    case 0x1B27: 
                                    case 0x1B28: 
                                    case 0x1B29: 
                                    case 0x1B2A: 
                                    case 0x1B2B: 
                                    case 0x1B2C: 
                                    case 0x1B2D: 
                                    case 0x1B2E: 
                                    case 0x1B2F: 
                                    case 0x1B30: 
                                    case 0x1B31: 
                                    case 0x1B32: 
                                    case 0x1B33: 
                                    case 0x1B34: 
                                    case 0x1B35: 
                                    case 0x1B36: 
                                    case 0x1B37: 
                                    case 0x1B38: 
                                    case 0x1B39: 
                                    case 0x1B3A: 
                                    case 0x1B3B: 
                                    case 0x1B3C: 
                                    case 0x1B3D: 
                                    case 0x1B3E: 
                                    case 0x1B3F: 
                                    case 0x1B40: 
                                    case 0x1B41: 
                                    case 0x1B42: 
                                    case 0x1B43: 
                                    case 0x1B44: 
                                    case 0x1B45: 
                                    case 0x1B46: 
                                    case 0x1B47: 
                                    case 0x1B48: 
                                    case 0x1B49: 
                                    case 0x1B4A: 
                                    case 0x1B4B: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᬀ', 'ᭋ'] */

                                    case 0x1B50: 
                                    case 0x1B51: 
                                    case 0x1B52: 
                                    case 0x1B53: 
                                    case 0x1B54: 
                                    case 0x1B55: 
                                    case 0x1B56: 
                                    case 0x1B57: 
                                    case 0x1B58: 
                                    case 0x1B59: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᭐', '᭙'] */

                                    case 0x1B6B: 
                                    case 0x1B6C: 
                                    case 0x1B6D: 
                                    case 0x1B6E: 
                                    case 0x1B6F: 
                                    case 0x1B70: 
                                    case 0x1B71: 
                                    case 0x1B72: 
                                    case 0x1B73: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᭫', '᭳'] */


                                }
                            } else {
                                if( input < 0x1BBA ) {
                                    switch( input ) {
                                        case 0x1B80: 
                                        case 0x1B81: 
                                        case 0x1B82: 
                                        case 0x1B83: 
                                        case 0x1B84: 
                                        case 0x1B85: 
                                        case 0x1B86: 
                                        case 0x1B87: 
                                        case 0x1B88: 
                                        case 0x1B89: 
                                        case 0x1B8A: 
                                        case 0x1B8B: 
                                        case 0x1B8C: 
                                        case 0x1B8D: 
                                        case 0x1B8E: 
                                        case 0x1B8F: 
                                        case 0x1B90: 
                                        case 0x1B91: 
                                        case 0x1B92: 
                                        case 0x1B93: 
                                        case 0x1B94: 
                                        case 0x1B95: 
                                        case 0x1B96: 
                                        case 0x1B97: 
                                        case 0x1B98: 
                                        case 0x1B99: 
                                        case 0x1B9A: 
                                        case 0x1B9B: 
                                        case 0x1B9C: 
                                        case 0x1B9D: 
                                        case 0x1B9E: 
                                        case 0x1B9F: 
                                        case 0x1BA0: 
                                        case 0x1BA1: 
                                        case 0x1BA2: 
                                        case 0x1BA3: 
                                        case 0x1BA4: 
                                        case 0x1BA5: 
                                        case 0x1BA6: 
                                        case 0x1BA7: 
                                        case 0x1BA8: 
                                        case 0x1BA9: 
                                        case 0x1BAA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᮀ', '᮪'] */

                                        case 0x1BAE: 
                                        case 0x1BAF: 
                                        case 0x1BB0: 
                                        case 0x1BB1: 
                                        case 0x1BB2: 
                                        case 0x1BB3: 
                                        case 0x1BB4: 
                                        case 0x1BB5: 
                                        case 0x1BB6: 
                                        case 0x1BB7: 
                                        case 0x1BB8: 
                                        case 0x1BB9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᮮ', '᮹'] */


                                    }
                                } else {
                                    if( input < 0x1BC0 ) {

                                    } else if( input < 0x1BF4 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᯀ', '᯳'] */

                                    } else if( input < 0x1C00 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᰀ', '᰷'] */

                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0x1F46 ) {
                            if( input < 0x1CF3 ) {
                                switch( input ) {
                                    case 0x1C40: 
                                    case 0x1C41: 
                                    case 0x1C42: 
                                    case 0x1C43: 
                                    case 0x1C44: 
                                    case 0x1C45: 
                                    case 0x1C46: 
                                    case 0x1C47: 
                                    case 0x1C48: 
                                    case 0x1C49: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᱀', '᱉'] */

                                    case 0x1C4D: 
                                    case 0x1C4E: 
                                    case 0x1C4F: 
                                    case 0x1C50: 
                                    case 0x1C51: 
                                    case 0x1C52: 
                                    case 0x1C53: 
                                    case 0x1C54: 
                                    case 0x1C55: 
                                    case 0x1C56: 
                                    case 0x1C57: 
                                    case 0x1C58: 
                                    case 0x1C59: 
                                    case 0x1C5A: 
                                    case 0x1C5B: 
                                    case 0x1C5C: 
                                    case 0x1C5D: 
                                    case 0x1C5E: 
                                    case 0x1C5F: 
                                    case 0x1C60: 
                                    case 0x1C61: 
                                    case 0x1C62: 
                                    case 0x1C63: 
                                    case 0x1C64: 
                                    case 0x1C65: 
                                    case 0x1C66: 
                                    case 0x1C67: 
                                    case 0x1C68: 
                                    case 0x1C69: 
                                    case 0x1C6A: 
                                    case 0x1C6B: 
                                    case 0x1C6C: 
                                    case 0x1C6D: 
                                    case 0x1C6E: 
                                    case 0x1C6F: 
                                    case 0x1C70: 
                                    case 0x1C71: 
                                    case 0x1C72: 
                                    case 0x1C73: 
                                    case 0x1C74: 
                                    case 0x1C75: 
                                    case 0x1C76: 
                                    case 0x1C77: 
                                    case 0x1C78: 
                                    case 0x1C79: 
                                    case 0x1C7A: 
                                    case 0x1C7B: 
                                    case 0x1C7C: 
                                    case 0x1C7D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᱍ', 'ᱽ'] */

                                    case 0x1CD0: 
                                    case 0x1CD1: 
                                    case 0x1CD2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᳐', '᳒'] */

                                    case 0x1CD4: 
                                    case 0x1CD5: 
                                    case 0x1CD6: 
                                    case 0x1CD7: 
                                    case 0x1CD8: 
                                    case 0x1CD9: 
                                    case 0x1CDA: 
                                    case 0x1CDB: 
                                    case 0x1CDC: 
                                    case 0x1CDD: 
                                    case 0x1CDE: 
                                    case 0x1CDF: 
                                    case 0x1CE0: 
                                    case 0x1CE1: 
                                    case 0x1CE2: 
                                    case 0x1CE3: 
                                    case 0x1CE4: 
                                    case 0x1CE5: 
                                    case 0x1CE6: 
                                    case 0x1CE7: 
                                    case 0x1CE8: 
                                    case 0x1CE9: 
                                    case 0x1CEA: 
                                    case 0x1CEB: 
                                    case 0x1CEC: 
                                    case 0x1CED: 
                                    case 0x1CEE: 
                                    case 0x1CEF: 
                                    case 0x1CF0: 
                                    case 0x1CF1: 
                                    case 0x1CF2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᳔', 'ᳲ'] */


                                }
                            } else {
                                if( input < 0x1F16 ) {
                                    if( input < 0x1D00 ) {

                                    } else if( input < 0x1DE7 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᴀ', 'ᷦ'] */

                                    } else if( input < 0x1DFC ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['᷼', 'ἕ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1F18: 
                                        case 0x1F19: 
                                        case 0x1F1A: 
                                        case 0x1F1B: 
                                        case 0x1F1C: 
                                        case 0x1F1D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ἐ', 'Ἕ'] */

                                        case 0x1F20: 
                                        case 0x1F21: 
                                        case 0x1F22: 
                                        case 0x1F23: 
                                        case 0x1F24: 
                                        case 0x1F25: 
                                        case 0x1F26: 
                                        case 0x1F27: 
                                        case 0x1F28: 
                                        case 0x1F29: 
                                        case 0x1F2A: 
                                        case 0x1F2B: 
                                        case 0x1F2C: 
                                        case 0x1F2D: 
                                        case 0x1F2E: 
                                        case 0x1F2F: 
                                        case 0x1F30: 
                                        case 0x1F31: 
                                        case 0x1F32: 
                                        case 0x1F33: 
                                        case 0x1F34: 
                                        case 0x1F35: 
                                        case 0x1F36: 
                                        case 0x1F37: 
                                        case 0x1F38: 
                                        case 0x1F39: 
                                        case 0x1F3A: 
                                        case 0x1F3B: 
                                        case 0x1F3C: 
                                        case 0x1F3D: 
                                        case 0x1F3E: 
                                        case 0x1F3F: 
                                        case 0x1F40: 
                                        case 0x1F41: 
                                        case 0x1F42: 
                                        case 0x1F43: 
                                        case 0x1F44: 
                                        case 0x1F45: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ἠ', 'ὅ'] */


                                    }
                                }
                            }
                        } else {
                            switch( input ) {
                                case 0x1F48: 
                                case 0x1F49: 
                                case 0x1F4A: 
                                case 0x1F4B: 
                                case 0x1F4C: 
                                case 0x1F4D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ὀ', 'Ὅ'] */

                                case 0x1F50: 
                                case 0x1F51: 
                                case 0x1F52: 
                                case 0x1F53: 
                                case 0x1F54: 
                                case 0x1F55: 
                                case 0x1F56: 
                                case 0x1F57: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ὐ', 'ὗ'] */

                                case 0x1F59: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'Ὑ' */

                                case 0x1F5B: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'Ὓ' */

                                case 0x1F5D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'Ὕ' */

                                case 0x1F5F: 
                                case 0x1F60: 
                                case 0x1F61: 
                                case 0x1F62: 
                                case 0x1F63: 
                                case 0x1F64: 
                                case 0x1F65: 
                                case 0x1F66: 
                                case 0x1F67: 
                                case 0x1F68: 
                                case 0x1F69: 
                                case 0x1F6A: 
                                case 0x1F6B: 
                                case 0x1F6C: 
                                case 0x1F6D: 
                                case 0x1F6E: 
                                case 0x1F6F: 
                                case 0x1F70: 
                                case 0x1F71: 
                                case 0x1F72: 
                                case 0x1F73: 
                                case 0x1F74: 
                                case 0x1F75: 
                                case 0x1F76: 
                                case 0x1F77: 
                                case 0x1F78: 
                                case 0x1F79: 
                                case 0x1F7A: 
                                case 0x1F7B: 
                                case 0x1F7C: 
                                case 0x1F7D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ὗ', 'ώ'] */

                                case 0x1F80: 
                                case 0x1F81: 
                                case 0x1F82: 
                                case 0x1F83: 
                                case 0x1F84: 
                                case 0x1F85: 
                                case 0x1F86: 
                                case 0x1F87: 
                                case 0x1F88: 
                                case 0x1F89: 
                                case 0x1F8A: 
                                case 0x1F8B: 
                                case 0x1F8C: 
                                case 0x1F8D: 
                                case 0x1F8E: 
                                case 0x1F8F: 
                                case 0x1F90: 
                                case 0x1F91: 
                                case 0x1F92: 
                                case 0x1F93: 
                                case 0x1F94: 
                                case 0x1F95: 
                                case 0x1F96: 
                                case 0x1F97: 
                                case 0x1F98: 
                                case 0x1F99: 
                                case 0x1F9A: 
                                case 0x1F9B: 
                                case 0x1F9C: 
                                case 0x1F9D: 
                                case 0x1F9E: 
                                case 0x1F9F: 
                                case 0x1FA0: 
                                case 0x1FA1: 
                                case 0x1FA2: 
                                case 0x1FA3: 
                                case 0x1FA4: 
                                case 0x1FA5: 
                                case 0x1FA6: 
                                case 0x1FA7: 
                                case 0x1FA8: 
                                case 0x1FA9: 
                                case 0x1FAA: 
                                case 0x1FAB: 
                                case 0x1FAC: 
                                case 0x1FAD: 
                                case 0x1FAE: 
                                case 0x1FAF: 
                                case 0x1FB0: 
                                case 0x1FB1: 
                                case 0x1FB2: 
                                case 0x1FB3: 
                                case 0x1FB4: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᾀ', 'ᾴ'] */

                                case 0x1FB6: 
                                case 0x1FB7: 
                                case 0x1FB8: 
                                case 0x1FB9: 
                                case 0x1FBA: 
                                case 0x1FBB: 
                                case 0x1FBC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ᾶ', 'ᾼ'] */


                            }
                        }
                    }
                } else {
                    if( input < 0x20E5 ) {
                        switch( input ) {
                            case 0x1FBE: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ι' */

                            case 0x1FC2: 
                            case 0x1FC3: 
                            case 0x1FC4: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ῂ', 'ῄ'] */

                            case 0x1FC6: 
                            case 0x1FC7: 
                            case 0x1FC8: 
                            case 0x1FC9: 
                            case 0x1FCA: 
                            case 0x1FCB: 
                            case 0x1FCC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ῆ', 'ῌ'] */

                            case 0x1FD0: 
                            case 0x1FD1: 
                            case 0x1FD2: 
                            case 0x1FD3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ῐ', 'ΐ'] */

                            case 0x1FD6: 
                            case 0x1FD7: 
                            case 0x1FD8: 
                            case 0x1FD9: 
                            case 0x1FDA: 
                            case 0x1FDB: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ῖ', 'Ί'] */

                            case 0x1FE0: 
                            case 0x1FE1: 
                            case 0x1FE2: 
                            case 0x1FE3: 
                            case 0x1FE4: 
                            case 0x1FE5: 
                            case 0x1FE6: 
                            case 0x1FE7: 
                            case 0x1FE8: 
                            case 0x1FE9: 
                            case 0x1FEA: 
                            case 0x1FEB: 
                            case 0x1FEC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ῠ', 'Ῥ'] */

                            case 0x1FF2: 
                            case 0x1FF3: 
                            case 0x1FF4: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ῲ', 'ῴ'] */

                            case 0x1FF6: 
                            case 0x1FF7: 
                            case 0x1FF8: 
                            case 0x1FF9: 
                            case 0x1FFA: 
                            case 0x1FFB: 
                            case 0x1FFC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ῶ', 'ῼ'] */

                            case 0x2009: QUEX_GOTO_STATE(template_482_target_2[state_key]);/* ' ' */

                            case 0x203F: 
                            case 0x2040: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['‿', '⁀'] */

                            case 0x2054: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '⁔' */

                            case 0x2071: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ⁱ' */

                            case 0x207F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ⁿ' */

                            case 0x2080: 
                            case 0x2081: 
                            case 0x2082: 
                            case 0x2083: 
                            case 0x2084: 
                            case 0x2085: 
                            case 0x2086: 
                            case 0x2087: 
                            case 0x2088: 
                            case 0x2089: QUEX_GOTO_STATE(template_482_target_3[state_key]);/* ['₀', '₉'] */

                            case 0x2090: 
                            case 0x2091: 
                            case 0x2092: 
                            case 0x2093: 
                            case 0x2094: 
                            case 0x2095: 
                            case 0x2096: 
                            case 0x2097: 
                            case 0x2098: 
                            case 0x2099: 
                            case 0x209A: 
                            case 0x209B: 
                            case 0x209C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ₐ', 'ₜ'] */

                            case 0x20D0: 
                            case 0x20D1: 
                            case 0x20D2: 
                            case 0x20D3: 
                            case 0x20D4: 
                            case 0x20D5: 
                            case 0x20D6: 
                            case 0x20D7: 
                            case 0x20D8: 
                            case 0x20D9: 
                            case 0x20DA: 
                            case 0x20DB: 
                            case 0x20DC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['⃐', '⃜'] */

                            case 0x20E1: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '⃡' */


                        }
                    } else {
                        if( input < 0x2128 ) {
                            switch( input ) {
                                case 0x20E5: 
                                case 0x20E6: 
                                case 0x20E7: 
                                case 0x20E8: 
                                case 0x20E9: 
                                case 0x20EA: 
                                case 0x20EB: 
                                case 0x20EC: 
                                case 0x20ED: 
                                case 0x20EE: 
                                case 0x20EF: 
                                case 0x20F0: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['⃥', '⃰'] */

                                case 0x2102: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ℂ' */

                                case 0x2107: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ℇ' */

                                case 0x210A: 
                                case 0x210B: 
                                case 0x210C: 
                                case 0x210D: 
                                case 0x210E: 
                                case 0x210F: 
                                case 0x2110: 
                                case 0x2111: 
                                case 0x2112: 
                                case 0x2113: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ℊ', 'ℓ'] */

                                case 0x2115: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ℕ' */

                                case 0x2118: 
                                case 0x2119: 
                                case 0x211A: 
                                case 0x211B: 
                                case 0x211C: 
                                case 0x211D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['℘', 'ℝ'] */

                                case 0x2124: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ℤ' */

                                case 0x2126: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'Ω' */


                            }
                        } else {
                            if( input < 0x214E ) {
                                switch( input ) {
                                    case 0x2128: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ℨ' */

                                    case 0x212A: 
                                    case 0x212B: 
                                    case 0x212C: 
                                    case 0x212D: 
                                    case 0x212E: 
                                    case 0x212F: 
                                    case 0x2130: 
                                    case 0x2131: 
                                    case 0x2132: 
                                    case 0x2133: 
                                    case 0x2134: 
                                    case 0x2135: 
                                    case 0x2136: 
                                    case 0x2137: 
                                    case 0x2138: 
                                    case 0x2139: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['K', 'ℹ'] */

                                    case 0x213C: 
                                    case 0x213D: 
                                    case 0x213E: 
                                    case 0x213F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ℼ', 'ℿ'] */

                                    case 0x2145: 
                                    case 0x2146: 
                                    case 0x2147: 
                                    case 0x2148: 
                                    case 0x2149: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⅅ', 'ⅉ'] */


                                }
                            } else {
                                if( input < 0x2C00 ) {
                                    switch( input ) {
                                        case 0x214E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ⅎ' */

                                        case 0x2160: 
                                        case 0x2161: 
                                        case 0x2162: 
                                        case 0x2163: 
                                        case 0x2164: 
                                        case 0x2165: 
                                        case 0x2166: 
                                        case 0x2167: 
                                        case 0x2168: 
                                        case 0x2169: 
                                        case 0x216A: 
                                        case 0x216B: 
                                        case 0x216C: 
                                        case 0x216D: 
                                        case 0x216E: 
                                        case 0x216F: 
                                        case 0x2170: 
                                        case 0x2171: 
                                        case 0x2172: 
                                        case 0x2173: 
                                        case 0x2174: 
                                        case 0x2175: 
                                        case 0x2176: 
                                        case 0x2177: 
                                        case 0x2178: 
                                        case 0x2179: 
                                        case 0x217A: 
                                        case 0x217B: 
                                        case 0x217C: 
                                        case 0x217D: 
                                        case 0x217E: 
                                        case 0x217F: 
                                        case 0x2180: 
                                        case 0x2181: 
                                        case 0x2182: 
                                        case 0x2183: 
                                        case 0x2184: 
                                        case 0x2185: 
                                        case 0x2186: 
                                        case 0x2187: 
                                        case 0x2188: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ⅰ', 'ↈ'] */


                                    }
                                } else {
                                    if( input < 0x2C2F ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ⰰ', 'Ⱞ'] */

                                    } else if( input == 0x2C2F ) {

                                    } else if( input < 0x2C5F ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⰰ', 'ⱞ'] */

                                    } else if( input == 0x2C5F ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ⱡ', 'ⳤ'] */

                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if( input < 0xA62C ) {
                    if( input < 0x3031 ) {
                        if( input < 0x2DB7 ) {
                            if( input < 0x2D70 ) {
                                if( input < 0x2D26 ) {
                                    switch( input ) {
                                        case 0x2CEB: 
                                        case 0x2CEC: 
                                        case 0x2CED: 
                                        case 0x2CEE: 
                                        case 0x2CEF: 
                                        case 0x2CF0: 
                                        case 0x2CF1: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ⳬ', '⳱'] */

                                        case 0x2D00: 
                                        case 0x2D01: 
                                        case 0x2D02: 
                                        case 0x2D03: 
                                        case 0x2D04: 
                                        case 0x2D05: 
                                        case 0x2D06: 
                                        case 0x2D07: 
                                        case 0x2D08: 
                                        case 0x2D09: 
                                        case 0x2D0A: 
                                        case 0x2D0B: 
                                        case 0x2D0C: 
                                        case 0x2D0D: 
                                        case 0x2D0E: 
                                        case 0x2D0F: 
                                        case 0x2D10: 
                                        case 0x2D11: 
                                        case 0x2D12: 
                                        case 0x2D13: 
                                        case 0x2D14: 
                                        case 0x2D15: 
                                        case 0x2D16: 
                                        case 0x2D17: 
                                        case 0x2D18: 
                                        case 0x2D19: 
                                        case 0x2D1A: 
                                        case 0x2D1B: 
                                        case 0x2D1C: 
                                        case 0x2D1D: 
                                        case 0x2D1E: 
                                        case 0x2D1F: 
                                        case 0x2D20: 
                                        case 0x2D21: 
                                        case 0x2D22: 
                                        case 0x2D23: 
                                        case 0x2D24: 
                                        case 0x2D25: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⴀ', 'ⴥ'] */


                                    }
                                } else {
                                    switch( input ) {
                                        case 0x2D30: 
                                        case 0x2D31: 
                                        case 0x2D32: 
                                        case 0x2D33: 
                                        case 0x2D34: 
                                        case 0x2D35: 
                                        case 0x2D36: 
                                        case 0x2D37: 
                                        case 0x2D38: 
                                        case 0x2D39: 
                                        case 0x2D3A: 
                                        case 0x2D3B: 
                                        case 0x2D3C: 
                                        case 0x2D3D: 
                                        case 0x2D3E: 
                                        case 0x2D3F: 
                                        case 0x2D40: 
                                        case 0x2D41: 
                                        case 0x2D42: 
                                        case 0x2D43: 
                                        case 0x2D44: 
                                        case 0x2D45: 
                                        case 0x2D46: 
                                        case 0x2D47: 
                                        case 0x2D48: 
                                        case 0x2D49: 
                                        case 0x2D4A: 
                                        case 0x2D4B: 
                                        case 0x2D4C: 
                                        case 0x2D4D: 
                                        case 0x2D4E: 
                                        case 0x2D4F: 
                                        case 0x2D50: 
                                        case 0x2D51: 
                                        case 0x2D52: 
                                        case 0x2D53: 
                                        case 0x2D54: 
                                        case 0x2D55: 
                                        case 0x2D56: 
                                        case 0x2D57: 
                                        case 0x2D58: 
                                        case 0x2D59: 
                                        case 0x2D5A: 
                                        case 0x2D5B: 
                                        case 0x2D5C: 
                                        case 0x2D5D: 
                                        case 0x2D5E: 
                                        case 0x2D5F: 
                                        case 0x2D60: 
                                        case 0x2D61: 
                                        case 0x2D62: 
                                        case 0x2D63: 
                                        case 0x2D64: 
                                        case 0x2D65: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⴰ', 'ⵥ'] */

                                        case 0x2D6F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ⵯ' */


                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x2D7F: 
                                    case 0x2D80: 
                                    case 0x2D81: 
                                    case 0x2D82: 
                                    case 0x2D83: 
                                    case 0x2D84: 
                                    case 0x2D85: 
                                    case 0x2D86: 
                                    case 0x2D87: 
                                    case 0x2D88: 
                                    case 0x2D89: 
                                    case 0x2D8A: 
                                    case 0x2D8B: 
                                    case 0x2D8C: 
                                    case 0x2D8D: 
                                    case 0x2D8E: 
                                    case 0x2D8F: 
                                    case 0x2D90: 
                                    case 0x2D91: 
                                    case 0x2D92: 
                                    case 0x2D93: 
                                    case 0x2D94: 
                                    case 0x2D95: 
                                    case 0x2D96: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['⵿', 'ⶖ'] */

                                    case 0x2DA0: 
                                    case 0x2DA1: 
                                    case 0x2DA2: 
                                    case 0x2DA3: 
                                    case 0x2DA4: 
                                    case 0x2DA5: 
                                    case 0x2DA6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⶠ', 'ⶦ'] */

                                    case 0x2DA8: 
                                    case 0x2DA9: 
                                    case 0x2DAA: 
                                    case 0x2DAB: 
                                    case 0x2DAC: 
                                    case 0x2DAD: 
                                    case 0x2DAE: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⶨ', 'ⶮ'] */

                                    case 0x2DB0: 
                                    case 0x2DB1: 
                                    case 0x2DB2: 
                                    case 0x2DB3: 
                                    case 0x2DB4: 
                                    case 0x2DB5: 
                                    case 0x2DB6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⶰ', 'ⶶ'] */


                                }
                            }
                        } else {
                            switch( input ) {
                                case 0x2DB8: 
                                case 0x2DB9: 
                                case 0x2DBA: 
                                case 0x2DBB: 
                                case 0x2DBC: 
                                case 0x2DBD: 
                                case 0x2DBE: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⶸ', 'ⶾ'] */

                                case 0x2DC0: 
                                case 0x2DC1: 
                                case 0x2DC2: 
                                case 0x2DC3: 
                                case 0x2DC4: 
                                case 0x2DC5: 
                                case 0x2DC6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⷀ', 'ⷆ'] */

                                case 0x2DC8: 
                                case 0x2DC9: 
                                case 0x2DCA: 
                                case 0x2DCB: 
                                case 0x2DCC: 
                                case 0x2DCD: 
                                case 0x2DCE: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⷈ', 'ⷎ'] */

                                case 0x2DD0: 
                                case 0x2DD1: 
                                case 0x2DD2: 
                                case 0x2DD3: 
                                case 0x2DD4: 
                                case 0x2DD5: 
                                case 0x2DD6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⷐ', 'ⷖ'] */

                                case 0x2DD8: 
                                case 0x2DD9: 
                                case 0x2DDA: 
                                case 0x2DDB: 
                                case 0x2DDC: 
                                case 0x2DDD: 
                                case 0x2DDE: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⷘ', 'ⷞ'] */

                                case 0x2DE0: 
                                case 0x2DE1: 
                                case 0x2DE2: 
                                case 0x2DE3: 
                                case 0x2DE4: 
                                case 0x2DE5: 
                                case 0x2DE6: 
                                case 0x2DE7: 
                                case 0x2DE8: 
                                case 0x2DE9: 
                                case 0x2DEA: 
                                case 0x2DEB: 
                                case 0x2DEC: 
                                case 0x2DED: 
                                case 0x2DEE: 
                                case 0x2DEF: 
                                case 0x2DF0: 
                                case 0x2DF1: 
                                case 0x2DF2: 
                                case 0x2DF3: 
                                case 0x2DF4: 
                                case 0x2DF5: 
                                case 0x2DF6: 
                                case 0x2DF7: 
                                case 0x2DF8: 
                                case 0x2DF9: 
                                case 0x2DFA: 
                                case 0x2DFB: 
                                case 0x2DFC: 
                                case 0x2DFD: 
                                case 0x2DFE: 
                                case 0x2DFF: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ⷠ', 'ⷿ'] */

                                case 0x3005: 
                                case 0x3006: 
                                case 0x3007: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['々', '〇'] */

                                case 0x3021: 
                                case 0x3022: 
                                case 0x3023: 
                                case 0x3024: 
                                case 0x3025: 
                                case 0x3026: 
                                case 0x3027: 
                                case 0x3028: 
                                case 0x3029: 
                                case 0x302A: 
                                case 0x302B: 
                                case 0x302C: 
                                case 0x302D: 
                                case 0x302E: 
                                case 0x302F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['〡', '〯'] */


                            }
                        }
                    } else {
                        if( input < 0x3131 ) {
                            if( input < 0x309D ) {
                                switch( input ) {
                                    case 0x3031: 
                                    case 0x3032: 
                                    case 0x3033: 
                                    case 0x3034: 
                                    case 0x3035: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['〱', '〵'] */

                                    case 0x3038: 
                                    case 0x3039: 
                                    case 0x303A: 
                                    case 0x303B: 
                                    case 0x303C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['〸', '〼'] */

                                    case 0x3041: 
                                    case 0x3042: 
                                    case 0x3043: 
                                    case 0x3044: 
                                    case 0x3045: 
                                    case 0x3046: 
                                    case 0x3047: 
                                    case 0x3048: 
                                    case 0x3049: 
                                    case 0x304A: 
                                    case 0x304B: 
                                    case 0x304C: 
                                    case 0x304D: 
                                    case 0x304E: 
                                    case 0x304F: 
                                    case 0x3050: 
                                    case 0x3051: 
                                    case 0x3052: 
                                    case 0x3053: 
                                    case 0x3054: 
                                    case 0x3055: 
                                    case 0x3056: 
                                    case 0x3057: 
                                    case 0x3058: 
                                    case 0x3059: 
                                    case 0x305A: 
                                    case 0x305B: 
                                    case 0x305C: 
                                    case 0x305D: 
                                    case 0x305E: 
                                    case 0x305F: 
                                    case 0x3060: 
                                    case 0x3061: 
                                    case 0x3062: 
                                    case 0x3063: 
                                    case 0x3064: 
                                    case 0x3065: 
                                    case 0x3066: 
                                    case 0x3067: 
                                    case 0x3068: 
                                    case 0x3069: 
                                    case 0x306A: 
                                    case 0x306B: 
                                    case 0x306C: 
                                    case 0x306D: 
                                    case 0x306E: 
                                    case 0x306F: 
                                    case 0x3070: 
                                    case 0x3071: 
                                    case 0x3072: 
                                    case 0x3073: 
                                    case 0x3074: 
                                    case 0x3075: 
                                    case 0x3076: 
                                    case 0x3077: 
                                    case 0x3078: 
                                    case 0x3079: 
                                    case 0x307A: 
                                    case 0x307B: 
                                    case 0x307C: 
                                    case 0x307D: 
                                    case 0x307E: 
                                    case 0x307F: 
                                    case 0x3080: 
                                    case 0x3081: 
                                    case 0x3082: 
                                    case 0x3083: 
                                    case 0x3084: 
                                    case 0x3085: 
                                    case 0x3086: 
                                    case 0x3087: 
                                    case 0x3088: 
                                    case 0x3089: 
                                    case 0x308A: 
                                    case 0x308B: 
                                    case 0x308C: 
                                    case 0x308D: 
                                    case 0x308E: 
                                    case 0x308F: 
                                    case 0x3090: 
                                    case 0x3091: 
                                    case 0x3092: 
                                    case 0x3093: 
                                    case 0x3094: 
                                    case 0x3095: 
                                    case 0x3096: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ぁ', 'ゖ'] */

                                    case 0x3099: 
                                    case 0x309A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['゙', '゚'] */


                                }
                            } else {
                                if( input < 0x30FC ) {
                                    if( input < 0x30A0 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ゝ', 'ゟ'] */

                                    } else if( input == 0x30A0 ) {

                                    } else if( input < 0x30FB ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ァ', 'ヺ'] */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x30FC: 
                                        case 0x30FD: 
                                        case 0x30FE: 
                                        case 0x30FF: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ー', 'ヿ'] */

                                        case 0x3105: 
                                        case 0x3106: 
                                        case 0x3107: 
                                        case 0x3108: 
                                        case 0x3109: 
                                        case 0x310A: 
                                        case 0x310B: 
                                        case 0x310C: 
                                        case 0x310D: 
                                        case 0x310E: 
                                        case 0x310F: 
                                        case 0x3110: 
                                        case 0x3111: 
                                        case 0x3112: 
                                        case 0x3113: 
                                        case 0x3114: 
                                        case 0x3115: 
                                        case 0x3116: 
                                        case 0x3117: 
                                        case 0x3118: 
                                        case 0x3119: 
                                        case 0x311A: 
                                        case 0x311B: 
                                        case 0x311C: 
                                        case 0x311D: 
                                        case 0x311E: 
                                        case 0x311F: 
                                        case 0x3120: 
                                        case 0x3121: 
                                        case 0x3122: 
                                        case 0x3123: 
                                        case 0x3124: 
                                        case 0x3125: 
                                        case 0x3126: 
                                        case 0x3127: 
                                        case 0x3128: 
                                        case 0x3129: 
                                        case 0x312A: 
                                        case 0x312B: 
                                        case 0x312C: 
                                        case 0x312D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ㄅ', 'ㄭ'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0x4E00 ) {
                                if( input < 0x31F0 ) {
                                    if( input < 0x318F ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ㄱ', 'ㆎ'] */

                                    } else if( input < 0x31A0 ) {

                                    } else if( input < 0x31BB ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ㆠ', 'ㆺ'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x3200 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ㇰ', 'ㇿ'] */

                                    } else if( input < 0x3400 ) {

                                    } else if( input < 0x4DB6 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['㐀', '䶵'] */

                                    } else {

                                    }
                                }
                            } else {
                                if( input < 0xA4D0 ) {
                                    if( input < 0x9FCC ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['一', '鿋'] */

                                    } else if( input < 0xA000 ) {

                                    } else if( input < 0xA48D ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꀀ', 'ꒌ'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0xA4FE ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꓐ', 'ꓽ'] */

                                    } else if( input < 0xA500 ) {

                                    } else if( input < 0xA60D ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꔀ', 'ꘌ'] */

                                    } else if( input < 0xA610 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꘐ', 'ꘫ'] */

                                    }
                                }
                            }
                        }
                    }
                } else {
                    if( input < 0xA930 ) {
                        if( input < 0xA792 ) {
                            if( input < 0xA6F2 ) {
                                if( input < 0xA67E ) {
                                    switch( input ) {
                                        case 0xA640: 
                                        case 0xA641: 
                                        case 0xA642: 
                                        case 0xA643: 
                                        case 0xA644: 
                                        case 0xA645: 
                                        case 0xA646: 
                                        case 0xA647: 
                                        case 0xA648: 
                                        case 0xA649: 
                                        case 0xA64A: 
                                        case 0xA64B: 
                                        case 0xA64C: 
                                        case 0xA64D: 
                                        case 0xA64E: 
                                        case 0xA64F: 
                                        case 0xA650: 
                                        case 0xA651: 
                                        case 0xA652: 
                                        case 0xA653: 
                                        case 0xA654: 
                                        case 0xA655: 
                                        case 0xA656: 
                                        case 0xA657: 
                                        case 0xA658: 
                                        case 0xA659: 
                                        case 0xA65A: 
                                        case 0xA65B: 
                                        case 0xA65C: 
                                        case 0xA65D: 
                                        case 0xA65E: 
                                        case 0xA65F: 
                                        case 0xA660: 
                                        case 0xA661: 
                                        case 0xA662: 
                                        case 0xA663: 
                                        case 0xA664: 
                                        case 0xA665: 
                                        case 0xA666: 
                                        case 0xA667: 
                                        case 0xA668: 
                                        case 0xA669: 
                                        case 0xA66A: 
                                        case 0xA66B: 
                                        case 0xA66C: 
                                        case 0xA66D: 
                                        case 0xA66E: 
                                        case 0xA66F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ꙁ', '꙯'] */

                                        case 0xA67C: 
                                        case 0xA67D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['꙼', '꙽'] */


                                    }
                                } else {
                                    if( input == 0xA67E ) {

                                    } else if( input < 0xA698 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꙿ', 'ꚗ'] */

                                    } else if( input < 0xA6A0 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꚠ', '꛱'] */

                                    }
                                }
                            } else {
                                if( input < 0xA789 ) {
                                    if( input < 0xA717 ) {

                                    } else if( input < 0xA720 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꜗ', 'ꜟ'] */

                                    } else if( input < 0xA722 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ꜣ', 'ꞈ'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0xA78B: 
                                        case 0xA78C: 
                                        case 0xA78D: 
                                        case 0xA78E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ꞌ', 'ꞎ'] */

                                        case 0xA790: 
                                        case 0xA791: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ꞑ', 'ꞑ'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0xA8C5 ) {
                                if( input < 0xA828 ) {
                                    switch( input ) {
                                        case 0xA7A0: 
                                        case 0xA7A1: 
                                        case 0xA7A2: 
                                        case 0xA7A3: 
                                        case 0xA7A4: 
                                        case 0xA7A5: 
                                        case 0xA7A6: 
                                        case 0xA7A7: 
                                        case 0xA7A8: 
                                        case 0xA7A9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ꞡ', 'ꞩ'] */

                                        case 0xA7FA: 
                                        case 0xA7FB: 
                                        case 0xA7FC: 
                                        case 0xA7FD: 
                                        case 0xA7FE: 
                                        case 0xA7FF: 
                                        case 0xA800: 
                                        case 0xA801: 
                                        case 0xA802: 
                                        case 0xA803: 
                                        case 0xA804: 
                                        case 0xA805: 
                                        case 0xA806: 
                                        case 0xA807: 
                                        case 0xA808: 
                                        case 0xA809: 
                                        case 0xA80A: 
                                        case 0xA80B: 
                                        case 0xA80C: 
                                        case 0xA80D: 
                                        case 0xA80E: 
                                        case 0xA80F: 
                                        case 0xA810: 
                                        case 0xA811: 
                                        case 0xA812: 
                                        case 0xA813: 
                                        case 0xA814: 
                                        case 0xA815: 
                                        case 0xA816: 
                                        case 0xA817: 
                                        case 0xA818: 
                                        case 0xA819: 
                                        case 0xA81A: 
                                        case 0xA81B: 
                                        case 0xA81C: 
                                        case 0xA81D: 
                                        case 0xA81E: 
                                        case 0xA81F: 
                                        case 0xA820: 
                                        case 0xA821: 
                                        case 0xA822: 
                                        case 0xA823: 
                                        case 0xA824: 
                                        case 0xA825: 
                                        case 0xA826: 
                                        case 0xA827: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꟺ', 'ꠧ'] */


                                    }
                                } else {
                                    if( input < 0xA840 ) {

                                    } else if( input < 0xA874 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꡀ', 'ꡳ'] */

                                    } else if( input < 0xA880 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꢀ', '꣄'] */

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0xA8D0: 
                                    case 0xA8D1: 
                                    case 0xA8D2: 
                                    case 0xA8D3: 
                                    case 0xA8D4: 
                                    case 0xA8D5: 
                                    case 0xA8D6: 
                                    case 0xA8D7: 
                                    case 0xA8D8: 
                                    case 0xA8D9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['꣐', '꣙'] */

                                    case 0xA8E0: 
                                    case 0xA8E1: 
                                    case 0xA8E2: 
                                    case 0xA8E3: 
                                    case 0xA8E4: 
                                    case 0xA8E5: 
                                    case 0xA8E6: 
                                    case 0xA8E7: 
                                    case 0xA8E8: 
                                    case 0xA8E9: 
                                    case 0xA8EA: 
                                    case 0xA8EB: 
                                    case 0xA8EC: 
                                    case 0xA8ED: 
                                    case 0xA8EE: 
                                    case 0xA8EF: 
                                    case 0xA8F0: 
                                    case 0xA8F1: 
                                    case 0xA8F2: 
                                    case 0xA8F3: 
                                    case 0xA8F4: 
                                    case 0xA8F5: 
                                    case 0xA8F6: 
                                    case 0xA8F7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['꣠', 'ꣷ'] */

                                    case 0xA8FB: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ꣻ' */

                                    case 0xA900: 
                                    case 0xA901: 
                                    case 0xA902: 
                                    case 0xA903: 
                                    case 0xA904: 
                                    case 0xA905: 
                                    case 0xA906: 
                                    case 0xA907: 
                                    case 0xA908: 
                                    case 0xA909: 
                                    case 0xA90A: 
                                    case 0xA90B: 
                                    case 0xA90C: 
                                    case 0xA90D: 
                                    case 0xA90E: 
                                    case 0xA90F: 
                                    case 0xA910: 
                                    case 0xA911: 
                                    case 0xA912: 
                                    case 0xA913: 
                                    case 0xA914: 
                                    case 0xA915: 
                                    case 0xA916: 
                                    case 0xA917: 
                                    case 0xA918: 
                                    case 0xA919: 
                                    case 0xA91A: 
                                    case 0xA91B: 
                                    case 0xA91C: 
                                    case 0xA91D: 
                                    case 0xA91E: 
                                    case 0xA91F: 
                                    case 0xA920: 
                                    case 0xA921: 
                                    case 0xA922: 
                                    case 0xA923: 
                                    case 0xA924: 
                                    case 0xA925: 
                                    case 0xA926: 
                                    case 0xA927: 
                                    case 0xA928: 
                                    case 0xA929: 
                                    case 0xA92A: 
                                    case 0xA92B: 
                                    case 0xA92C: 
                                    case 0xA92D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['꤀', '꤭'] */


                                }
                            }
                        }
                    } else {
                        if( input < 0xAA7A ) {
                            if( input < 0xAA00 ) {
                                if( input < 0xA980 ) {
                                    switch( input ) {
                                        case 0xA930: 
                                        case 0xA931: 
                                        case 0xA932: 
                                        case 0xA933: 
                                        case 0xA934: 
                                        case 0xA935: 
                                        case 0xA936: 
                                        case 0xA937: 
                                        case 0xA938: 
                                        case 0xA939: 
                                        case 0xA93A: 
                                        case 0xA93B: 
                                        case 0xA93C: 
                                        case 0xA93D: 
                                        case 0xA93E: 
                                        case 0xA93F: 
                                        case 0xA940: 
                                        case 0xA941: 
                                        case 0xA942: 
                                        case 0xA943: 
                                        case 0xA944: 
                                        case 0xA945: 
                                        case 0xA946: 
                                        case 0xA947: 
                                        case 0xA948: 
                                        case 0xA949: 
                                        case 0xA94A: 
                                        case 0xA94B: 
                                        case 0xA94C: 
                                        case 0xA94D: 
                                        case 0xA94E: 
                                        case 0xA94F: 
                                        case 0xA950: 
                                        case 0xA951: 
                                        case 0xA952: 
                                        case 0xA953: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꤰ', '꥓'] */

                                        case 0xA960: 
                                        case 0xA961: 
                                        case 0xA962: 
                                        case 0xA963: 
                                        case 0xA964: 
                                        case 0xA965: 
                                        case 0xA966: 
                                        case 0xA967: 
                                        case 0xA968: 
                                        case 0xA969: 
                                        case 0xA96A: 
                                        case 0xA96B: 
                                        case 0xA96C: 
                                        case 0xA96D: 
                                        case 0xA96E: 
                                        case 0xA96F: 
                                        case 0xA970: 
                                        case 0xA971: 
                                        case 0xA972: 
                                        case 0xA973: 
                                        case 0xA974: 
                                        case 0xA975: 
                                        case 0xA976: 
                                        case 0xA977: 
                                        case 0xA978: 
                                        case 0xA979: 
                                        case 0xA97A: 
                                        case 0xA97B: 
                                        case 0xA97C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꥠ', 'ꥼ'] */


                                    }
                                } else {
                                    if( input < 0xA9C1 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꦀ', '꧀'] */

                                    } else if( input < 0xA9CF ) {

                                    } else if( input < 0xA9DA ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꧏ', '꧙'] */

                                    } else {

                                    }
                                }
                            } else {
                                if( input < 0xAA50 ) {
                                    if( input < 0xAA37 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꨀ', 'ꨶ'] */

                                    } else if( input < 0xAA40 ) {

                                    } else if( input < 0xAA4E ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꩀ', 'ꩍ'] */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0xAA50: 
                                        case 0xAA51: 
                                        case 0xAA52: 
                                        case 0xAA53: 
                                        case 0xAA54: 
                                        case 0xAA55: 
                                        case 0xAA56: 
                                        case 0xAA57: 
                                        case 0xAA58: 
                                        case 0xAA59: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['꩐', '꩙'] */

                                        case 0xAA60: 
                                        case 0xAA61: 
                                        case 0xAA62: 
                                        case 0xAA63: 
                                        case 0xAA64: 
                                        case 0xAA65: 
                                        case 0xAA66: 
                                        case 0xAA67: 
                                        case 0xAA68: 
                                        case 0xAA69: 
                                        case 0xAA6A: 
                                        case 0xAA6B: 
                                        case 0xAA6C: 
                                        case 0xAA6D: 
                                        case 0xAA6E: 
                                        case 0xAA6F: 
                                        case 0xAA70: 
                                        case 0xAA71: 
                                        case 0xAA72: 
                                        case 0xAA73: 
                                        case 0xAA74: 
                                        case 0xAA75: 
                                        case 0xAA76: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꩠ', 'ꩶ'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0xAB09 ) {
                                switch( input ) {
                                    case 0xAA7A: 
                                    case 0xAA7B: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꩺ', 'ꩻ'] */

                                    case 0xAA80: 
                                    case 0xAA81: 
                                    case 0xAA82: 
                                    case 0xAA83: 
                                    case 0xAA84: 
                                    case 0xAA85: 
                                    case 0xAA86: 
                                    case 0xAA87: 
                                    case 0xAA88: 
                                    case 0xAA89: 
                                    case 0xAA8A: 
                                    case 0xAA8B: 
                                    case 0xAA8C: 
                                    case 0xAA8D: 
                                    case 0xAA8E: 
                                    case 0xAA8F: 
                                    case 0xAA90: 
                                    case 0xAA91: 
                                    case 0xAA92: 
                                    case 0xAA93: 
                                    case 0xAA94: 
                                    case 0xAA95: 
                                    case 0xAA96: 
                                    case 0xAA97: 
                                    case 0xAA98: 
                                    case 0xAA99: 
                                    case 0xAA9A: 
                                    case 0xAA9B: 
                                    case 0xAA9C: 
                                    case 0xAA9D: 
                                    case 0xAA9E: 
                                    case 0xAA9F: 
                                    case 0xAAA0: 
                                    case 0xAAA1: 
                                    case 0xAAA2: 
                                    case 0xAAA3: 
                                    case 0xAAA4: 
                                    case 0xAAA5: 
                                    case 0xAAA6: 
                                    case 0xAAA7: 
                                    case 0xAAA8: 
                                    case 0xAAA9: 
                                    case 0xAAAA: 
                                    case 0xAAAB: 
                                    case 0xAAAC: 
                                    case 0xAAAD: 
                                    case 0xAAAE: 
                                    case 0xAAAF: 
                                    case 0xAAB0: 
                                    case 0xAAB1: 
                                    case 0xAAB2: 
                                    case 0xAAB3: 
                                    case 0xAAB4: 
                                    case 0xAAB5: 
                                    case 0xAAB6: 
                                    case 0xAAB7: 
                                    case 0xAAB8: 
                                    case 0xAAB9: 
                                    case 0xAABA: 
                                    case 0xAABB: 
                                    case 0xAABC: 
                                    case 0xAABD: 
                                    case 0xAABE: 
                                    case 0xAABF: 
                                    case 0xAAC0: 
                                    case 0xAAC1: 
                                    case 0xAAC2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꪀ', 'ꫂ'] */

                                    case 0xAADB: 
                                    case 0xAADC: 
                                    case 0xAADD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꫛ', 'ꫝ'] */

                                    case 0xAB01: 
                                    case 0xAB02: 
                                    case 0xAB03: 
                                    case 0xAB04: 
                                    case 0xAB05: 
                                    case 0xAB06: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꬁ', 'ꬆ'] */


                                }
                            } else {
                                switch( input ) {
                                    case 0xAB09: 
                                    case 0xAB0A: 
                                    case 0xAB0B: 
                                    case 0xAB0C: 
                                    case 0xAB0D: 
                                    case 0xAB0E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꬉ', 'ꬎ'] */

                                    case 0xAB11: 
                                    case 0xAB12: 
                                    case 0xAB13: 
                                    case 0xAB14: 
                                    case 0xAB15: 
                                    case 0xAB16: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꬑ', 'ꬖ'] */

                                    case 0xAB20: 
                                    case 0xAB21: 
                                    case 0xAB22: 
                                    case 0xAB23: 
                                    case 0xAB24: 
                                    case 0xAB25: 
                                    case 0xAB26: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꬠ', 'ꬦ'] */

                                    case 0xAB28: 
                                    case 0xAB29: 
                                    case 0xAB2A: 
                                    case 0xAB2B: 
                                    case 0xAB2C: 
                                    case 0xAB2D: 
                                    case 0xAB2E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꬨ', 'ꬮ'] */

                                    case 0xABC0: 
                                    case 0xABC1: 
                                    case 0xABC2: 
                                    case 0xABC3: 
                                    case 0xABC4: 
                                    case 0xABC5: 
                                    case 0xABC6: 
                                    case 0xABC7: 
                                    case 0xABC8: 
                                    case 0xABC9: 
                                    case 0xABCA: 
                                    case 0xABCB: 
                                    case 0xABCC: 
                                    case 0xABCD: 
                                    case 0xABCE: 
                                    case 0xABCF: 
                                    case 0xABD0: 
                                    case 0xABD1: 
                                    case 0xABD2: 
                                    case 0xABD3: 
                                    case 0xABD4: 
                                    case 0xABD5: 
                                    case 0xABD6: 
                                    case 0xABD7: 
                                    case 0xABD8: 
                                    case 0xABD9: 
                                    case 0xABDA: 
                                    case 0xABDB: 
                                    case 0xABDC: 
                                    case 0xABDD: 
                                    case 0xABDE: 
                                    case 0xABDF: 
                                    case 0xABE0: 
                                    case 0xABE1: 
                                    case 0xABE2: 
                                    case 0xABE3: 
                                    case 0xABE4: 
                                    case 0xABE5: 
                                    case 0xABE6: 
                                    case 0xABE7: 
                                    case 0xABE8: 
                                    case 0xABE9: 
                                    case 0xABEA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ꯀ', 'ꯪ'] */


                                }
                            }
                        }
                    }
                }
            }
        } else {
            if( input < 0x1083C ) {
                if( input < 0xFE7F ) {
                    if( input < 0xFB45 ) {
                        if( input < 0xFADA ) {
                            if( input < 0xD7C7 ) {
                                if( input < 0xABFA ) {
                                    switch( input ) {
                                        case 0xABEC: 
                                        case 0xABED: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['꯬', '꯭'] */

                                        case 0xABF0: 
                                        case 0xABF1: 
                                        case 0xABF2: 
                                        case 0xABF3: 
                                        case 0xABF4: 
                                        case 0xABF5: 
                                        case 0xABF6: 
                                        case 0xABF7: 
                                        case 0xABF8: 
                                        case 0xABF9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['꯰', '꯹'] */


                                    }
                                } else {
                                    if( input < 0xAC00 ) {

                                    } else if( input < 0xD7A4 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['가', '힣'] */

                                    } else if( input < 0xD7B0 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ힰ', 'ퟆ'] */

                                    }
                                }
                            } else {
                                if( input < 0xFA2E ) {
                                    if( input < 0xD7CB ) {

                                    } else if( input < 0xD7FC ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ퟋ', 'ퟻ'] */

                                    } else if( input < 0xF900 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['豈', '鶴'] */

                                    }
                                } else {
                                    if( input < 0xFA30 ) {

                                    } else if( input < 0xFA6E ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['侮', '舘'] */

                                    } else if( input < 0xFA70 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['並', '龎'] */

                                    }
                                }
                            }
                        } else {
                            switch( input ) {
                                case 0xFB00: 
                                case 0xFB01: 
                                case 0xFB02: 
                                case 0xFB03: 
                                case 0xFB04: 
                                case 0xFB05: 
                                case 0xFB06: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ﬀ', 'ﬆ'] */

                                case 0xFB13: 
                                case 0xFB14: 
                                case 0xFB15: 
                                case 0xFB16: 
                                case 0xFB17: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ﬓ', 'ﬗ'] */

                                case 0xFB1D: 
                                case 0xFB1E: 
                                case 0xFB1F: 
                                case 0xFB20: 
                                case 0xFB21: 
                                case 0xFB22: 
                                case 0xFB23: 
                                case 0xFB24: 
                                case 0xFB25: 
                                case 0xFB26: 
                                case 0xFB27: 
                                case 0xFB28: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['יִ', 'ﬨ'] */

                                case 0xFB2A: 
                                case 0xFB2B: 
                                case 0xFB2C: 
                                case 0xFB2D: 
                                case 0xFB2E: 
                                case 0xFB2F: 
                                case 0xFB30: 
                                case 0xFB31: 
                                case 0xFB32: 
                                case 0xFB33: 
                                case 0xFB34: 
                                case 0xFB35: 
                                case 0xFB36: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['שׁ', 'זּ'] */

                                case 0xFB38: 
                                case 0xFB39: 
                                case 0xFB3A: 
                                case 0xFB3B: 
                                case 0xFB3C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['טּ', 'לּ'] */

                                case 0xFB3E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'מּ' */

                                case 0xFB40: 
                                case 0xFB41: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['נּ', 'סּ'] */

                                case 0xFB43: 
                                case 0xFB44: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ףּ', 'פּ'] */


                            }
                        }
                    } else {
                        if( input < 0xFE27 ) {
                            if( input < 0xFD90 ) {
                                if( input < 0xFC5E ) {
                                    if( input == 0xFB45 ) {

                                    } else if( input < 0xFBB2 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['צּ', 'ﮱ'] */

                                    } else if( input < 0xFBD3 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ﯓ', 'ﱝ'] */

                                    }
                                } else {
                                    if( input < 0xFC64 ) {

                                    } else if( input < 0xFD3E ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ﱤ', 'ﴽ'] */

                                    } else if( input < 0xFD50 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ﵐ', 'ﶏ'] */

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0xFD92: 
                                    case 0xFD93: 
                                    case 0xFD94: 
                                    case 0xFD95: 
                                    case 0xFD96: 
                                    case 0xFD97: 
                                    case 0xFD98: 
                                    case 0xFD99: 
                                    case 0xFD9A: 
                                    case 0xFD9B: 
                                    case 0xFD9C: 
                                    case 0xFD9D: 
                                    case 0xFD9E: 
                                    case 0xFD9F: 
                                    case 0xFDA0: 
                                    case 0xFDA1: 
                                    case 0xFDA2: 
                                    case 0xFDA3: 
                                    case 0xFDA4: 
                                    case 0xFDA5: 
                                    case 0xFDA6: 
                                    case 0xFDA7: 
                                    case 0xFDA8: 
                                    case 0xFDA9: 
                                    case 0xFDAA: 
                                    case 0xFDAB: 
                                    case 0xFDAC: 
                                    case 0xFDAD: 
                                    case 0xFDAE: 
                                    case 0xFDAF: 
                                    case 0xFDB0: 
                                    case 0xFDB1: 
                                    case 0xFDB2: 
                                    case 0xFDB3: 
                                    case 0xFDB4: 
                                    case 0xFDB5: 
                                    case 0xFDB6: 
                                    case 0xFDB7: 
                                    case 0xFDB8: 
                                    case 0xFDB9: 
                                    case 0xFDBA: 
                                    case 0xFDBB: 
                                    case 0xFDBC: 
                                    case 0xFDBD: 
                                    case 0xFDBE: 
                                    case 0xFDBF: 
                                    case 0xFDC0: 
                                    case 0xFDC1: 
                                    case 0xFDC2: 
                                    case 0xFDC3: 
                                    case 0xFDC4: 
                                    case 0xFDC5: 
                                    case 0xFDC6: 
                                    case 0xFDC7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ﶒ', 'ﷇ'] */

                                    case 0xFDF0: 
                                    case 0xFDF1: 
                                    case 0xFDF2: 
                                    case 0xFDF3: 
                                    case 0xFDF4: 
                                    case 0xFDF5: 
                                    case 0xFDF6: 
                                    case 0xFDF7: 
                                    case 0xFDF8: 
                                    case 0xFDF9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ﷰ', 'ﷹ'] */

                                    case 0xFE00: 
                                    case 0xFE01: 
                                    case 0xFE02: 
                                    case 0xFE03: 
                                    case 0xFE04: 
                                    case 0xFE05: 
                                    case 0xFE06: 
                                    case 0xFE07: 
                                    case 0xFE08: 
                                    case 0xFE09: 
                                    case 0xFE0A: 
                                    case 0xFE0B: 
                                    case 0xFE0C: 
                                    case 0xFE0D: 
                                    case 0xFE0E: 
                                    case 0xFE0F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['︀', '️'] */

                                    case 0xFE20: 
                                    case 0xFE21: 
                                    case 0xFE22: 
                                    case 0xFE23: 
                                    case 0xFE24: 
                                    case 0xFE25: 
                                    case 0xFE26: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['︠', '︦'] */


                                }
                            }
                        } else {
                            switch( input ) {
                                case 0xFE33: 
                                case 0xFE34: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['︳', '︴'] */

                                case 0xFE4D: 
                                case 0xFE4E: 
                                case 0xFE4F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['﹍', '﹏'] */

                                case 0xFE71: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ﹱ' */

                                case 0xFE73: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ﹳ' */

                                case 0xFE77: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ﹷ' */

                                case 0xFE79: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ﹹ' */

                                case 0xFE7B: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ﹻ' */

                                case 0xFE7D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* 'ﹽ' */


                            }
                        }
                    }
                } else {
                    if( input < 0x100FB ) {
                        if( input < 0xFFD2 ) {
                            if( input < 0xFF41 ) {
                                if( input < 0xFF21 ) {
                                    if( input < 0xFEFD ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ﹿ', 'ﻼ'] */

                                    } else if( input < 0xFF10 ) {

                                    } else if( input < 0xFF1A ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['０', '９'] */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0xFF21: 
                                        case 0xFF22: 
                                        case 0xFF23: 
                                        case 0xFF24: 
                                        case 0xFF25: 
                                        case 0xFF26: 
                                        case 0xFF27: 
                                        case 0xFF28: 
                                        case 0xFF29: 
                                        case 0xFF2A: 
                                        case 0xFF2B: 
                                        case 0xFF2C: 
                                        case 0xFF2D: 
                                        case 0xFF2E: 
                                        case 0xFF2F: 
                                        case 0xFF30: 
                                        case 0xFF31: 
                                        case 0xFF32: 
                                        case 0xFF33: 
                                        case 0xFF34: 
                                        case 0xFF35: 
                                        case 0xFF36: 
                                        case 0xFF37: 
                                        case 0xFF38: 
                                        case 0xFF39: 
                                        case 0xFF3A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['Ａ', 'Ｚ'] */

                                        case 0xFF3F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '＿' */


                                    }
                                }
                            } else {
                                if( input < 0xFFC2 ) {
                                    if( input < 0xFF5B ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ａ', 'ｚ'] */

                                    } else if( input < 0xFF66 ) {

                                    } else if( input < 0xFFBF ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ｦ', 'ﾾ'] */

                                    } else {

                                    }
                                } else {
                                    switch( input ) {
                                        case 0xFFC2: 
                                        case 0xFFC3: 
                                        case 0xFFC4: 
                                        case 0xFFC5: 
                                        case 0xFFC6: 
                                        case 0xFFC7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ￂ', 'ￇ'] */

                                        case 0xFFCA: 
                                        case 0xFFCB: 
                                        case 0xFFCC: 
                                        case 0xFFCD: 
                                        case 0xFFCE: 
                                        case 0xFFCF: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ￊ', 'ￏ'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0x10028 ) {
                                switch( input ) {
                                    case 0xFFD2: 
                                    case 0xFFD3: 
                                    case 0xFFD4: 
                                    case 0xFFD5: 
                                    case 0xFFD6: 
                                    case 0xFFD7: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ￒ', 'ￗ'] */

                                    case 0xFFDA: 
                                    case 0xFFDB: 
                                    case 0xFFDC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['ￚ', 'ￜ'] */

                                    case 0x10000: 
                                    case 0x10001: 
                                    case 0x10002: 
                                    case 0x10003: 
                                    case 0x10004: 
                                    case 0x10005: 
                                    case 0x10006: 
                                    case 0x10007: 
                                    case 0x10008: 
                                    case 0x10009: 
                                    case 0x1000A: 
                                    case 0x1000B: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐀀', '𐀋'] */

                                    case 0x1000D: 
                                    case 0x1000E: 
                                    case 0x1000F: 
                                    case 0x10010: 
                                    case 0x10011: 
                                    case 0x10012: 
                                    case 0x10013: 
                                    case 0x10014: 
                                    case 0x10015: 
                                    case 0x10016: 
                                    case 0x10017: 
                                    case 0x10018: 
                                    case 0x10019: 
                                    case 0x1001A: 
                                    case 0x1001B: 
                                    case 0x1001C: 
                                    case 0x1001D: 
                                    case 0x1001E: 
                                    case 0x1001F: 
                                    case 0x10020: 
                                    case 0x10021: 
                                    case 0x10022: 
                                    case 0x10023: 
                                    case 0x10024: 
                                    case 0x10025: 
                                    case 0x10026: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐀍', '𐀦'] */


                                }
                            } else {
                                if( input < 0x1003F ) {
                                    switch( input ) {
                                        case 0x10028: 
                                        case 0x10029: 
                                        case 0x1002A: 
                                        case 0x1002B: 
                                        case 0x1002C: 
                                        case 0x1002D: 
                                        case 0x1002E: 
                                        case 0x1002F: 
                                        case 0x10030: 
                                        case 0x10031: 
                                        case 0x10032: 
                                        case 0x10033: 
                                        case 0x10034: 
                                        case 0x10035: 
                                        case 0x10036: 
                                        case 0x10037: 
                                        case 0x10038: 
                                        case 0x10039: 
                                        case 0x1003A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐀨', '𐀺'] */

                                        case 0x1003C: 
                                        case 0x1003D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐀼', '𐀽'] */


                                    }
                                } else {
                                    if( input < 0x1004E ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐀿', '𐁍'] */

                                    } else if( input < 0x10050 ) {

                                    } else if( input < 0x1005E ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐁐', '𐁝'] */

                                    } else if( input < 0x10080 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐂀', '𐃺'] */

                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0x103C4 ) {
                            if( input < 0x102D1 ) {
                                if( input < 0x101FE ) {
                                    switch( input ) {
                                        case 0x10140: 
                                        case 0x10141: 
                                        case 0x10142: 
                                        case 0x10143: 
                                        case 0x10144: 
                                        case 0x10145: 
                                        case 0x10146: 
                                        case 0x10147: 
                                        case 0x10148: 
                                        case 0x10149: 
                                        case 0x1014A: 
                                        case 0x1014B: 
                                        case 0x1014C: 
                                        case 0x1014D: 
                                        case 0x1014E: 
                                        case 0x1014F: 
                                        case 0x10150: 
                                        case 0x10151: 
                                        case 0x10152: 
                                        case 0x10153: 
                                        case 0x10154: 
                                        case 0x10155: 
                                        case 0x10156: 
                                        case 0x10157: 
                                        case 0x10158: 
                                        case 0x10159: 
                                        case 0x1015A: 
                                        case 0x1015B: 
                                        case 0x1015C: 
                                        case 0x1015D: 
                                        case 0x1015E: 
                                        case 0x1015F: 
                                        case 0x10160: 
                                        case 0x10161: 
                                        case 0x10162: 
                                        case 0x10163: 
                                        case 0x10164: 
                                        case 0x10165: 
                                        case 0x10166: 
                                        case 0x10167: 
                                        case 0x10168: 
                                        case 0x10169: 
                                        case 0x1016A: 
                                        case 0x1016B: 
                                        case 0x1016C: 
                                        case 0x1016D: 
                                        case 0x1016E: 
                                        case 0x1016F: 
                                        case 0x10170: 
                                        case 0x10171: 
                                        case 0x10172: 
                                        case 0x10173: 
                                        case 0x10174: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐅀', '𐅴'] */

                                        case 0x101FD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '𐇽' */


                                    }
                                } else {
                                    if( input < 0x10280 ) {

                                    } else if( input < 0x1029D ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐊀', '𐊜'] */

                                    } else if( input < 0x102A0 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐊠', '𐋐'] */

                                    }
                                }
                            } else {
                                if( input < 0x1034B ) {
                                    switch( input ) {
                                        case 0x10300: 
                                        case 0x10301: 
                                        case 0x10302: 
                                        case 0x10303: 
                                        case 0x10304: 
                                        case 0x10305: 
                                        case 0x10306: 
                                        case 0x10307: 
                                        case 0x10308: 
                                        case 0x10309: 
                                        case 0x1030A: 
                                        case 0x1030B: 
                                        case 0x1030C: 
                                        case 0x1030D: 
                                        case 0x1030E: 
                                        case 0x1030F: 
                                        case 0x10310: 
                                        case 0x10311: 
                                        case 0x10312: 
                                        case 0x10313: 
                                        case 0x10314: 
                                        case 0x10315: 
                                        case 0x10316: 
                                        case 0x10317: 
                                        case 0x10318: 
                                        case 0x10319: 
                                        case 0x1031A: 
                                        case 0x1031B: 
                                        case 0x1031C: 
                                        case 0x1031D: 
                                        case 0x1031E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐌀', '𐌞'] */

                                        case 0x10330: 
                                        case 0x10331: 
                                        case 0x10332: 
                                        case 0x10333: 
                                        case 0x10334: 
                                        case 0x10335: 
                                        case 0x10336: 
                                        case 0x10337: 
                                        case 0x10338: 
                                        case 0x10339: 
                                        case 0x1033A: 
                                        case 0x1033B: 
                                        case 0x1033C: 
                                        case 0x1033D: 
                                        case 0x1033E: 
                                        case 0x1033F: 
                                        case 0x10340: 
                                        case 0x10341: 
                                        case 0x10342: 
                                        case 0x10343: 
                                        case 0x10344: 
                                        case 0x10345: 
                                        case 0x10346: 
                                        case 0x10347: 
                                        case 0x10348: 
                                        case 0x10349: 
                                        case 0x1034A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐌰', '𐍊'] */


                                    }
                                } else {
                                    switch( input ) {
                                        case 0x10380: 
                                        case 0x10381: 
                                        case 0x10382: 
                                        case 0x10383: 
                                        case 0x10384: 
                                        case 0x10385: 
                                        case 0x10386: 
                                        case 0x10387: 
                                        case 0x10388: 
                                        case 0x10389: 
                                        case 0x1038A: 
                                        case 0x1038B: 
                                        case 0x1038C: 
                                        case 0x1038D: 
                                        case 0x1038E: 
                                        case 0x1038F: 
                                        case 0x10390: 
                                        case 0x10391: 
                                        case 0x10392: 
                                        case 0x10393: 
                                        case 0x10394: 
                                        case 0x10395: 
                                        case 0x10396: 
                                        case 0x10397: 
                                        case 0x10398: 
                                        case 0x10399: 
                                        case 0x1039A: 
                                        case 0x1039B: 
                                        case 0x1039C: 
                                        case 0x1039D: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐎀', '𐎝'] */

                                        case 0x103A0: 
                                        case 0x103A1: 
                                        case 0x103A2: 
                                        case 0x103A3: 
                                        case 0x103A4: 
                                        case 0x103A5: 
                                        case 0x103A6: 
                                        case 0x103A7: 
                                        case 0x103A8: 
                                        case 0x103A9: 
                                        case 0x103AA: 
                                        case 0x103AB: 
                                        case 0x103AC: 
                                        case 0x103AD: 
                                        case 0x103AE: 
                                        case 0x103AF: 
                                        case 0x103B0: 
                                        case 0x103B1: 
                                        case 0x103B2: 
                                        case 0x103B3: 
                                        case 0x103B4: 
                                        case 0x103B5: 
                                        case 0x103B6: 
                                        case 0x103B7: 
                                        case 0x103B8: 
                                        case 0x103B9: 
                                        case 0x103BA: 
                                        case 0x103BB: 
                                        case 0x103BC: 
                                        case 0x103BD: 
                                        case 0x103BE: 
                                        case 0x103BF: 
                                        case 0x103C0: 
                                        case 0x103C1: 
                                        case 0x103C2: 
                                        case 0x103C3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐎠', '𐏃'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0x104AA ) {
                                if( input < 0x103D6 ) {
                                    switch( input ) {
                                        case 0x103C8: 
                                        case 0x103C9: 
                                        case 0x103CA: 
                                        case 0x103CB: 
                                        case 0x103CC: 
                                        case 0x103CD: 
                                        case 0x103CE: 
                                        case 0x103CF: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐏈', '𐏏'] */

                                        case 0x103D1: 
                                        case 0x103D2: 
                                        case 0x103D3: 
                                        case 0x103D4: 
                                        case 0x103D5: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐏑', '𐏕'] */


                                    }
                                } else {
                                    if( input < 0x10400 ) {

                                    } else if( input < 0x1049E ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐐀', '𐒝'] */

                                    } else if( input < 0x104A0 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐒠', '𐒩'] */

                                    }
                                }
                            } else {
                                switch( input ) {
                                    case 0x10800: 
                                    case 0x10801: 
                                    case 0x10802: 
                                    case 0x10803: 
                                    case 0x10804: 
                                    case 0x10805: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐠀', '𐠅'] */

                                    case 0x10808: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '𐠈' */

                                    case 0x1080A: 
                                    case 0x1080B: 
                                    case 0x1080C: 
                                    case 0x1080D: 
                                    case 0x1080E: 
                                    case 0x1080F: 
                                    case 0x10810: 
                                    case 0x10811: 
                                    case 0x10812: 
                                    case 0x10813: 
                                    case 0x10814: 
                                    case 0x10815: 
                                    case 0x10816: 
                                    case 0x10817: 
                                    case 0x10818: 
                                    case 0x10819: 
                                    case 0x1081A: 
                                    case 0x1081B: 
                                    case 0x1081C: 
                                    case 0x1081D: 
                                    case 0x1081E: 
                                    case 0x1081F: 
                                    case 0x10820: 
                                    case 0x10821: 
                                    case 0x10822: 
                                    case 0x10823: 
                                    case 0x10824: 
                                    case 0x10825: 
                                    case 0x10826: 
                                    case 0x10827: 
                                    case 0x10828: 
                                    case 0x10829: 
                                    case 0x1082A: 
                                    case 0x1082B: 
                                    case 0x1082C: 
                                    case 0x1082D: 
                                    case 0x1082E: 
                                    case 0x1082F: 
                                    case 0x10830: 
                                    case 0x10831: 
                                    case 0x10832: 
                                    case 0x10833: 
                                    case 0x10834: 
                                    case 0x10835: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐠊', '𐠵'] */

                                    case 0x10837: 
                                    case 0x10838: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐠷', '𐠸'] */


                                }
                            }
                        }
                    }
                }
            } else {
                if( input < 0x1D4A2 ) {
                    if( input < 0x11047 ) {
                        if( input < 0x10A19 ) {
                            switch( input ) {
                                case 0x1083C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '𐠼' */

                                case 0x1083F: 
                                case 0x10840: 
                                case 0x10841: 
                                case 0x10842: 
                                case 0x10843: 
                                case 0x10844: 
                                case 0x10845: 
                                case 0x10846: 
                                case 0x10847: 
                                case 0x10848: 
                                case 0x10849: 
                                case 0x1084A: 
                                case 0x1084B: 
                                case 0x1084C: 
                                case 0x1084D: 
                                case 0x1084E: 
                                case 0x1084F: 
                                case 0x10850: 
                                case 0x10851: 
                                case 0x10852: 
                                case 0x10853: 
                                case 0x10854: 
                                case 0x10855: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐠿', '𐡕'] */

                                case 0x10900: 
                                case 0x10901: 
                                case 0x10902: 
                                case 0x10903: 
                                case 0x10904: 
                                case 0x10905: 
                                case 0x10906: 
                                case 0x10907: 
                                case 0x10908: 
                                case 0x10909: 
                                case 0x1090A: 
                                case 0x1090B: 
                                case 0x1090C: 
                                case 0x1090D: 
                                case 0x1090E: 
                                case 0x1090F: 
                                case 0x10910: 
                                case 0x10911: 
                                case 0x10912: 
                                case 0x10913: 
                                case 0x10914: 
                                case 0x10915: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐤀', '𐤕'] */

                                case 0x10920: 
                                case 0x10921: 
                                case 0x10922: 
                                case 0x10923: 
                                case 0x10924: 
                                case 0x10925: 
                                case 0x10926: 
                                case 0x10927: 
                                case 0x10928: 
                                case 0x10929: 
                                case 0x1092A: 
                                case 0x1092B: 
                                case 0x1092C: 
                                case 0x1092D: 
                                case 0x1092E: 
                                case 0x1092F: 
                                case 0x10930: 
                                case 0x10931: 
                                case 0x10932: 
                                case 0x10933: 
                                case 0x10934: 
                                case 0x10935: 
                                case 0x10936: 
                                case 0x10937: 
                                case 0x10938: 
                                case 0x10939: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐤠', '𐤹'] */

                                case 0x10A00: 
                                case 0x10A01: 
                                case 0x10A02: 
                                case 0x10A03: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐨀', '𐨃'] */

                                case 0x10A05: 
                                case 0x10A06: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐨅', '𐨆'] */

                                case 0x10A0C: 
                                case 0x10A0D: 
                                case 0x10A0E: 
                                case 0x10A0F: 
                                case 0x10A10: 
                                case 0x10A11: 
                                case 0x10A12: 
                                case 0x10A13: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐨌', '𐨓'] */

                                case 0x10A15: 
                                case 0x10A16: 
                                case 0x10A17: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐨕', '𐨗'] */


                            }
                        } else {
                            if( input < 0x10B00 ) {
                                switch( input ) {
                                    case 0x10A19: 
                                    case 0x10A1A: 
                                    case 0x10A1B: 
                                    case 0x10A1C: 
                                    case 0x10A1D: 
                                    case 0x10A1E: 
                                    case 0x10A1F: 
                                    case 0x10A20: 
                                    case 0x10A21: 
                                    case 0x10A22: 
                                    case 0x10A23: 
                                    case 0x10A24: 
                                    case 0x10A25: 
                                    case 0x10A26: 
                                    case 0x10A27: 
                                    case 0x10A28: 
                                    case 0x10A29: 
                                    case 0x10A2A: 
                                    case 0x10A2B: 
                                    case 0x10A2C: 
                                    case 0x10A2D: 
                                    case 0x10A2E: 
                                    case 0x10A2F: 
                                    case 0x10A30: 
                                    case 0x10A31: 
                                    case 0x10A32: 
                                    case 0x10A33: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐨙', '𐨳'] */

                                    case 0x10A38: 
                                    case 0x10A39: 
                                    case 0x10A3A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐨸', '𐨺'] */

                                    case 0x10A3F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '𐨿' */

                                    case 0x10A60: 
                                    case 0x10A61: 
                                    case 0x10A62: 
                                    case 0x10A63: 
                                    case 0x10A64: 
                                    case 0x10A65: 
                                    case 0x10A66: 
                                    case 0x10A67: 
                                    case 0x10A68: 
                                    case 0x10A69: 
                                    case 0x10A6A: 
                                    case 0x10A6B: 
                                    case 0x10A6C: 
                                    case 0x10A6D: 
                                    case 0x10A6E: 
                                    case 0x10A6F: 
                                    case 0x10A70: 
                                    case 0x10A71: 
                                    case 0x10A72: 
                                    case 0x10A73: 
                                    case 0x10A74: 
                                    case 0x10A75: 
                                    case 0x10A76: 
                                    case 0x10A77: 
                                    case 0x10A78: 
                                    case 0x10A79: 
                                    case 0x10A7A: 
                                    case 0x10A7B: 
                                    case 0x10A7C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐩠', '𐩼'] */


                                }
                            } else {
                                if( input < 0x10B60 ) {
                                    if( input < 0x10B36 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐬀', '𐬵'] */

                                    } else if( input < 0x10B40 ) {

                                    } else if( input < 0x10B56 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐭀', '𐭕'] */

                                    } else {

                                    }
                                } else {
                                    if( input < 0x10B73 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐭠', '𐭲'] */

                                    } else if( input < 0x10C00 ) {

                                    } else if( input < 0x10C49 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𐰀', '𐱈'] */

                                    } else if( input < 0x11000 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𑀀', '𑁆'] */

                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0x1D16A ) {
                            if( input < 0x12463 ) {
                                if( input < 0x110BB ) {
                                    if( input < 0x11066 ) {

                                    } else if( input < 0x11070 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𑁦', '𑁯'] */

                                    } else if( input < 0x11080 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𑂀', '𑂺'] */

                                    }
                                } else {
                                    if( input < 0x12000 ) {

                                    } else if( input < 0x1236F ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𒀀', '𒍮'] */

                                    } else if( input < 0x12400 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𒐀', '𒑢'] */

                                    }
                                }
                            } else {
                                if( input < 0x16A39 ) {
                                    if( input < 0x13000 ) {

                                    } else if( input < 0x1342F ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𓀀', '𓐮'] */

                                    } else if( input < 0x16800 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𖠀', '𖨸'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1B000: 
                                        case 0x1B001: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𛀀', '𛀁'] */

                                        case 0x1D165: 
                                        case 0x1D166: 
                                        case 0x1D167: 
                                        case 0x1D168: 
                                        case 0x1D169: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝅥', '𝅩'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0x1D1AE ) {
                                switch( input ) {
                                    case 0x1D16D: 
                                    case 0x1D16E: 
                                    case 0x1D16F: 
                                    case 0x1D170: 
                                    case 0x1D171: 
                                    case 0x1D172: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝅭', '𝅲'] */

                                    case 0x1D17B: 
                                    case 0x1D17C: 
                                    case 0x1D17D: 
                                    case 0x1D17E: 
                                    case 0x1D17F: 
                                    case 0x1D180: 
                                    case 0x1D181: 
                                    case 0x1D182: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝅻', '𝆂'] */

                                    case 0x1D185: 
                                    case 0x1D186: 
                                    case 0x1D187: 
                                    case 0x1D188: 
                                    case 0x1D189: 
                                    case 0x1D18A: 
                                    case 0x1D18B: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝆅', '𝆋'] */

                                    case 0x1D1AA: 
                                    case 0x1D1AB: 
                                    case 0x1D1AC: 
                                    case 0x1D1AD: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝆪', '𝆭'] */


                                }
                            } else {
                                if( input < 0x1D455 ) {
                                    if( input < 0x1D242 ) {

                                    } else if( input < 0x1D245 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝉂', '𝉄'] */

                                    } else if( input < 0x1D400 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝐀', '𝑔'] */

                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1D456: 
                                        case 0x1D457: 
                                        case 0x1D458: 
                                        case 0x1D459: 
                                        case 0x1D45A: 
                                        case 0x1D45B: 
                                        case 0x1D45C: 
                                        case 0x1D45D: 
                                        case 0x1D45E: 
                                        case 0x1D45F: 
                                        case 0x1D460: 
                                        case 0x1D461: 
                                        case 0x1D462: 
                                        case 0x1D463: 
                                        case 0x1D464: 
                                        case 0x1D465: 
                                        case 0x1D466: 
                                        case 0x1D467: 
                                        case 0x1D468: 
                                        case 0x1D469: 
                                        case 0x1D46A: 
                                        case 0x1D46B: 
                                        case 0x1D46C: 
                                        case 0x1D46D: 
                                        case 0x1D46E: 
                                        case 0x1D46F: 
                                        case 0x1D470: 
                                        case 0x1D471: 
                                        case 0x1D472: 
                                        case 0x1D473: 
                                        case 0x1D474: 
                                        case 0x1D475: 
                                        case 0x1D476: 
                                        case 0x1D477: 
                                        case 0x1D478: 
                                        case 0x1D479: 
                                        case 0x1D47A: 
                                        case 0x1D47B: 
                                        case 0x1D47C: 
                                        case 0x1D47D: 
                                        case 0x1D47E: 
                                        case 0x1D47F: 
                                        case 0x1D480: 
                                        case 0x1D481: 
                                        case 0x1D482: 
                                        case 0x1D483: 
                                        case 0x1D484: 
                                        case 0x1D485: 
                                        case 0x1D486: 
                                        case 0x1D487: 
                                        case 0x1D488: 
                                        case 0x1D489: 
                                        case 0x1D48A: 
                                        case 0x1D48B: 
                                        case 0x1D48C: 
                                        case 0x1D48D: 
                                        case 0x1D48E: 
                                        case 0x1D48F: 
                                        case 0x1D490: 
                                        case 0x1D491: 
                                        case 0x1D492: 
                                        case 0x1D493: 
                                        case 0x1D494: 
                                        case 0x1D495: 
                                        case 0x1D496: 
                                        case 0x1D497: 
                                        case 0x1D498: 
                                        case 0x1D499: 
                                        case 0x1D49A: 
                                        case 0x1D49B: 
                                        case 0x1D49C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝑖', '𝒜'] */

                                        case 0x1D49E: 
                                        case 0x1D49F: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝒞', '𝒟'] */


                                    }
                                }
                            }
                        }
                    }
                } else {
                    if( input < 0x1D6C1 ) {
                        if( input < 0x1D50D ) {
                            switch( input ) {
                                case 0x1D4A2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '𝒢' */

                                case 0x1D4A5: 
                                case 0x1D4A6: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝒥', '𝒦'] */

                                case 0x1D4A9: 
                                case 0x1D4AA: 
                                case 0x1D4AB: 
                                case 0x1D4AC: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝒩', '𝒬'] */

                                case 0x1D4AE: 
                                case 0x1D4AF: 
                                case 0x1D4B0: 
                                case 0x1D4B1: 
                                case 0x1D4B2: 
                                case 0x1D4B3: 
                                case 0x1D4B4: 
                                case 0x1D4B5: 
                                case 0x1D4B6: 
                                case 0x1D4B7: 
                                case 0x1D4B8: 
                                case 0x1D4B9: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝒮', '𝒹'] */

                                case 0x1D4BB: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '𝒻' */

                                case 0x1D4BD: 
                                case 0x1D4BE: 
                                case 0x1D4BF: 
                                case 0x1D4C0: 
                                case 0x1D4C1: 
                                case 0x1D4C2: 
                                case 0x1D4C3: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝒽', '𝓃'] */

                                case 0x1D4C5: 
                                case 0x1D4C6: 
                                case 0x1D4C7: 
                                case 0x1D4C8: 
                                case 0x1D4C9: 
                                case 0x1D4CA: 
                                case 0x1D4CB: 
                                case 0x1D4CC: 
                                case 0x1D4CD: 
                                case 0x1D4CE: 
                                case 0x1D4CF: 
                                case 0x1D4D0: 
                                case 0x1D4D1: 
                                case 0x1D4D2: 
                                case 0x1D4D3: 
                                case 0x1D4D4: 
                                case 0x1D4D5: 
                                case 0x1D4D6: 
                                case 0x1D4D7: 
                                case 0x1D4D8: 
                                case 0x1D4D9: 
                                case 0x1D4DA: 
                                case 0x1D4DB: 
                                case 0x1D4DC: 
                                case 0x1D4DD: 
                                case 0x1D4DE: 
                                case 0x1D4DF: 
                                case 0x1D4E0: 
                                case 0x1D4E1: 
                                case 0x1D4E2: 
                                case 0x1D4E3: 
                                case 0x1D4E4: 
                                case 0x1D4E5: 
                                case 0x1D4E6: 
                                case 0x1D4E7: 
                                case 0x1D4E8: 
                                case 0x1D4E9: 
                                case 0x1D4EA: 
                                case 0x1D4EB: 
                                case 0x1D4EC: 
                                case 0x1D4ED: 
                                case 0x1D4EE: 
                                case 0x1D4EF: 
                                case 0x1D4F0: 
                                case 0x1D4F1: 
                                case 0x1D4F2: 
                                case 0x1D4F3: 
                                case 0x1D4F4: 
                                case 0x1D4F5: 
                                case 0x1D4F6: 
                                case 0x1D4F7: 
                                case 0x1D4F8: 
                                case 0x1D4F9: 
                                case 0x1D4FA: 
                                case 0x1D4FB: 
                                case 0x1D4FC: 
                                case 0x1D4FD: 
                                case 0x1D4FE: 
                                case 0x1D4FF: 
                                case 0x1D500: 
                                case 0x1D501: 
                                case 0x1D502: 
                                case 0x1D503: 
                                case 0x1D504: 
                                case 0x1D505: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝓅', '𝔅'] */

                                case 0x1D507: 
                                case 0x1D508: 
                                case 0x1D509: 
                                case 0x1D50A: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝔇', '𝔊'] */


                            }
                        } else {
                            if( input < 0x1D540 ) {
                                switch( input ) {
                                    case 0x1D50D: 
                                    case 0x1D50E: 
                                    case 0x1D50F: 
                                    case 0x1D510: 
                                    case 0x1D511: 
                                    case 0x1D512: 
                                    case 0x1D513: 
                                    case 0x1D514: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝔍', '𝔔'] */

                                    case 0x1D516: 
                                    case 0x1D517: 
                                    case 0x1D518: 
                                    case 0x1D519: 
                                    case 0x1D51A: 
                                    case 0x1D51B: 
                                    case 0x1D51C: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝔖', '𝔜'] */

                                    case 0x1D51E: 
                                    case 0x1D51F: 
                                    case 0x1D520: 
                                    case 0x1D521: 
                                    case 0x1D522: 
                                    case 0x1D523: 
                                    case 0x1D524: 
                                    case 0x1D525: 
                                    case 0x1D526: 
                                    case 0x1D527: 
                                    case 0x1D528: 
                                    case 0x1D529: 
                                    case 0x1D52A: 
                                    case 0x1D52B: 
                                    case 0x1D52C: 
                                    case 0x1D52D: 
                                    case 0x1D52E: 
                                    case 0x1D52F: 
                                    case 0x1D530: 
                                    case 0x1D531: 
                                    case 0x1D532: 
                                    case 0x1D533: 
                                    case 0x1D534: 
                                    case 0x1D535: 
                                    case 0x1D536: 
                                    case 0x1D537: 
                                    case 0x1D538: 
                                    case 0x1D539: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝔞', '𝔹'] */

                                    case 0x1D53B: 
                                    case 0x1D53C: 
                                    case 0x1D53D: 
                                    case 0x1D53E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝔻', '𝔾'] */


                                }
                            } else {
                                if( input < 0x1D54A ) {
                                    switch( input ) {
                                        case 0x1D540: 
                                        case 0x1D541: 
                                        case 0x1D542: 
                                        case 0x1D543: 
                                        case 0x1D544: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝕀', '𝕄'] */

                                        case 0x1D546: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* '𝕆' */


                                    }
                                } else {
                                    if( input < 0x1D551 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝕊', '𝕐'] */

                                    } else if( input == 0x1D551 ) {

                                    } else if( input < 0x1D6A6 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝕒', '𝚥'] */

                                    } else if( input < 0x1D6A8 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝚨', '𝛀'] */

                                    }
                                }
                            }
                        }
                    } else {
                        if( input < 0x1D7A9 ) {
                            if( input < 0x1D735 ) {
                                if( input < 0x1D6FB ) {
                                    switch( input ) {
                                        case 0x1D6C2: 
                                        case 0x1D6C3: 
                                        case 0x1D6C4: 
                                        case 0x1D6C5: 
                                        case 0x1D6C6: 
                                        case 0x1D6C7: 
                                        case 0x1D6C8: 
                                        case 0x1D6C9: 
                                        case 0x1D6CA: 
                                        case 0x1D6CB: 
                                        case 0x1D6CC: 
                                        case 0x1D6CD: 
                                        case 0x1D6CE: 
                                        case 0x1D6CF: 
                                        case 0x1D6D0: 
                                        case 0x1D6D1: 
                                        case 0x1D6D2: 
                                        case 0x1D6D3: 
                                        case 0x1D6D4: 
                                        case 0x1D6D5: 
                                        case 0x1D6D6: 
                                        case 0x1D6D7: 
                                        case 0x1D6D8: 
                                        case 0x1D6D9: 
                                        case 0x1D6DA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝛂', '𝛚'] */

                                        case 0x1D6DC: 
                                        case 0x1D6DD: 
                                        case 0x1D6DE: 
                                        case 0x1D6DF: 
                                        case 0x1D6E0: 
                                        case 0x1D6E1: 
                                        case 0x1D6E2: 
                                        case 0x1D6E3: 
                                        case 0x1D6E4: 
                                        case 0x1D6E5: 
                                        case 0x1D6E6: 
                                        case 0x1D6E7: 
                                        case 0x1D6E8: 
                                        case 0x1D6E9: 
                                        case 0x1D6EA: 
                                        case 0x1D6EB: 
                                        case 0x1D6EC: 
                                        case 0x1D6ED: 
                                        case 0x1D6EE: 
                                        case 0x1D6EF: 
                                        case 0x1D6F0: 
                                        case 0x1D6F1: 
                                        case 0x1D6F2: 
                                        case 0x1D6F3: 
                                        case 0x1D6F4: 
                                        case 0x1D6F5: 
                                        case 0x1D6F6: 
                                        case 0x1D6F7: 
                                        case 0x1D6F8: 
                                        case 0x1D6F9: 
                                        case 0x1D6FA: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝛜', '𝛺'] */


                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1D6FC: 
                                        case 0x1D6FD: 
                                        case 0x1D6FE: 
                                        case 0x1D6FF: 
                                        case 0x1D700: 
                                        case 0x1D701: 
                                        case 0x1D702: 
                                        case 0x1D703: 
                                        case 0x1D704: 
                                        case 0x1D705: 
                                        case 0x1D706: 
                                        case 0x1D707: 
                                        case 0x1D708: 
                                        case 0x1D709: 
                                        case 0x1D70A: 
                                        case 0x1D70B: 
                                        case 0x1D70C: 
                                        case 0x1D70D: 
                                        case 0x1D70E: 
                                        case 0x1D70F: 
                                        case 0x1D710: 
                                        case 0x1D711: 
                                        case 0x1D712: 
                                        case 0x1D713: 
                                        case 0x1D714: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝛼', '𝜔'] */

                                        case 0x1D716: 
                                        case 0x1D717: 
                                        case 0x1D718: 
                                        case 0x1D719: 
                                        case 0x1D71A: 
                                        case 0x1D71B: 
                                        case 0x1D71C: 
                                        case 0x1D71D: 
                                        case 0x1D71E: 
                                        case 0x1D71F: 
                                        case 0x1D720: 
                                        case 0x1D721: 
                                        case 0x1D722: 
                                        case 0x1D723: 
                                        case 0x1D724: 
                                        case 0x1D725: 
                                        case 0x1D726: 
                                        case 0x1D727: 
                                        case 0x1D728: 
                                        case 0x1D729: 
                                        case 0x1D72A: 
                                        case 0x1D72B: 
                                        case 0x1D72C: 
                                        case 0x1D72D: 
                                        case 0x1D72E: 
                                        case 0x1D72F: 
                                        case 0x1D730: 
                                        case 0x1D731: 
                                        case 0x1D732: 
                                        case 0x1D733: 
                                        case 0x1D734: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝜖', '𝜴'] */


                                    }
                                }
                            } else {
                                if( input < 0x1D76F ) {
                                    switch( input ) {
                                        case 0x1D736: 
                                        case 0x1D737: 
                                        case 0x1D738: 
                                        case 0x1D739: 
                                        case 0x1D73A: 
                                        case 0x1D73B: 
                                        case 0x1D73C: 
                                        case 0x1D73D: 
                                        case 0x1D73E: 
                                        case 0x1D73F: 
                                        case 0x1D740: 
                                        case 0x1D741: 
                                        case 0x1D742: 
                                        case 0x1D743: 
                                        case 0x1D744: 
                                        case 0x1D745: 
                                        case 0x1D746: 
                                        case 0x1D747: 
                                        case 0x1D748: 
                                        case 0x1D749: 
                                        case 0x1D74A: 
                                        case 0x1D74B: 
                                        case 0x1D74C: 
                                        case 0x1D74D: 
                                        case 0x1D74E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝜶', '𝝎'] */

                                        case 0x1D750: 
                                        case 0x1D751: 
                                        case 0x1D752: 
                                        case 0x1D753: 
                                        case 0x1D754: 
                                        case 0x1D755: 
                                        case 0x1D756: 
                                        case 0x1D757: 
                                        case 0x1D758: 
                                        case 0x1D759: 
                                        case 0x1D75A: 
                                        case 0x1D75B: 
                                        case 0x1D75C: 
                                        case 0x1D75D: 
                                        case 0x1D75E: 
                                        case 0x1D75F: 
                                        case 0x1D760: 
                                        case 0x1D761: 
                                        case 0x1D762: 
                                        case 0x1D763: 
                                        case 0x1D764: 
                                        case 0x1D765: 
                                        case 0x1D766: 
                                        case 0x1D767: 
                                        case 0x1D768: 
                                        case 0x1D769: 
                                        case 0x1D76A: 
                                        case 0x1D76B: 
                                        case 0x1D76C: 
                                        case 0x1D76D: 
                                        case 0x1D76E: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝝐', '𝝮'] */


                                    }
                                } else {
                                    switch( input ) {
                                        case 0x1D770: 
                                        case 0x1D771: 
                                        case 0x1D772: 
                                        case 0x1D773: 
                                        case 0x1D774: 
                                        case 0x1D775: 
                                        case 0x1D776: 
                                        case 0x1D777: 
                                        case 0x1D778: 
                                        case 0x1D779: 
                                        case 0x1D77A: 
                                        case 0x1D77B: 
                                        case 0x1D77C: 
                                        case 0x1D77D: 
                                        case 0x1D77E: 
                                        case 0x1D77F: 
                                        case 0x1D780: 
                                        case 0x1D781: 
                                        case 0x1D782: 
                                        case 0x1D783: 
                                        case 0x1D784: 
                                        case 0x1D785: 
                                        case 0x1D786: 
                                        case 0x1D787: 
                                        case 0x1D788: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝝰', '𝞈'] */

                                        case 0x1D78A: 
                                        case 0x1D78B: 
                                        case 0x1D78C: 
                                        case 0x1D78D: 
                                        case 0x1D78E: 
                                        case 0x1D78F: 
                                        case 0x1D790: 
                                        case 0x1D791: 
                                        case 0x1D792: 
                                        case 0x1D793: 
                                        case 0x1D794: 
                                        case 0x1D795: 
                                        case 0x1D796: 
                                        case 0x1D797: 
                                        case 0x1D798: 
                                        case 0x1D799: 
                                        case 0x1D79A: 
                                        case 0x1D79B: 
                                        case 0x1D79C: 
                                        case 0x1D79D: 
                                        case 0x1D79E: 
                                        case 0x1D79F: 
                                        case 0x1D7A0: 
                                        case 0x1D7A1: 
                                        case 0x1D7A2: 
                                        case 0x1D7A3: 
                                        case 0x1D7A4: 
                                        case 0x1D7A5: 
                                        case 0x1D7A6: 
                                        case 0x1D7A7: 
                                        case 0x1D7A8: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝞊', '𝞨'] */


                                    }
                                }
                            }
                        } else {
                            if( input < 0x2A6D7 ) {
                                if( input < 0x1D7CC ) {
                                    switch( input ) {
                                        case 0x1D7AA: 
                                        case 0x1D7AB: 
                                        case 0x1D7AC: 
                                        case 0x1D7AD: 
                                        case 0x1D7AE: 
                                        case 0x1D7AF: 
                                        case 0x1D7B0: 
                                        case 0x1D7B1: 
                                        case 0x1D7B2: 
                                        case 0x1D7B3: 
                                        case 0x1D7B4: 
                                        case 0x1D7B5: 
                                        case 0x1D7B6: 
                                        case 0x1D7B7: 
                                        case 0x1D7B8: 
                                        case 0x1D7B9: 
                                        case 0x1D7BA: 
                                        case 0x1D7BB: 
                                        case 0x1D7BC: 
                                        case 0x1D7BD: 
                                        case 0x1D7BE: 
                                        case 0x1D7BF: 
                                        case 0x1D7C0: 
                                        case 0x1D7C1: 
                                        case 0x1D7C2: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝞪', '𝟂'] */

                                        case 0x1D7C4: 
                                        case 0x1D7C5: 
                                        case 0x1D7C6: 
                                        case 0x1D7C7: 
                                        case 0x1D7C8: 
                                        case 0x1D7C9: 
                                        case 0x1D7CA: 
                                        case 0x1D7CB: QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝟄', '𝟋'] */


                                    }
                                } else {
                                    if( input < 0x1D7CE ) {

                                    } else if( input < 0x1D800 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𝟎', '𝟿'] */

                                    } else if( input < 0x20000 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𠀀', '𪛖'] */

                                    }
                                }
                            } else {
                                if( input < 0x2B81E ) {
                                    if( input < 0x2A700 ) {

                                    } else if( input < 0x2B735 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𪜀', '𫜴'] */

                                    } else if( input < 0x2B740 ) {

                                    } else {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['𫝀', '𫠝'] */

                                    }
                                } else {
                                    if( input < 0x2F800 ) {

                                    } else if( input < 0x2FA1E ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['丽', '𪘀'] */

                                    } else if( input < 0xE0100 ) {

                                    } else if( input < 0xE01F0 ) {
                                        QUEX_GOTO_STATE(template_482_target_1[state_key]);/* ['󠄀', '󠇯'] */

                                    } else {

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
_492:
    __quex_debug_template_drop_out(482, state_key);

    switch( state_key ) {
        case 0x0: 
        case 0x1:         goto TERMINAL_355;
        case 0x2: 
        case 0x3:         goto TERMINAL_354;

    }
#   undef __QUEX_DEBUG_MAP_STATE_KEY_TO_STATE
#   define __QUEX_DEBUG_MAP_STATE_KEY_TO_STATE(X) ( \
             (X) == 0 ? 473 :    \
             (X) == 1 ? 476 :    \
             (X) == 2 ? 475 : 0)

    __quex_assert_no_passage();
_493: /* (473 from 474) (473 from 466) (473 from 458) */
    state_key = 0;
    __quex_debug("state_key = 0\n");
    goto _483;
_494: /* (476 from 475) (476 from 473) */
    state_key = 1;
    __quex_debug("state_key = 1\n");
    goto _483;
_495: /* (475 from 473) */
    state_key = 2;
    __quex_debug("state_key = 2\n");

_483: /* (473 from 473) (476 from 476) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_template_state(483, state_key);
    switch( input ) {
        case 0xB2: 
        case 0xB3: QUEX_GOTO_STATE(template_483_target_0[state_key]);/* ['²', '³'] */

        case 0xB9: QUEX_GOTO_STATE(template_483_target_0[state_key]);/* '¹' */

        case 0xFF: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 483, 496);/* 'ÿ' */

        case 0x2070: QUEX_GOTO_STATE(template_483_target_0[state_key]);/* '⁰' */

        case 0x2074: 
        case 0x2075: 
        case 0x2076: 
        case 0x2077: 
        case 0x2078: 
        case 0x2079: QUEX_GOTO_STATE(template_483_target_0[state_key]);/* ['⁴', '⁹'] */

        case 0x207A: 
        case 0x207B: QUEX_GOTO_STATE(template_483_target_1[state_key]);/* ['⁺', '⁻'] */

        case 0x2080: 
        case 0x2081: 
        case 0x2082: 
        case 0x2083: 
        case 0x2084: 
        case 0x2085: 
        case 0x2086: 
        case 0x2087: 
        case 0x2088: 
        case 0x2089: QUEX_GOTO_STATE(template_483_target_2[state_key]);/* ['₀', '₉'] */


    }
_496:
    __quex_debug_template_drop_out(483, state_key);

    switch( state_key ) {
        case 0x0: 
        case 0x1:         goto TERMINAL_355;
        case 0x2:         me->buffer._input_p -= 1; 
        goto TERMINAL_355;

    }
#   undef __QUEX_DEBUG_MAP_STATE_KEY_TO_STATE
#   define __QUEX_DEBUG_MAP_STATE_KEY_TO_STATE(X) ( \
             (X) == 0 ? 461 :    \
             (X) == 1 ? 477 : 0)

    __quex_assert_no_passage();
_485: /* (461 from 477) (461 from 455) */
    state_key = 0;
    __quex_debug("state_key = 0\n");
    goto _479;
_497: /* (477 from 461) */
    position[0] = me->buffer._input_p; __quex_debug("position[0] = input_p;\n");
    state_key = 1;
    __quex_debug("state_key = 1\n");

_479: /* (461 from 461) (477 from 477) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_template_state(479, state_key);
    switch( input ) {
        case 0x9: QUEX_GOTO_STATE(template_479_target_0[state_key]);/* '\t' */

        case 0xA: QUEX_GOTO_STATE(template_479_target_1[state_key]);/* '\n' */

        case 0xD: QUEX_GOTO_STATE(template_479_target_1[state_key]);/* '\r' */

        case 0x1C: 
        case 0x1D: 
        case 0x1E: QUEX_GOTO_STATE(template_479_target_1[state_key]);/* [\28, \30] */

        case 0x85: QUEX_GOTO_STATE(template_479_target_1[state_key]);/* '' */

        case 0xFF: QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 479, 498);/* 'ÿ' */

        case 0x2029: QUEX_GOTO_STATE(template_479_target_1[state_key]);/* ' ' */


    }
_498:
    __quex_debug_template_drop_out(479, state_key);

    switch( state_key ) {
        case 0x0:         goto TERMINAL_343;
        case 0x1:         __quex_assert(position[0] != 0x0);
me->buffer._input_p = position[0];

        goto TERMINAL_343;

    }
#   undef __QUEX_DEBUG_MAP_STATE_KEY_TO_STATE


    __quex_assert_no_passage();
_456: /* (456 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(456);
    __quex_debug_drop_out(456);
goto TERMINAL_350;

    __quex_assert_no_passage();
_457: /* (457 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(457);
    __quex_debug_drop_out(457);
goto TERMINAL_348;

    __quex_assert_no_passage();
_459: /* (459 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(459);
    __quex_debug_drop_out(459);
goto TERMINAL_347;

    __quex_assert_no_passage();
_460: /* (460 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(460);
    __quex_debug_drop_out(460);
goto TERMINAL_353;

    __quex_assert_no_passage();
_462: /* (462 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(462);
    __quex_debug_drop_out(462);
goto TERMINAL_358;

    __quex_assert_no_passage();
_463: /* (463 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(463);
    __quex_debug_drop_out(463);
goto TERMINAL_351;

    __quex_assert_no_passage();
_464: /* (464 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(464);
    __quex_debug_drop_out(464);
goto TERMINAL_356;

    __quex_assert_no_passage();
_465: /* (465 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(465);
    __quex_debug_drop_out(465);
goto TERMINAL_344;

    __quex_assert_no_passage();
_467: /* (467 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(467);
    __quex_debug_drop_out(467);
goto TERMINAL_352;

    __quex_assert_no_passage();
_468: /* (468 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(468);
    __quex_debug_drop_out(468);
goto TERMINAL_346;

    __quex_assert_no_passage();
_469: /* (469 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(469);
    __quex_debug_drop_out(469);
goto TERMINAL_345;

    __quex_assert_no_passage();
_470: /* (470 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(470);
    __quex_debug_drop_out(470);
goto TERMINAL_349;

    __quex_assert_no_passage();
_472: /* (472 from 455) */

    ++(me->buffer._input_p);
    __quex_debug_state(472);
    __quex_debug_drop_out(472);
goto TERMINAL_357;
    /* (*) Terminal states _______________________________________________________
     *
     * States that implement actions of the 'winner patterns.                     */

    /* Lexeme setup: 
     *
     * There is a temporary zero stored at the end of each lexeme, if the action 
     * references to the 'Lexeme'. 'LexemeNull' provides a reference to an empty
     * zero terminated string.                                                    */
#if defined(QUEX_OPTION_ASSERTS)
#   define Lexeme       QUEX_NAME(access_Lexeme)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeBegin  QUEX_NAME(access_LexemeBegin)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeL      QUEX_NAME(access_LexemeL)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeEnd    QUEX_NAME(access_LexemeEnd)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#else
#   define Lexeme       (me->buffer._lexeme_start_p)
#   define LexemeBegin  Lexeme
#   define LexemeL      ((size_t)(me->buffer._input_p - me->buffer._lexeme_start_p))
#   define LexemeEnd    me->buffer._input_p
#endif

#define LexemeNull      (&QUEX_LEXEME_NULL)

TERMINAL_343:
    __quex_debug("* terminal 343:   {Newline}\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
    QUEX_BUFFER_ASSERT_CONSISTENCY(&me->buffer);
    __quex_assert(QUEX_NAME(Buffer_content_size)(&me->buffer) >= 1);

    /* Indentation Counter:
        * Skip whitespace at line begin; Count indentation. */

    reference_p              = me->buffer._input_p;
    me->counter._indentation = (QUEX_TYPE_INDENTATION)0;

    goto _ENTRY_362;

_362:
    ++(me->buffer._input_p);
_ENTRY_362:
input = *(me->buffer._input_p);

    switch( input ) {
            case 0x9: goto _362;/* '\t' */

            case 0xFF: goto _RELOAD_362;/* 'ÿ' */


    }


    /* Here's where the first non-whitespace appeared after newline.
        *
        * NOTE: The entry into the indentation counter happens by matching the pattern:
        *
        *                   newline ([space]* newline)*'
        *
        * Thus, it is not possible that here a newline appears. All empty lines have
        * been eaten by the pattern match.                                            */
    me->counter._indentation = (size_t)(me->buffer._input_p - reference_p);
    __QUEX_IF_COUNT_COLUMNS_ADD(me->counter._indentation);
    QUEX_NAME(Program_on_indentation)(me, me->counter._indentation, reference_p);

    /* No need for re-entry preparation. Acceptance flags and modes are untouched. */
    goto __REENTRY;

_RELOAD_362:
    /* The application might actually be interested in the indentation string.
        * => make sure it remains in the buffer upon reload.                    */
    me->buffer._lexeme_start_p = reference_p;
    QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 362, 363);

    }
    goto __REENTRY_PREPARATION;

TERMINAL_344:
    __quex_debug("* terminal 344:   {Whitespace}\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {

    }
    goto __REENTRY_PREPARATION;

TERMINAL_345:
    __quex_debug("* terminal 345:   {Call}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 76 "src/Parser/QuexParser.qx"
    self_send(TokenCall);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12796 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_346:
    __quex_debug("* terminal 346:   {Closure}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 77 "src/Parser/QuexParser.qx"
    self_send(TokenClosure);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12810 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_347:
    __quex_debug("* terminal 347:   {Because}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 78 "src/Parser/QuexParser.qx"
    self_send(TokenBecause);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12824 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_348:
    __quex_debug("* terminal 348:   {Axiom}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 79 "src/Parser/QuexParser.qx"
    self_send(TokenAxiom);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12838 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_349:
    __quex_debug("* terminal 349:   {Proofs}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 80 "src/Parser/QuexParser.qx"
    self_send(TokenProofs);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12852 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_350:
    __quex_debug("* terminal 350:   {Therefore}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 81 "src/Parser/QuexParser.qx"
    self_send(TokenTherefore);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12866 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_351:
    __quex_debug("* terminal 351:   {BracketOpen}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 82 "src/Parser/QuexParser.qx"
    self_send(TokenBracketOpen);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12880 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_352:
    __quex_debug("* terminal 352:   {BracketClose}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 83 "src/Parser/QuexParser.qx"
    self_send(TokenBracketClose);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12894 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_353:
    __quex_debug("* terminal 353:   {BracketValue}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 84 "src/Parser/QuexParser.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TokenBracketValue);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12909 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_354:
    __quex_debug("* terminal 354:   {Identifier}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    {
#   line 85 "src/Parser/QuexParser.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TokenIdentifier);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12924 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_355:
    __quex_debug("* terminal 355:   {Number}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(LexemeL);
    {
#   line 86 "src/Parser/QuexParser.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TokenNumber);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12939 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_356:
    __quex_debug("* terminal 356:   {QuoteOpen}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 87 "src/Parser/QuexParser.qx"
    QUEX_NAME(push_mode)(&self, &Quotation);QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12952 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_357:
    __quex_debug("* terminal 357:   {QuoteClose}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 88 "src/Parser/QuexParser.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TokenFailure);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12967 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_358:
    __quex_debug("* terminal 358:   {Syntax}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 89 "src/Parser/QuexParser.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TokenIdentifier);
    QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
    
#   line 12982 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;


_490: /* TERMINAL: FAILURE */
    if(QUEX_NAME(Buffer_is_end_of_file)(&me->buffer)) {
        /* Init state is going to detect 'input == buffer limit code', and
         * enter the reload procedure, which will decide about 'end of stream'. */
    } else {
        /* In init state 'input = *input_p' and we need to increment
         * in order to avoid getting stalled. Else, input = *(input_p - 1),
         * so 'input_p' points already to the next character.                   */
        if( me->buffer._input_p == me->buffer._lexeme_start_p ) {
            /* Step over non-matching character */
            ++(me->buffer._input_p);
        }
    }
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 94 "src/Parser/QuexParser.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TokenFailure);
    
#   line 13007 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION_2;


/* TERMINAL: END_OF_STREAM */
_363:
__QUEX_IF_COUNT_SHIFT_VALUES();
    {
    QUEX_NAME(Program_on_indentation)(me, /*Indentation*/0, LexemeNull);
    
#   line 95 "src/Parser/QuexParser.qx"
    self_send(TokenEndOfStream);
    
#   line 13022 "QuexParser.cpp"

    }
    /* End of Stream causes a return from the lexical analyzer, so that no
     * tokens can be filled after the termination token.                    */
    RETURN;

__REENTRY_PREPARATION:
    /* (*) Common point for **restarting** lexical analysis.
     *     at each time when CONTINUE is called at the end of a pattern.     */
 

    /* FAILURE needs not to run through 'on_after_match'. It enters here.    */
__REENTRY_PREPARATION_2:

#   undef Lexeme
#   undef LexemeBegin
#   undef LexemeEnd
#   undef LexemeNull
#   undef LexemeL

#   ifndef __QUEX_OPTION_PLAIN_ANALYZER_OBJECT
#   ifdef  QUEX_OPTION_TOKEN_POLICY_QUEUE
    if( QUEX_NAME(TokenQueue_is_full)(&self._token_queue) ) {
        return;
    }
#   else
    if( self_token_get_id() != __QUEX_SETTING_TOKEN_ID_UNINITIALIZED) {
        return __self_result_token_id;
    }
#   endif
#   endif


    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. Post context position's live cycle:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, then it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context), then the post context position is used
     *       to reset the input position.                                              */

    /*  If a mode change happened, then the function must first return and
     *  indicate that another mode function is to be called. At this point, 
     *  we to force a 'return' on a mode change. 
     *
     *  Pseudo Code: if( previous_mode != current_mode ) {
     *                   return 0;
     *               }
     *
     *  When the analyzer returns, the caller function has to watch if a mode 
     *  change occurred. If not it can call this function again.             */
#   if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)        || defined(QUEX_OPTION_ASSERTS)
    if( me->DEBUG_analyzer_function_at_entry != me->current_analyzer_function ) 
#   endif
    { 
#       if defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)
        self_token_set_id(__QUEX_SETTING_TOKEN_ID_UNINITIALIZED);
        __QUEX_PURE_RETURN;
#       elif defined(QUEX_OPTION_ASSERTS)
        QUEX_ERROR_EXIT("Mode change without immediate return from the lexical analyzer.");
#       endif
    }

    goto __REENTRY;

    __quex_assert_no_passage();
__RELOAD_FORWARD:

    __quex_debug1("__RELOAD_FORWARD");
    __quex_assert(*(me->buffer._input_p) == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( me->buffer._memory._end_of_file_p == 0x0 ) {

        __quex_debug_reload_before(); /* Leave macro here to report source position. */
        QUEX_NAME(buffer_reload_forward)(&me->buffer, (QUEX_TYPE_CHARACTER_POSITION*)position, PositionRegisterN);

        __quex_debug_reload_after();
        QUEX_GOTO_STATE(target_state_index);
    }
    __quex_debug("reload impossible\n");
    QUEX_GOTO_STATE(target_state_else_index);
#   ifndef QUEX_OPTION_COMPUTED_GOTOS
    __quex_assert_no_passage();
__STATE_ROUTER:
    switch( target_state_index ) {
        case 362: { goto _362; }
        case 363: { goto _363; }
        case 455: { goto _455; }
        case 456: { goto _456; }
        case 457: { goto _457; }
        case 459: { goto _459; }
        case 460: { goto _460; }
        case 462: { goto _462; }
        case 463: { goto _463; }
        case 464: { goto _464; }
        case 465: { goto _465; }
        case 467: { goto _467; }
        case 468: { goto _468; }
        case 469: { goto _469; }
        case 470: { goto _470; }
        case 472: { goto _472; }
        case 479: { goto _479; }
        case 482: { goto _482; }
        case 483: { goto _483; }
        case 485: { goto _485; }
        case 486: { goto _486; }
        case 487: { goto _487; }
        case 488: { goto _488; }
        case 491: { goto _491; }
        case 492: { goto _492; }
        case 493: { goto _493; }
        case 494: { goto _494; }
        case 495: { goto _495; }
        case 496: { goto _496; }
        case 497: { goto _497; }
        case 498: { goto _498; }

        default:
            __QUEX_STD_fprintf(stderr, "State router: index = %i\n", (int)target_state_index);
            QUEX_ERROR_EXIT("State router: unknown index.\n");
    }
#   endif /* QUEX_OPTION_COMPUTED_GOTOS */

    /* Prevent compiler warning 'unused variable': use variables once in a part of the code*/
    /* that is never reached (and deleted by the compiler anyway).*/
    (void)QUEX_LEXEME_NULL;
    (void)QUEX_NAME_TOKEN(DumpedTokenIdObject);
    QUEX_ERROR_EXIT("Unreachable code has been reached.\n");
#   undef Program
#   undef Quotation
#   undef self
}
#include <quex/code_base/temporary_macros_off>
#ifdef      __QUEX_COUNT_VOID
#   undef   __QUEX_COUNT_VOID
#endif
#ifdef      __QUEX_OPTION_COUNTER
#    define __QUEX_COUNT_VOID(ME, BEGIN, END) \
            do {                              \
                QUEX_NAME(Program_counter)((ME), (BEGIN), (END));     \
                __quex_debug_counter();       \
            } while(0)
#else
#    define __QUEX_COUNT_VOID(ME, BEGIN, END) /* empty */
#endif

#include <quex/code_base/analyzer/member/basic>
#include <quex/code_base/buffer/Buffer>
#ifdef QUEX_OPTION_TOKEN_POLICY_QUEUE
#   include <quex/code_base/token/TokenQueue>
#endif

#ifdef    CONTINUE
#   undef CONTINUE
#endif
#define   CONTINUE goto __REENTRY_PREPARATION; 

#ifdef    RETURN
#   undef RETURN
#endif

#define RETURN    __QUEX_PURE_RETURN;
#include <quex/code_base/temporary_macros_on>

__QUEX_TYPE_ANALYZER_RETURN_VALUE  
QUEX_NAME(Quotation_analyzer_function)(QUEX_TYPE_ANALYZER* me) 
{
    /* NOTE: Different modes correspond to different analyzer functions. The 
     *       analyzer functions are all located inside the main class as static
     *       functions. That means, they are something like 'globals'. They 
     *       receive a pointer to the lexical analyzer, since static members do
     *       not have access to the 'this' pointer.                          */
#   if defined(QUEX_OPTION_TOKEN_POLICY_SINGLE)
    register QUEX_TYPE_TOKEN_ID __self_result_token_id 
           = (QUEX_TYPE_TOKEN_ID)__QUEX_SETTING_TOKEN_ID_UNINITIALIZED;
#   endif
#   ifdef     self
#       undef self
#   endif
#   define self (*((QUEX_TYPE_ANALYZER*)me))
    void*                          position                       = (void*)0x0;
    QUEX_TYPE_GOTO_LABEL           target_state_else_index        = QUEX_GOTO_LABEL_VOID;
    const size_t                   PositionRegisterN              = (size_t)0;
    QUEX_TYPE_CHARACTER            input                          = (QUEX_TYPE_CHARACTER)(0x00);
    QUEX_TYPE_GOTO_LABEL           target_state_index             = QUEX_GOTO_LABEL_VOID;
#   ifndef QUEX_OPTION_COMPUTED_GOTOS
#   endif /* QUEX_OPTION_COMPUTED_GOTOS */
#   define Program      (QUEX_NAME(Program))
#   define Quotation    (QUEX_NAME(Quotation))

    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. Post context position's live cycle:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, then it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context), then the post context position is used
     *       to reset the input position.                                              */
#   if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE) \
       || defined(QUEX_OPTION_ASSERTS)
    me->DEBUG_analyzer_function_at_entry = me->current_analyzer_function;
#   endif
__REENTRY:
    me->buffer._lexeme_start_p = me->buffer._input_p;
    QUEX_LEXEME_TERMINATING_ZERO_UNDO(&me->buffer);
    /* BEGIN: STATE MACHINE
     * init-state = 529L
     * 00529 (359, 288), (360, 292), (361, 306)
     *      == [-oo, 'ý'], ['Ā', '‛'], ['„', oo] ==> 00530
     *      == '“' ==> 00532
     *      == '”' ==> 00531
     *     
     * 00530 (361, 307, A)
     *      == [-oo, 'ý'], ['Ā', '‛'], ['„', oo] ==> 00530
     *     
     * 00532 (359, 289, A)
     *     
     * 00531 (360, 293, A)
     *     
     * END: STATE MACHINE
     */
_533: /* INIT_STATE_TRANSITION_BLOCK */
    input = *(me->buffer._input_p);
    __quex_debug("Init State\n");
    __quex_debug_state(529);
    if( input < 0x100 ) {
        if( input < 0xFE ) {
            goto _530;/* [\0, 'ý'] */

        } else if( input == 0xFE ) {

        } else {
            QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 529, 363);/* 'ÿ' */

        }
    } else {
        if( input < 0x201C ) {
            goto _530;/* ['Ā', '‛'] */

        } else if( input == 0x201C ) {
            goto _532;/* '“' */

        } else if( input == 0x201D ) {
            goto _531;/* '”' */

        } else {
            goto _530;/* ['„', <4294967295>] */

        }
    }
    __quex_debug_drop_out(529);

goto _490; /* TERMINAL_FAILURE */

_529:


    ++(me->buffer._input_p);
    goto _533;


    __quex_assert_no_passage();
_530: /* (530 from 530) (530 from 529) */

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p);
    __quex_debug_state(530);
    if( input < 0x100 ) {
        if( input < 0xFE ) {
            goto _530;/* [\0, 'ý'] */

        } else if( input == 0xFE ) {

        } else {
            QUEX_GOTO_RELOAD(__RELOAD_FORWARD, 530, 535);/* 'ÿ' */

        }
    } else {
        if( input < 0x201C ) {
            goto _530;/* ['Ā', '‛'] */

        } else if( input < 0x201E ) {

        } else {
            goto _530;/* ['„', <4294967295>] */

        }
    }
_535:
    __quex_debug_drop_out(530);
goto TERMINAL_361;

    __quex_assert_no_passage();
_531: /* (531 from 529) */

    ++(me->buffer._input_p);
    __quex_debug_state(531);
    __quex_debug_drop_out(531);
goto TERMINAL_360;

    __quex_assert_no_passage();
_532: /* (532 from 529) */

    ++(me->buffer._input_p);
    __quex_debug_state(532);
    __quex_debug_drop_out(532);
goto TERMINAL_359;
    /* (*) Terminal states _______________________________________________________
     *
     * States that implement actions of the 'winner patterns.                     */

    /* Lexeme setup: 
     *
     * There is a temporary zero stored at the end of each lexeme, if the action 
     * references to the 'Lexeme'. 'LexemeNull' provides a reference to an empty
     * zero terminated string.                                                    */
#if defined(QUEX_OPTION_ASSERTS)
#   define Lexeme       QUEX_NAME(access_Lexeme)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeBegin  QUEX_NAME(access_LexemeBegin)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeL      QUEX_NAME(access_LexemeL)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeEnd    QUEX_NAME(access_LexemeEnd)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#else
#   define Lexeme       (me->buffer._lexeme_start_p)
#   define LexemeBegin  Lexeme
#   define LexemeL      ((size_t)(me->buffer._input_p - me->buffer._lexeme_start_p))
#   define LexemeEnd    me->buffer._input_p
#endif

#define LexemeNull      (&QUEX_LEXEME_NULL)

TERMINAL_359:
    __quex_debug("* terminal 359:   {QuoteOpen}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 111 "src/Parser/QuexParser.qx"
        ++self.quote_depth; self_accumulator_add(LexemeBegin, LexemeEnd);
    
#   line 13369 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_360:
    __quex_debug("* terminal 360:   {QuoteClose}\n");
    __QUEX_IF_COUNT_SHIFT_VALUES();
__QUEX_IF_COUNT_COLUMNS_ADD(1);
    {
#   line 112 "src/Parser/QuexParser.qx"
    
        if(--self.quote_depth == 0) self.pop_mode();
        else self_accumulator_add(LexemeBegin, LexemeEnd);
    
    
#   line 13385 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;

TERMINAL_361:
    __quex_debug("* terminal 361:   [:inverse({QuoteOpen},{QuoteClose}):]+\n");
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    QUEX_LEXEME_TERMINATING_ZERO_SET(&me->buffer);
    {
#   line 118 "src/Parser/QuexParser.qx"
    
        self_accumulator_add(Lexeme, LexemeEnd);
    
    
#   line 13400 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION;


_490: /* TERMINAL: FAILURE */
    if(QUEX_NAME(Buffer_is_end_of_file)(&me->buffer)) {
        /* Init state is going to detect 'input == buffer limit code', and
         * enter the reload procedure, which will decide about 'end of stream'. */
    } else {
        /* In init state 'input = *input_p' and we need to increment
         * in order to avoid getting stalled. Else, input = *(input_p - 1),
         * so 'input_p' points already to the next character.                   */
        if( me->buffer._input_p == me->buffer._lexeme_start_p ) {
            /* Step over non-matching character */
            ++(me->buffer._input_p);
        }
    }
    __QUEX_COUNT_VOID(&self, LexemeBegin, LexemeEnd);
    {
#   line 123 "src/Parser/QuexParser.qx"
    QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
    self_send(TokenFailure);
    
#   line 13425 "QuexParser.cpp"

    }
    goto __REENTRY_PREPARATION_2;


/* TERMINAL: END_OF_STREAM */
_363:
__QUEX_IF_COUNT_SHIFT_VALUES();
    {
QUEX_NAME(on_indentation)(me, /*Indentation*/0, LexemeNull);
self_send(__QUEX_SETTING_TOKEN_ID_TERMINATION);
RETURN;

    }
    /* End of Stream causes a return from the lexical analyzer, so that no
     * tokens can be filled after the termination token.                    */
    RETURN;

__REENTRY_PREPARATION:
    /* (*) Common point for **restarting** lexical analysis.
     *     at each time when CONTINUE is called at the end of a pattern.     */
 

    /* FAILURE needs not to run through 'on_after_match'. It enters here.    */
__REENTRY_PREPARATION_2:

#   undef Lexeme
#   undef LexemeBegin
#   undef LexemeEnd
#   undef LexemeNull
#   undef LexemeL

#   ifndef __QUEX_OPTION_PLAIN_ANALYZER_OBJECT
#   ifdef  QUEX_OPTION_TOKEN_POLICY_QUEUE
    if( QUEX_NAME(TokenQueue_is_full)(&self._token_queue) ) {
        return;
    }
#   else
    if( self_token_get_id() != __QUEX_SETTING_TOKEN_ID_UNINITIALIZED) {
        return __self_result_token_id;
    }
#   endif
#   endif


    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. Post context position's live cycle:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, then it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context), then the post context position is used
     *       to reset the input position.                                              */

    /*  If a mode change happened, then the function must first return and
     *  indicate that another mode function is to be called. At this point, 
     *  we to force a 'return' on a mode change. 
     *
     *  Pseudo Code: if( previous_mode != current_mode ) {
     *                   return 0;
     *               }
     *
     *  When the analyzer returns, the caller function has to watch if a mode 
     *  change occurred. If not it can call this function again.             */
#   if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)        || defined(QUEX_OPTION_ASSERTS)
    if( me->DEBUG_analyzer_function_at_entry != me->current_analyzer_function ) 
#   endif
    { 
#       if defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)
        self_token_set_id(__QUEX_SETTING_TOKEN_ID_UNINITIALIZED);
        __QUEX_PURE_RETURN;
#       elif defined(QUEX_OPTION_ASSERTS)
        QUEX_ERROR_EXIT("Mode change without immediate return from the lexical analyzer.");
#       endif
    }

    goto __REENTRY;

    __quex_assert_no_passage();
__RELOAD_FORWARD:

    __quex_debug1("__RELOAD_FORWARD");
    __quex_assert(*(me->buffer._input_p) == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( me->buffer._memory._end_of_file_p == 0x0 ) {

        __quex_debug_reload_before(); /* Leave macro here to report source position. */
        QUEX_NAME(buffer_reload_forward)(&me->buffer, (QUEX_TYPE_CHARACTER_POSITION*)position, PositionRegisterN);

        __quex_debug_reload_after();
        QUEX_GOTO_STATE(target_state_index);
    }
    __quex_debug("reload impossible\n");
    QUEX_GOTO_STATE(target_state_else_index);
#   ifndef QUEX_OPTION_COMPUTED_GOTOS
    __quex_assert_no_passage();
__STATE_ROUTER:
    switch( target_state_index ) {
        case 363: { goto _363; }
        case 529: { goto _529; }
        case 530: { goto _530; }
        case 531: { goto _531; }
        case 532: { goto _532; }
        case 535: { goto _535; }

        default:
            __QUEX_STD_fprintf(stderr, "State router: index = %i\n", (int)target_state_index);
            QUEX_ERROR_EXIT("State router: unknown index.\n");
    }
#   endif /* QUEX_OPTION_COMPUTED_GOTOS */

    /* Prevent compiler warning 'unused variable': use variables once in a part of the code*/
    /* that is never reached (and deleted by the compiler anyway).*/
    (void)QUEX_LEXEME_NULL;
    (void)QUEX_NAME_TOKEN(DumpedTokenIdObject);
    QUEX_ERROR_EXIT("Unreachable code has been reached.\n");
#   undef Program
#   undef Quotation
#   undef self
}
#include <quex/code_base/temporary_macros_off>
    /* BEGIN: MODE PATTERNS
     * 
     * MODE: Program
     * 
     *     PATTERN-ACTION PAIRS:
     *       ON_END_OF_STREAM
     *       ON_FAILURE
     *       (343) Program: {Newline}
     *       (344) Program: {Whitespace}
     *       (345) Program: {Call}
     *       (346) Program: {Closure}
     *       (347) Program: {Because}
     *       (348) Program: {Axiom}
     *       (349) Program: {Proofs}
     *       (350) Program: {Therefore}
     *       (351) Program: {BracketOpen}
     *       (352) Program: {BracketClose}
     *       (353) Program: {BracketValue}
     *       (354) Program: {Identifier}
     *       (355) Program: {Number}
     *       (356) Program: {QuoteOpen}
     *       (357) Program: {QuoteClose}
     *       (358) Program: {Syntax}
     * 
     * 
     * MODE: Quotation
     * 
     *     PATTERN-ACTION PAIRS:
     *       ON_END_OF_STREAM
     *       ON_FAILURE
     *       (359) Quotation: {QuoteOpen}
     *       (360) Quotation: {QuoteClose}
     *       (361) Quotation: [:inverse({QuoteOpen},{QuoteClose}):]+
     * 
     * 
     * END: MODE PATTERNS
     */
QUEX_NAMESPACE_MAIN_CLOSE


QUEX_NAMESPACE_TOKEN_OPEN

const char*
QUEX_NAME_TOKEN(map_id_to_name)(const QUEX_TYPE_TOKEN_ID TokenID)
{
   static char  error_string[64];
   static const char  uninitialized_string[] = "<UNINITIALIZED>";
   static const char  termination_string[]   = "<TERMINATION>";
#  if defined(QUEX_OPTION_INDENTATION_TRIGGER)
   static const char  indent_string[]        = "<INDENT>";
   static const char  dedent_string[]        = "<DEDENT>";
   static const char  nodent_string[]        = "<NODENT>";
#  endif
   static const char  token_id_str_Axiom[]              = "Axiom";
   static const char  token_id_str_Because[]            = "Because";
   static const char  token_id_str_BlockBegin[]         = "BlockBegin";
   static const char  token_id_str_BlockEnd[]           = "BlockEnd";
   static const char  token_id_str_BracketClose[]       = "BracketClose";
   static const char  token_id_str_BracketOpen[]        = "BracketOpen";
   static const char  token_id_str_BracketValue[]       = "BracketValue";
   static const char  token_id_str_Call[]               = "Call";
   static const char  token_id_str_Closure[]            = "Closure";
   static const char  token_id_str_EndOfStream[]        = "EndOfStream";
   static const char  token_id_str_Failure[]            = "Failure";
   static const char  token_id_str_Identifier[]         = "Identifier";
   static const char  token_id_str_Number[]             = "Number";
   static const char  token_id_str_Proofs[]             = "Proofs";
   static const char  token_id_str_Quotation[]          = "Quotation";
   static const char  token_id_str_StatementSeparator[] = "StatementSeparator";
   static const char  token_id_str_Therefore[]          = "Therefore";
       

   /* NOTE: This implementation works only for token id types that are 
    *       some type of integer or enum. In case an alien type is to
    *       used, this function needs to be redefined.                  */
   switch( TokenID ) {
   default: {
       __QUEX_STD_sprintf(error_string, "<UNKNOWN TOKEN-ID: %i>", (int)TokenID);
       return error_string;
   }
   case TokenTERMINATION:    return termination_string;
   case TokenUNINITIALIZED:  return uninitialized_string;
#  if defined(QUEX_OPTION_INDENTATION_TRIGGER)
   case TokenINDENT:         return indent_string;
   case TokenDEDENT:         return dedent_string;
   case TokenNODENT:         return nodent_string;
#  endif
   case TokenAxiom:              return token_id_str_Axiom;
   case TokenBecause:            return token_id_str_Because;
   case TokenBlockBegin:         return token_id_str_BlockBegin;
   case TokenBlockEnd:           return token_id_str_BlockEnd;
   case TokenBracketClose:       return token_id_str_BracketClose;
   case TokenBracketOpen:        return token_id_str_BracketOpen;
   case TokenBracketValue:       return token_id_str_BracketValue;
   case TokenCall:               return token_id_str_Call;
   case TokenClosure:            return token_id_str_Closure;
   case TokenEndOfStream:        return token_id_str_EndOfStream;
   case TokenFailure:            return token_id_str_Failure;
   case TokenIdentifier:         return token_id_str_Identifier;
   case TokenNumber:             return token_id_str_Number;
   case TokenProofs:             return token_id_str_Proofs;
   case TokenQuotation:          return token_id_str_Quotation;
   case TokenStatementSeparator: return token_id_str_StatementSeparator;
   case TokenTherefore:          return token_id_str_Therefore;

   }
}

QUEX_NAMESPACE_TOKEN_CLOSE

