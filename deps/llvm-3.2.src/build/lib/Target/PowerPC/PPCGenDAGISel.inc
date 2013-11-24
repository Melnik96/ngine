/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* DAG Instruction Selector for the PPC target                                *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

// *** NOTE: This file is #included into the middle of the target
// *** instruction selector class.  These functions are really methods.

// The main instruction selector code.
SDNode *SelectCode(SDNode *N) {
  // Some target values are emitted as 2 bytes, TARGET_VAL handles
  // this.
  #define TARGET_VAL(X) X & 255, unsigned(X) >> 8
  static const unsigned char MatcherTable[] = {
/*0*/     OPC_SwitchOpcode /*105 cases */, 33,  TARGET_VAL(ISD::PREFETCH),// ->37
/*4*/       OPC_RecordMemRef,
/*5*/       OPC_RecordNode,   // #0 = 'prefetch' chained node
/*6*/       OPC_RecordChild1, // #1 = $dst
/*7*/       OPC_MoveChild, 2,
/*9*/       OPC_CheckInteger, 0, 
/*11*/      OPC_CheckType, MVT::i32,
/*13*/      OPC_MoveParent,
/*14*/      OPC_MoveChild, 3,
/*16*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*19*/      OPC_MoveParent,
/*20*/      OPC_MoveChild, 4,
/*22*/      OPC_CheckInteger, 1, 
/*24*/      OPC_MoveParent,
/*25*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$dst #2 #3
/*28*/      OPC_EmitMergeInputChains1_0,
/*29*/      OPC_MorphNodeTo, TARGET_VAL(PPC::DCBT), 0|OPFL_Chain|OPFL_MemRefs,
                0/*#VTs*/, 2/*#Ops*/, 2, 3, 
            // Src: (prefetch xoaddr:iPTR:$dst, 0:i32, (imm:i32), 1:i32) - Complexity = 25
            // Dst: (DCBT xoaddr:iPTR:$dst)
          /*SwitchOpcode*/ 40,  TARGET_VAL(ISD::MEMBARRIER),// ->80
/*40*/      OPC_RecordNode,   // #0 = 'membarrier' chained node
/*41*/      OPC_MoveChild, 1,
/*43*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*46*/      OPC_CheckType, MVT::i32,
/*48*/      OPC_MoveParent,
/*49*/      OPC_MoveChild, 2,
/*51*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*54*/      OPC_MoveParent,
/*55*/      OPC_MoveChild, 3,
/*57*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*60*/      OPC_MoveParent,
/*61*/      OPC_MoveChild, 4,
/*63*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*66*/      OPC_MoveParent,
/*67*/      OPC_MoveChild, 5,
/*69*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*72*/      OPC_MoveParent,
/*73*/      OPC_EmitMergeInputChains1_0,
/*74*/      OPC_MorphNodeTo, TARGET_VAL(PPC::SYNC), 0|OPFL_Chain,
                0/*#VTs*/, 0/*#Ops*/, 
            // Src: (membarrier (imm:i32), (imm:i32), (imm:i32), (imm:i32), (imm:i32)) - Complexity = 18
            // Dst: (SYNC)
          /*SwitchOpcode*/ 73|128,4/*585*/,  TARGET_VAL(ISD::INTRINSIC_VOID),// ->669
/*84*/      OPC_RecordNode,   // #0 = 'intrinsic_void' chained node
/*85*/      OPC_MoveChild, 1,
/*87*/      OPC_Scope, 17, /*->106*/ // 21 children in Scope
/*89*/        OPC_CheckInteger, 65|128,12/*1601*/, 
/*92*/        OPC_MoveParent,
/*93*/        OPC_RecordChild2, // #1 = $dst
/*94*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$dst #2 #3
/*97*/        OPC_EmitMergeInputChains1_0,
/*98*/        OPC_MorphNodeTo, TARGET_VAL(PPC::DCBA), 0|OPFL_Chain,
                  0/*#VTs*/, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_void 1601:iPTR, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (DCBA xoaddr:iPTR:$dst)
/*106*/     /*Scope*/ 17, /*->124*/
/*107*/       OPC_CheckInteger, 66|128,12/*1602*/, 
/*110*/       OPC_MoveParent,
/*111*/       OPC_RecordChild2, // #1 = $dst
/*112*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$dst #2 #3
/*115*/       OPC_EmitMergeInputChains1_0,
/*116*/       OPC_MorphNodeTo, TARGET_VAL(PPC::DCBF), 0|OPFL_Chain,
                  0/*#VTs*/, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_void 1602:iPTR, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (DCBF xoaddr:iPTR:$dst)
/*124*/     /*Scope*/ 17, /*->142*/
/*125*/       OPC_CheckInteger, 67|128,12/*1603*/, 
/*128*/       OPC_MoveParent,
/*129*/       OPC_RecordChild2, // #1 = $dst
/*130*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$dst #2 #3
/*133*/       OPC_EmitMergeInputChains1_0,
/*134*/       OPC_MorphNodeTo, TARGET_VAL(PPC::DCBI), 0|OPFL_Chain,
                  0/*#VTs*/, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_void 1603:iPTR, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (DCBI xoaddr:iPTR:$dst)
/*142*/     /*Scope*/ 17, /*->160*/
/*143*/       OPC_CheckInteger, 68|128,12/*1604*/, 
/*146*/       OPC_MoveParent,
/*147*/       OPC_RecordChild2, // #1 = $dst
/*148*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$dst #2 #3
/*151*/       OPC_EmitMergeInputChains1_0,
/*152*/       OPC_MorphNodeTo, TARGET_VAL(PPC::DCBST), 0|OPFL_Chain,
                  0/*#VTs*/, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_void 1604:iPTR, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (DCBST xoaddr:iPTR:$dst)
/*160*/     /*Scope*/ 17, /*->178*/
/*161*/       OPC_CheckInteger, 69|128,12/*1605*/, 
/*164*/       OPC_MoveParent,
/*165*/       OPC_RecordChild2, // #1 = $dst
/*166*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$dst #2 #3
/*169*/       OPC_EmitMergeInputChains1_0,
/*170*/       OPC_MorphNodeTo, TARGET_VAL(PPC::DCBT), 0|OPFL_Chain,
                  0/*#VTs*/, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_void 1605:iPTR, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (DCBT xoaddr:iPTR:$dst)
/*178*/     /*Scope*/ 17, /*->196*/
/*179*/       OPC_CheckInteger, 70|128,12/*1606*/, 
/*182*/       OPC_MoveParent,
/*183*/       OPC_RecordChild2, // #1 = $dst
/*184*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$dst #2 #3
/*187*/       OPC_EmitMergeInputChains1_0,
/*188*/       OPC_MorphNodeTo, TARGET_VAL(PPC::DCBTST), 0|OPFL_Chain,
                  0/*#VTs*/, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_void 1606:iPTR, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (DCBTST xoaddr:iPTR:$dst)
/*196*/     /*Scope*/ 17, /*->214*/
/*197*/       OPC_CheckInteger, 71|128,12/*1607*/, 
/*200*/       OPC_MoveParent,
/*201*/       OPC_RecordChild2, // #1 = $dst
/*202*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$dst #2 #3
/*205*/       OPC_EmitMergeInputChains1_0,
/*206*/       OPC_MorphNodeTo, TARGET_VAL(PPC::DCBZ), 0|OPFL_Chain,
                  0/*#VTs*/, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_void 1607:iPTR, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (DCBZ xoaddr:iPTR:$dst)
/*214*/     /*Scope*/ 17, /*->232*/
/*215*/       OPC_CheckInteger, 72|128,12/*1608*/, 
/*218*/       OPC_MoveParent,
/*219*/       OPC_RecordChild2, // #1 = $dst
/*220*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$dst #2 #3
/*223*/       OPC_EmitMergeInputChains1_0,
/*224*/       OPC_MorphNodeTo, TARGET_VAL(PPC::DCBZL), 0|OPFL_Chain,
                  0/*#VTs*/, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_void 1608:iPTR, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (DCBZL xoaddr:iPTR:$dst)
/*232*/     /*Scope*/ 19, /*->252*/
/*233*/       OPC_CheckInteger, 61|128,11/*1469*/, 
/*236*/       OPC_MoveParent,
/*237*/       OPC_RecordChild2, // #1 = $rS
/*238*/       OPC_RecordChild3, // #2 = $dst
/*239*/       OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*242*/       OPC_EmitMergeInputChains1_0,
/*243*/       OPC_MorphNodeTo, TARGET_VAL(PPC::STVEBX), 0|OPFL_Chain,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (intrinsic_void 1469:iPTR, VRRC:v16i8:$rS, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (STVEBX VRRC:v16i8:$rS, xoaddr:iPTR:$dst)
/*252*/     /*Scope*/ 19, /*->272*/
/*253*/       OPC_CheckInteger, 62|128,11/*1470*/, 
/*256*/       OPC_MoveParent,
/*257*/       OPC_RecordChild2, // #1 = $rS
/*258*/       OPC_RecordChild3, // #2 = $dst
/*259*/       OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*262*/       OPC_EmitMergeInputChains1_0,
/*263*/       OPC_MorphNodeTo, TARGET_VAL(PPC::STVEHX), 0|OPFL_Chain,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (intrinsic_void 1470:iPTR, VRRC:v8i16:$rS, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (STVEHX VRRC:v8i16:$rS, xoaddr:iPTR:$dst)
/*272*/     /*Scope*/ 19, /*->292*/
/*273*/       OPC_CheckInteger, 63|128,11/*1471*/, 
/*276*/       OPC_MoveParent,
/*277*/       OPC_RecordChild2, // #1 = $rS
/*278*/       OPC_RecordChild3, // #2 = $dst
/*279*/       OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*282*/       OPC_EmitMergeInputChains1_0,
/*283*/       OPC_MorphNodeTo, TARGET_VAL(PPC::STVEWX), 0|OPFL_Chain,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (intrinsic_void 1471:iPTR, VRRC:v4i32:$rS, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (STVEWX VRRC:v4i32:$rS, xoaddr:iPTR:$dst)
/*292*/     /*Scope*/ 19, /*->312*/
/*293*/       OPC_CheckInteger, 64|128,11/*1472*/, 
/*296*/       OPC_MoveParent,
/*297*/       OPC_RecordChild2, // #1 = $rS
/*298*/       OPC_RecordChild3, // #2 = $dst
/*299*/       OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*302*/       OPC_EmitMergeInputChains1_0,
/*303*/       OPC_MorphNodeTo, TARGET_VAL(PPC::STVX), 0|OPFL_Chain,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (intrinsic_void 1472:iPTR, VRRC:v4i32:$rS, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (STVX VRRC:v4i32:$rS, xoaddr:iPTR:$dst)
/*312*/     /*Scope*/ 19, /*->332*/
/*313*/       OPC_CheckInteger, 65|128,11/*1473*/, 
/*316*/       OPC_MoveParent,
/*317*/       OPC_RecordChild2, // #1 = $rS
/*318*/       OPC_RecordChild3, // #2 = $dst
/*319*/       OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*322*/       OPC_EmitMergeInputChains1_0,
/*323*/       OPC_MorphNodeTo, TARGET_VAL(PPC::STVXL), 0|OPFL_Chain,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (intrinsic_void 1473:iPTR, VRRC:v4i32:$rS, xoaddr:iPTR:$dst) - Complexity = 17
              // Dst: (STVXL VRRC:v4i32:$rS, xoaddr:iPTR:$dst)
/*332*/     /*Scope*/ 33, /*->366*/
/*333*/       OPC_CheckInteger, 46|128,11/*1454*/, 
/*336*/       OPC_MoveParent,
/*337*/       OPC_RecordChild2, // #1 = $STRM
/*338*/       OPC_MoveChild, 2,
/*340*/       OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*343*/       OPC_MoveParent,
/*344*/       OPC_EmitMergeInputChains1_0,
/*345*/       OPC_EmitInteger, MVT::i32, 0, 
/*348*/       OPC_EmitConvertToTarget, 1,
/*350*/       OPC_EmitInteger, MVT::i32, 0, 
/*353*/       OPC_EmitInteger, MVT::i32, 0, 
/*356*/       OPC_MorphNodeTo, TARGET_VAL(PPC::DSS), 0|OPFL_Chain,
                  0/*#VTs*/, 4/*#Ops*/, 2, 3, 4, 5, 
              // Src: (intrinsic_void 1454:iPTR, (imm:i32):$STRM) - Complexity = 11
              // Dst: (DSS 0:i32, (imm:i32):$STRM, 0:i32, 0:i32)
/*366*/     /*Scope*/ 61, /*->428*/
/*367*/       OPC_CheckInteger, 48|128,11/*1456*/, 
/*370*/       OPC_MoveParent,
/*371*/       OPC_RecordChild2, // #1 = $rA
/*372*/       OPC_Scope, 26, /*->400*/ // 2 children in Scope
/*374*/         OPC_CheckChild2Type, MVT::i32,
/*376*/         OPC_RecordChild3, // #2 = $rB
/*377*/         OPC_RecordChild4, // #3 = $STRM
/*378*/         OPC_MoveChild, 4,
/*380*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*383*/         OPC_MoveParent,
/*384*/         OPC_EmitMergeInputChains1_0,
/*385*/         OPC_EmitInteger, MVT::i32, 0, 
/*388*/         OPC_EmitConvertToTarget, 3,
/*390*/         OPC_MorphNodeTo, TARGET_VAL(PPC::DST), 0|OPFL_Chain,
                    0/*#VTs*/, 4/*#Ops*/, 4, 5, 1, 2, 
                // Src: (intrinsic_void 1456:iPTR, GPRC:i32:$rA, GPRC:i32:$rB, (imm:i32):$STRM) - Complexity = 11
                // Dst: (DST 0:i32, (imm:i32):$STRM, GPRC:i32:$rA, GPRC:i32:$rB)
/*400*/       /*Scope*/ 26, /*->427*/
/*401*/         OPC_CheckChild2Type, MVT::i64,
/*403*/         OPC_RecordChild3, // #2 = $rB
/*404*/         OPC_RecordChild4, // #3 = $STRM
/*405*/         OPC_MoveChild, 4,
/*407*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*410*/         OPC_MoveParent,
/*411*/         OPC_EmitMergeInputChains1_0,
/*412*/         OPC_EmitInteger, MVT::i32, 0, 
/*415*/         OPC_EmitConvertToTarget, 3,
/*417*/         OPC_MorphNodeTo, TARGET_VAL(PPC::DST64), 0|OPFL_Chain,
                    0/*#VTs*/, 4/*#Ops*/, 4, 5, 1, 2, 
                // Src: (intrinsic_void 1456:iPTR, G8RC:i64:$rA, GPRC:i32:$rB, (imm:i32):$STRM) - Complexity = 11
                // Dst: (DST64 0:i32, (imm:i32):$STRM, G8RC:i64:$rA, GPRC:i32:$rB)
/*427*/       0, /*End of Scope*/
/*428*/     /*Scope*/ 61, /*->490*/
/*429*/       OPC_CheckInteger, 51|128,11/*1459*/, 
/*432*/       OPC_MoveParent,
/*433*/       OPC_RecordChild2, // #1 = $rA
/*434*/       OPC_Scope, 26, /*->462*/ // 2 children in Scope
/*436*/         OPC_CheckChild2Type, MVT::i32,
/*438*/         OPC_RecordChild3, // #2 = $rB
/*439*/         OPC_RecordChild4, // #3 = $STRM
/*440*/         OPC_MoveChild, 4,
/*442*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*445*/         OPC_MoveParent,
/*446*/         OPC_EmitMergeInputChains1_0,
/*447*/         OPC_EmitInteger, MVT::i32, 1, 
/*450*/         OPC_EmitConvertToTarget, 3,
/*452*/         OPC_MorphNodeTo, TARGET_VAL(PPC::DSTT), 0|OPFL_Chain,
                    0/*#VTs*/, 4/*#Ops*/, 4, 5, 1, 2, 
                // Src: (intrinsic_void 1459:iPTR, GPRC:i32:$rA, GPRC:i32:$rB, (imm:i32):$STRM) - Complexity = 11
                // Dst: (DSTT 1:i32, (imm:i32):$STRM, GPRC:i32:$rA, GPRC:i32:$rB)
/*462*/       /*Scope*/ 26, /*->489*/
/*463*/         OPC_CheckChild2Type, MVT::i64,
/*465*/         OPC_RecordChild3, // #2 = $rB
/*466*/         OPC_RecordChild4, // #3 = $STRM
/*467*/         OPC_MoveChild, 4,
/*469*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*472*/         OPC_MoveParent,
/*473*/         OPC_EmitMergeInputChains1_0,
/*474*/         OPC_EmitInteger, MVT::i32, 1, 
/*477*/         OPC_EmitConvertToTarget, 3,
/*479*/         OPC_MorphNodeTo, TARGET_VAL(PPC::DSTT64), 0|OPFL_Chain,
                    0/*#VTs*/, 4/*#Ops*/, 4, 5, 1, 2, 
                // Src: (intrinsic_void 1459:iPTR, G8RC:i64:$rA, GPRC:i32:$rB, (imm:i32):$STRM) - Complexity = 11
                // Dst: (DSTT64 1:i32, (imm:i32):$STRM, G8RC:i64:$rA, GPRC:i32:$rB)
/*489*/       0, /*End of Scope*/
/*490*/     /*Scope*/ 61, /*->552*/
/*491*/       OPC_CheckInteger, 49|128,11/*1457*/, 
/*494*/       OPC_MoveParent,
/*495*/       OPC_RecordChild2, // #1 = $rA
/*496*/       OPC_Scope, 26, /*->524*/ // 2 children in Scope
/*498*/         OPC_CheckChild2Type, MVT::i32,
/*500*/         OPC_RecordChild3, // #2 = $rB
/*501*/         OPC_RecordChild4, // #3 = $STRM
/*502*/         OPC_MoveChild, 4,
/*504*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*507*/         OPC_MoveParent,
/*508*/         OPC_EmitMergeInputChains1_0,
/*509*/         OPC_EmitInteger, MVT::i32, 0, 
/*512*/         OPC_EmitConvertToTarget, 3,
/*514*/         OPC_MorphNodeTo, TARGET_VAL(PPC::DSTST), 0|OPFL_Chain,
                    0/*#VTs*/, 4/*#Ops*/, 4, 5, 1, 2, 
                // Src: (intrinsic_void 1457:iPTR, GPRC:i32:$rA, GPRC:i32:$rB, (imm:i32):$STRM) - Complexity = 11
                // Dst: (DSTST 0:i32, (imm:i32):$STRM, GPRC:i32:$rA, GPRC:i32:$rB)
/*524*/       /*Scope*/ 26, /*->551*/
/*525*/         OPC_CheckChild2Type, MVT::i64,
/*527*/         OPC_RecordChild3, // #2 = $rB
/*528*/         OPC_RecordChild4, // #3 = $STRM
/*529*/         OPC_MoveChild, 4,
/*531*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*534*/         OPC_MoveParent,
/*535*/         OPC_EmitMergeInputChains1_0,
/*536*/         OPC_EmitInteger, MVT::i32, 0, 
/*539*/         OPC_EmitConvertToTarget, 3,
/*541*/         OPC_MorphNodeTo, TARGET_VAL(PPC::DSTST64), 0|OPFL_Chain,
                    0/*#VTs*/, 4/*#Ops*/, 4, 5, 1, 2, 
                // Src: (intrinsic_void 1457:iPTR, G8RC:i64:$rA, GPRC:i32:$rB, (imm:i32):$STRM) - Complexity = 11
                // Dst: (DSTST64 0:i32, (imm:i32):$STRM, G8RC:i64:$rA, GPRC:i32:$rB)
/*551*/       0, /*End of Scope*/
/*552*/     /*Scope*/ 61, /*->614*/
/*553*/       OPC_CheckInteger, 50|128,11/*1458*/, 
/*556*/       OPC_MoveParent,
/*557*/       OPC_RecordChild2, // #1 = $rA
/*558*/       OPC_Scope, 26, /*->586*/ // 2 children in Scope
/*560*/         OPC_CheckChild2Type, MVT::i32,
/*562*/         OPC_RecordChild3, // #2 = $rB
/*563*/         OPC_RecordChild4, // #3 = $STRM
/*564*/         OPC_MoveChild, 4,
/*566*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*569*/         OPC_MoveParent,
/*570*/         OPC_EmitMergeInputChains1_0,
/*571*/         OPC_EmitInteger, MVT::i32, 1, 
/*574*/         OPC_EmitConvertToTarget, 3,
/*576*/         OPC_MorphNodeTo, TARGET_VAL(PPC::DSTSTT), 0|OPFL_Chain,
                    0/*#VTs*/, 4/*#Ops*/, 4, 5, 1, 2, 
                // Src: (intrinsic_void 1458:iPTR, GPRC:i32:$rA, GPRC:i32:$rB, (imm:i32):$STRM) - Complexity = 11
                // Dst: (DSTSTT 1:i32, (imm:i32):$STRM, GPRC:i32:$rA, GPRC:i32:$rB)
/*586*/       /*Scope*/ 26, /*->613*/
/*587*/         OPC_CheckChild2Type, MVT::i64,
/*589*/         OPC_RecordChild3, // #2 = $rB
/*590*/         OPC_RecordChild4, // #3 = $STRM
/*591*/         OPC_MoveChild, 4,
/*593*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*596*/         OPC_MoveParent,
/*597*/         OPC_EmitMergeInputChains1_0,
/*598*/         OPC_EmitInteger, MVT::i32, 1, 
/*601*/         OPC_EmitConvertToTarget, 3,
/*603*/         OPC_MorphNodeTo, TARGET_VAL(PPC::DSTSTT64), 0|OPFL_Chain,
                    0/*#VTs*/, 4/*#Ops*/, 4, 5, 1, 2, 
                // Src: (intrinsic_void 1458:iPTR, G8RC:i64:$rA, GPRC:i32:$rB, (imm:i32):$STRM) - Complexity = 11
                // Dst: (DSTSTT64 1:i32, (imm:i32):$STRM, G8RC:i64:$rA, GPRC:i32:$rB)
/*613*/       0, /*End of Scope*/
/*614*/     /*Scope*/ 11, /*->626*/
/*615*/       OPC_CheckInteger, 73|128,12/*1609*/, 
/*618*/       OPC_MoveParent,
/*619*/       OPC_EmitMergeInputChains1_0,
/*620*/       OPC_MorphNodeTo, TARGET_VAL(PPC::SYNC), 0|OPFL_Chain,
                  0/*#VTs*/, 0/*#Ops*/, 
              // Src: (intrinsic_void 1609:iPTR) - Complexity = 8
              // Dst: (SYNC)
/*626*/     /*Scope*/ 13, /*->640*/
/*627*/       OPC_CheckInteger, 60|128,11/*1468*/, 
/*630*/       OPC_MoveParent,
/*631*/       OPC_RecordChild2, // #1 = $vB
/*632*/       OPC_EmitMergeInputChains1_0,
/*633*/       OPC_MorphNodeTo, TARGET_VAL(PPC::MTVSCR), 0|OPFL_Chain,
                  0/*#VTs*/, 1/*#Ops*/, 1, 
              // Src: (intrinsic_void 1468:iPTR, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (MTVSCR VRRC:v4i32:$vB)
/*640*/     /*Scope*/ 27, /*->668*/
/*641*/       OPC_CheckInteger, 47|128,11/*1455*/, 
/*644*/       OPC_MoveParent,
/*645*/       OPC_EmitMergeInputChains1_0,
/*646*/       OPC_EmitInteger, MVT::i32, 1, 
/*649*/       OPC_EmitInteger, MVT::i32, 0, 
/*652*/       OPC_EmitInteger, MVT::i32, 0, 
/*655*/       OPC_EmitInteger, MVT::i32, 0, 
/*658*/       OPC_MorphNodeTo, TARGET_VAL(PPC::DSSALL), 0|OPFL_Chain,
                  0/*#VTs*/, 4/*#Ops*/, 1, 2, 3, 4, 
              // Src: (intrinsic_void 1455:iPTR) - Complexity = 8
              // Dst: (DSSALL 1:i32, 0:i32, 0:i32, 0:i32)
/*668*/     0, /*End of Scope*/
          /*SwitchOpcode*/ 113,  TARGET_VAL(ISD::INTRINSIC_W_CHAIN),// ->785
/*672*/     OPC_RecordNode,   // #0 = 'intrinsic_w_chain' chained node
/*673*/     OPC_MoveChild, 1,
/*675*/     OPC_Scope, 18, /*->695*/ // 6 children in Scope
/*677*/       OPC_CheckInteger, 52|128,11/*1460*/, 
/*680*/       OPC_MoveParent,
/*681*/       OPC_RecordChild2, // #1 = $src
/*682*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$src #2 #3
/*685*/       OPC_EmitMergeInputChains1_0,
/*686*/       OPC_MorphNodeTo, TARGET_VAL(PPC::LVEBX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_w_chain:v16i8 1460:iPTR, xoaddr:iPTR:$src) - Complexity = 17
              // Dst: (LVEBX:v16i8 xoaddr:iPTR:$src)
/*695*/     /*Scope*/ 18, /*->714*/
/*696*/       OPC_CheckInteger, 53|128,11/*1461*/, 
/*699*/       OPC_MoveParent,
/*700*/       OPC_RecordChild2, // #1 = $src
/*701*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$src #2 #3
/*704*/       OPC_EmitMergeInputChains1_0,
/*705*/       OPC_MorphNodeTo, TARGET_VAL(PPC::LVEHX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_w_chain:v8i16 1461:iPTR, xoaddr:iPTR:$src) - Complexity = 17
              // Dst: (LVEHX:v8i16 xoaddr:iPTR:$src)
/*714*/     /*Scope*/ 18, /*->733*/
/*715*/       OPC_CheckInteger, 54|128,11/*1462*/, 
/*718*/       OPC_MoveParent,
/*719*/       OPC_RecordChild2, // #1 = $src
/*720*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$src #2 #3
/*723*/       OPC_EmitMergeInputChains1_0,
/*724*/       OPC_MorphNodeTo, TARGET_VAL(PPC::LVEWX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_w_chain:v4i32 1462:iPTR, xoaddr:iPTR:$src) - Complexity = 17
              // Dst: (LVEWX:v4i32 xoaddr:iPTR:$src)
/*733*/     /*Scope*/ 18, /*->752*/
/*734*/       OPC_CheckInteger, 57|128,11/*1465*/, 
/*737*/       OPC_MoveParent,
/*738*/       OPC_RecordChild2, // #1 = $src
/*739*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$src #2 #3
/*742*/       OPC_EmitMergeInputChains1_0,
/*743*/       OPC_MorphNodeTo, TARGET_VAL(PPC::LVX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_w_chain:v4i32 1465:iPTR, xoaddr:iPTR:$src) - Complexity = 17
              // Dst: (LVX:v4i32 xoaddr:iPTR:$src)
/*752*/     /*Scope*/ 18, /*->771*/
/*753*/       OPC_CheckInteger, 58|128,11/*1466*/, 
/*756*/       OPC_MoveParent,
/*757*/       OPC_RecordChild2, // #1 = $src
/*758*/       OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$src #2 #3
/*761*/       OPC_EmitMergeInputChains1_0,
/*762*/       OPC_MorphNodeTo, TARGET_VAL(PPC::LVXL), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 2, 3, 
              // Src: (intrinsic_w_chain:v4i32 1466:iPTR, xoaddr:iPTR:$src) - Complexity = 17
              // Dst: (LVXL:v4i32 xoaddr:iPTR:$src)
/*771*/     /*Scope*/ 12, /*->784*/
/*772*/       OPC_CheckInteger, 59|128,11/*1467*/, 
/*775*/       OPC_MoveParent,
/*776*/       OPC_EmitMergeInputChains1_0,
/*777*/       OPC_MorphNodeTo, TARGET_VAL(PPC::MFVSCR), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::v8i16, 0/*#Ops*/, 
              // Src: (intrinsic_w_chain:v8i16 1467:iPTR) - Complexity = 8
              // Dst: (MFVSCR:v8i16)
/*784*/     0, /*End of Scope*/
          /*SwitchOpcode*/ 90|128,13/*1754*/,  TARGET_VAL(ISD::INTRINSIC_WO_CHAIN),// ->2543
/*789*/     OPC_MoveChild, 0,
/*791*/     OPC_Scope, 17, /*->810*/ // 103 children in Scope
/*793*/       OPC_CheckInteger, 55|128,11/*1463*/, 
/*796*/       OPC_MoveParent,
/*797*/       OPC_RecordChild1, // #0 = $src
/*798*/       OPC_CheckComplexPat, /*CP*/0, /*#*/0, // SelectAddrIdxOnly:$src #1 #2
/*801*/       OPC_MorphNodeTo, TARGET_VAL(PPC::LVSL), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 1, 2, 
              // Src: (intrinsic_wo_chain:v16i8 1463:iPTR, xoaddr:iPTR:$src) - Complexity = 17
              // Dst: (LVSL:v16i8 xoaddr:iPTR:$src)
/*810*/     /*Scope*/ 17, /*->828*/
/*811*/       OPC_CheckInteger, 56|128,11/*1464*/, 
/*814*/       OPC_MoveParent,
/*815*/       OPC_RecordChild1, // #0 = $src
/*816*/       OPC_CheckComplexPat, /*CP*/0, /*#*/0, // SelectAddrIdxOnly:$src #1 #2
/*819*/       OPC_MorphNodeTo, TARGET_VAL(PPC::LVSR), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 1, 2, 
              // Src: (intrinsic_wo_chain:v16i8 1464:iPTR, xoaddr:iPTR:$src) - Complexity = 17
              // Dst: (LVSR:v16i8 xoaddr:iPTR:$src)
/*828*/     /*Scope*/ 40, /*->869*/
/*829*/       OPC_CheckInteger, 108|128,11/*1516*/, 
/*832*/       OPC_MoveParent,
/*833*/       OPC_RecordChild1, // #0 = $vB
/*834*/       OPC_Scope, 13, /*->849*/ // 2 children in Scope
/*836*/         OPC_MoveChild, 2,
/*838*/         OPC_CheckInteger, 0, 
/*840*/         OPC_MoveParent,
/*841*/         OPC_MorphNodeTo, TARGET_VAL(PPC::VCTUXS_0), 0,
                    1/*#VTs*/, MVT::v4i32, 1/*#Ops*/, 0, 
                // Src: (intrinsic_wo_chain:v4i32 1516:iPTR, VRRC:v4f32:$vB, 0:i32) - Complexity = 13
                // Dst: (VCTUXS_0:v4i32 VRRC:v4f32:$vB)
/*849*/       /*Scope*/ 18, /*->868*/
/*850*/         OPC_RecordChild2, // #1 = $UIMM
/*851*/         OPC_MoveChild, 2,
/*853*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*856*/         OPC_MoveParent,
/*857*/         OPC_EmitConvertToTarget, 1,
/*859*/         OPC_MorphNodeTo, TARGET_VAL(PPC::VCTUXS), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 2, 0, 
                // Src: (intrinsic_wo_chain:v4i32 1516:iPTR, VRRC:v4f32:$vB, (imm:i32):$UIMM) - Complexity = 11
                // Dst: (VCTUXS:v4i32 (imm:i32):$UIMM, VRRC:v4f32:$vB)
/*868*/       0, /*End of Scope*/
/*869*/     /*Scope*/ 40, /*->910*/
/*870*/       OPC_CheckInteger, 107|128,11/*1515*/, 
/*873*/       OPC_MoveParent,
/*874*/       OPC_RecordChild1, // #0 = $vB
/*875*/       OPC_Scope, 13, /*->890*/ // 2 children in Scope
/*877*/         OPC_MoveChild, 2,
/*879*/         OPC_CheckInteger, 0, 
/*881*/         OPC_MoveParent,
/*882*/         OPC_MorphNodeTo, TARGET_VAL(PPC::VCTSXS_0), 0,
                    1/*#VTs*/, MVT::v4i32, 1/*#Ops*/, 0, 
                // Src: (intrinsic_wo_chain:v4i32 1515:iPTR, VRRC:v4f32:$vB, 0:i32) - Complexity = 13
                // Dst: (VCTSXS_0:v4i32 VRRC:v4f32:$vB)
/*890*/       /*Scope*/ 18, /*->909*/
/*891*/         OPC_RecordChild2, // #1 = $UIMM
/*892*/         OPC_MoveChild, 2,
/*894*/         OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*897*/         OPC_MoveParent,
/*898*/         OPC_EmitConvertToTarget, 1,
/*900*/         OPC_MorphNodeTo, TARGET_VAL(PPC::VCTSXS), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 2, 0, 
                // Src: (intrinsic_wo_chain:v4i32 1515:iPTR, VRRC:v4f32:$vB, (imm:i32):$UIMM) - Complexity = 11
                // Dst: (VCTSXS:v4i32 (imm:i32):$UIMM, VRRC:v4f32:$vB)
/*909*/       0, /*End of Scope*/
/*910*/     /*Scope*/ 17, /*->928*/
/*911*/       OPC_CheckInteger, 119|128,11/*1527*/, 
/*914*/       OPC_MoveParent,
/*915*/       OPC_RecordChild1, // #0 = $vA
/*916*/       OPC_RecordChild2, // #1 = $vB
/*917*/       OPC_RecordChild3, // #2 = $vC
/*918*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMHADDSHS), 0,
                  1/*#VTs*/, MVT::v8i16, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v8i16 1527:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v8i16:$vC) - Complexity = 8
              // Dst: (VMHADDSHS:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v8i16:$vC)
/*928*/     /*Scope*/ 17, /*->946*/
/*929*/       OPC_CheckInteger, 120|128,11/*1528*/, 
/*932*/       OPC_MoveParent,
/*933*/       OPC_RecordChild1, // #0 = $vA
/*934*/       OPC_RecordChild2, // #1 = $vB
/*935*/       OPC_RecordChild3, // #2 = $vC
/*936*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMHRADDSHS), 0,
                  1/*#VTs*/, MVT::v8i16, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v8i16 1528:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v8i16:$vC) - Complexity = 8
              // Dst: (VMHRADDSHS:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v8i16:$vC)
/*946*/     /*Scope*/ 17, /*->964*/
/*947*/       OPC_CheckInteger, 0|128,12/*1536*/, 
/*950*/       OPC_MoveParent,
/*951*/       OPC_RecordChild1, // #0 = $vA
/*952*/       OPC_RecordChild2, // #1 = $vB
/*953*/       OPC_RecordChild3, // #2 = $vC
/*954*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMLADDUHM), 0,
                  1/*#VTs*/, MVT::v8i16, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v8i16 1536:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v8i16:$vC) - Complexity = 8
              // Dst: (VMLADDUHM:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v8i16:$vC)
/*964*/     /*Scope*/ 17, /*->982*/
/*965*/       OPC_CheckInteger, 16|128,12/*1552*/, 
/*968*/       OPC_MoveParent,
/*969*/       OPC_RecordChild1, // #0 = $vA
/*970*/       OPC_RecordChild2, // #1 = $vB
/*971*/       OPC_RecordChild3, // #2 = $vC
/*972*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VPERM), 0,
                  1/*#VTs*/, MVT::v4i32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4i32 1552:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB, VRRC:v16i8:$vC) - Complexity = 8
              // Dst: (VPERM:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB, VRRC:v16i8:$vC)
/*982*/     /*Scope*/ 17, /*->1000*/
/*983*/       OPC_CheckInteger, 33|128,12/*1569*/, 
/*986*/       OPC_MoveParent,
/*987*/       OPC_RecordChild1, // #0 = $vA
/*988*/       OPC_RecordChild2, // #1 = $vB
/*989*/       OPC_RecordChild3, // #2 = $vC
/*990*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VSEL), 0,
                  1/*#VTs*/, MVT::v4i32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4i32 1569:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB, VRRC:v4i32:$vC) - Complexity = 8
              // Dst: (VSEL:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB, VRRC:v4i32:$vC)
/*1000*/    /*Scope*/ 15, /*->1016*/
/*1001*/      OPC_CheckInteger, 66|128,11/*1474*/, 
/*1004*/      OPC_MoveParent,
/*1005*/      OPC_RecordChild1, // #0 = $vA
/*1006*/      OPC_RecordChild2, // #1 = $vB
/*1007*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VADDCUW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1474:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VADDCUW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1016*/    /*Scope*/ 15, /*->1032*/
/*1017*/      OPC_CheckInteger, 67|128,11/*1475*/, 
/*1020*/      OPC_MoveParent,
/*1021*/      OPC_RecordChild1, // #0 = $vA
/*1022*/      OPC_RecordChild2, // #1 = $vB
/*1023*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VADDSBS), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1475:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VADDSBS:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1032*/    /*Scope*/ 15, /*->1048*/
/*1033*/      OPC_CheckInteger, 68|128,11/*1476*/, 
/*1036*/      OPC_MoveParent,
/*1037*/      OPC_RecordChild1, // #0 = $vA
/*1038*/      OPC_RecordChild2, // #1 = $vB
/*1039*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VADDSHS), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1476:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VADDSHS:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1048*/    /*Scope*/ 15, /*->1064*/
/*1049*/      OPC_CheckInteger, 69|128,11/*1477*/, 
/*1052*/      OPC_MoveParent,
/*1053*/      OPC_RecordChild1, // #0 = $vA
/*1054*/      OPC_RecordChild2, // #1 = $vB
/*1055*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VADDSWS), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1477:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VADDSWS:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1064*/    /*Scope*/ 15, /*->1080*/
/*1065*/      OPC_CheckInteger, 70|128,11/*1478*/, 
/*1068*/      OPC_MoveParent,
/*1069*/      OPC_RecordChild1, // #0 = $vA
/*1070*/      OPC_RecordChild2, // #1 = $vB
/*1071*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VADDUBS), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1478:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VADDUBS:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1080*/    /*Scope*/ 15, /*->1096*/
/*1081*/      OPC_CheckInteger, 71|128,11/*1479*/, 
/*1084*/      OPC_MoveParent,
/*1085*/      OPC_RecordChild1, // #0 = $vA
/*1086*/      OPC_RecordChild2, // #1 = $vB
/*1087*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VADDUHS), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1479:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VADDUHS:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1096*/    /*Scope*/ 15, /*->1112*/
/*1097*/      OPC_CheckInteger, 72|128,11/*1480*/, 
/*1100*/      OPC_MoveParent,
/*1101*/      OPC_RecordChild1, // #0 = $vA
/*1102*/      OPC_RecordChild2, // #1 = $vB
/*1103*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VADDUWS), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1480:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VADDUWS:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1112*/    /*Scope*/ 15, /*->1128*/
/*1113*/      OPC_CheckInteger, 73|128,11/*1481*/, 
/*1116*/      OPC_MoveParent,
/*1117*/      OPC_RecordChild1, // #0 = $vA
/*1118*/      OPC_RecordChild2, // #1 = $vB
/*1119*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VAVGSB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1481:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VAVGSB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1128*/    /*Scope*/ 15, /*->1144*/
/*1129*/      OPC_CheckInteger, 74|128,11/*1482*/, 
/*1132*/      OPC_MoveParent,
/*1133*/      OPC_RecordChild1, // #0 = $vA
/*1134*/      OPC_RecordChild2, // #1 = $vB
/*1135*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VAVGSH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1482:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VAVGSH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1144*/    /*Scope*/ 15, /*->1160*/
/*1145*/      OPC_CheckInteger, 75|128,11/*1483*/, 
/*1148*/      OPC_MoveParent,
/*1149*/      OPC_RecordChild1, // #0 = $vA
/*1150*/      OPC_RecordChild2, // #1 = $vB
/*1151*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VAVGSW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1483:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VAVGSW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1160*/    /*Scope*/ 15, /*->1176*/
/*1161*/      OPC_CheckInteger, 76|128,11/*1484*/, 
/*1164*/      OPC_MoveParent,
/*1165*/      OPC_RecordChild1, // #0 = $vA
/*1166*/      OPC_RecordChild2, // #1 = $vB
/*1167*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VAVGUB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1484:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VAVGUB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1176*/    /*Scope*/ 15, /*->1192*/
/*1177*/      OPC_CheckInteger, 77|128,11/*1485*/, 
/*1180*/      OPC_MoveParent,
/*1181*/      OPC_RecordChild1, // #0 = $vA
/*1182*/      OPC_RecordChild2, // #1 = $vB
/*1183*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VAVGUH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1485:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VAVGUH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1192*/    /*Scope*/ 15, /*->1208*/
/*1193*/      OPC_CheckInteger, 78|128,11/*1486*/, 
/*1196*/      OPC_MoveParent,
/*1197*/      OPC_RecordChild1, // #0 = $vA
/*1198*/      OPC_RecordChild2, // #1 = $vB
/*1199*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VAVGUW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1486:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VAVGUW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1208*/    /*Scope*/ 15, /*->1224*/
/*1209*/      OPC_CheckInteger, 113|128,11/*1521*/, 
/*1212*/      OPC_MoveParent,
/*1213*/      OPC_RecordChild1, // #0 = $vA
/*1214*/      OPC_RecordChild2, // #1 = $vB
/*1215*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMAXSB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1521:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VMAXSB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1224*/    /*Scope*/ 15, /*->1240*/
/*1225*/      OPC_CheckInteger, 114|128,11/*1522*/, 
/*1228*/      OPC_MoveParent,
/*1229*/      OPC_RecordChild1, // #0 = $vA
/*1230*/      OPC_RecordChild2, // #1 = $vB
/*1231*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMAXSH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1522:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VMAXSH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1240*/    /*Scope*/ 15, /*->1256*/
/*1241*/      OPC_CheckInteger, 115|128,11/*1523*/, 
/*1244*/      OPC_MoveParent,
/*1245*/      OPC_RecordChild1, // #0 = $vA
/*1246*/      OPC_RecordChild2, // #1 = $vB
/*1247*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMAXSW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1523:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VMAXSW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1256*/    /*Scope*/ 15, /*->1272*/
/*1257*/      OPC_CheckInteger, 116|128,11/*1524*/, 
/*1260*/      OPC_MoveParent,
/*1261*/      OPC_RecordChild1, // #0 = $vA
/*1262*/      OPC_RecordChild2, // #1 = $vB
/*1263*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMAXUB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1524:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VMAXUB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1272*/    /*Scope*/ 15, /*->1288*/
/*1273*/      OPC_CheckInteger, 117|128,11/*1525*/, 
/*1276*/      OPC_MoveParent,
/*1277*/      OPC_RecordChild1, // #0 = $vA
/*1278*/      OPC_RecordChild2, // #1 = $vB
/*1279*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMAXUH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1525:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VMAXUH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1288*/    /*Scope*/ 15, /*->1304*/
/*1289*/      OPC_CheckInteger, 118|128,11/*1526*/, 
/*1292*/      OPC_MoveParent,
/*1293*/      OPC_RecordChild1, // #0 = $vA
/*1294*/      OPC_RecordChild2, // #1 = $vB
/*1295*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMAXUW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1526:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VMAXUW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1304*/    /*Scope*/ 15, /*->1320*/
/*1305*/      OPC_CheckInteger, 122|128,11/*1530*/, 
/*1308*/      OPC_MoveParent,
/*1309*/      OPC_RecordChild1, // #0 = $vA
/*1310*/      OPC_RecordChild2, // #1 = $vB
/*1311*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMINSB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1530:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VMINSB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1320*/    /*Scope*/ 15, /*->1336*/
/*1321*/      OPC_CheckInteger, 123|128,11/*1531*/, 
/*1324*/      OPC_MoveParent,
/*1325*/      OPC_RecordChild1, // #0 = $vA
/*1326*/      OPC_RecordChild2, // #1 = $vB
/*1327*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMINSH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1531:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VMINSH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1336*/    /*Scope*/ 15, /*->1352*/
/*1337*/      OPC_CheckInteger, 124|128,11/*1532*/, 
/*1340*/      OPC_MoveParent,
/*1341*/      OPC_RecordChild1, // #0 = $vA
/*1342*/      OPC_RecordChild2, // #1 = $vB
/*1343*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMINSW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1532:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VMINSW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1352*/    /*Scope*/ 15, /*->1368*/
/*1353*/      OPC_CheckInteger, 125|128,11/*1533*/, 
/*1356*/      OPC_MoveParent,
/*1357*/      OPC_RecordChild1, // #0 = $vA
/*1358*/      OPC_RecordChild2, // #1 = $vB
/*1359*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMINUB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1533:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VMINUB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1368*/    /*Scope*/ 15, /*->1384*/
/*1369*/      OPC_CheckInteger, 126|128,11/*1534*/, 
/*1372*/      OPC_MoveParent,
/*1373*/      OPC_RecordChild1, // #0 = $vA
/*1374*/      OPC_RecordChild2, // #1 = $vB
/*1375*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMINUH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1534:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VMINUH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1384*/    /*Scope*/ 15, /*->1400*/
/*1385*/      OPC_CheckInteger, 127|128,11/*1535*/, 
/*1388*/      OPC_MoveParent,
/*1389*/      OPC_RecordChild1, // #0 = $vA
/*1390*/      OPC_RecordChild2, // #1 = $vB
/*1391*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMINUW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1535:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VMINUW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1400*/    /*Scope*/ 17, /*->1418*/
/*1401*/      OPC_CheckInteger, 1|128,12/*1537*/, 
/*1404*/      OPC_MoveParent,
/*1405*/      OPC_RecordChild1, // #0 = $vA
/*1406*/      OPC_RecordChild2, // #1 = $vB
/*1407*/      OPC_RecordChild3, // #2 = $vC
/*1408*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMSUMMBM), 0,
                  1/*#VTs*/, MVT::v4i32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4i32 1537:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB, VRRC:v4i32:$vC) - Complexity = 8
              // Dst: (VMSUMMBM:v4i32 VRRC:v16i8:$vA, VRRC:v16i8:$vB, VRRC:v4i32:$vC)
/*1418*/    /*Scope*/ 17, /*->1436*/
/*1419*/      OPC_CheckInteger, 2|128,12/*1538*/, 
/*1422*/      OPC_MoveParent,
/*1423*/      OPC_RecordChild1, // #0 = $vA
/*1424*/      OPC_RecordChild2, // #1 = $vB
/*1425*/      OPC_RecordChild3, // #2 = $vC
/*1426*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMSUMSHM), 0,
                  1/*#VTs*/, MVT::v4i32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4i32 1538:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v4i32:$vC) - Complexity = 8
              // Dst: (VMSUMSHM:v4i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v4i32:$vC)
/*1436*/    /*Scope*/ 17, /*->1454*/
/*1437*/      OPC_CheckInteger, 3|128,12/*1539*/, 
/*1440*/      OPC_MoveParent,
/*1441*/      OPC_RecordChild1, // #0 = $vA
/*1442*/      OPC_RecordChild2, // #1 = $vB
/*1443*/      OPC_RecordChild3, // #2 = $vC
/*1444*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMSUMSHS), 0,
                  1/*#VTs*/, MVT::v4i32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4i32 1539:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v4i32:$vC) - Complexity = 8
              // Dst: (VMSUMSHS:v4i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v4i32:$vC)
/*1454*/    /*Scope*/ 17, /*->1472*/
/*1455*/      OPC_CheckInteger, 4|128,12/*1540*/, 
/*1458*/      OPC_MoveParent,
/*1459*/      OPC_RecordChild1, // #0 = $vA
/*1460*/      OPC_RecordChild2, // #1 = $vB
/*1461*/      OPC_RecordChild3, // #2 = $vC
/*1462*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMSUMUBM), 0,
                  1/*#VTs*/, MVT::v4i32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4i32 1540:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB, VRRC:v4i32:$vC) - Complexity = 8
              // Dst: (VMSUMUBM:v4i32 VRRC:v16i8:$vA, VRRC:v16i8:$vB, VRRC:v4i32:$vC)
/*1472*/    /*Scope*/ 17, /*->1490*/
/*1473*/      OPC_CheckInteger, 5|128,12/*1541*/, 
/*1476*/      OPC_MoveParent,
/*1477*/      OPC_RecordChild1, // #0 = $vA
/*1478*/      OPC_RecordChild2, // #1 = $vB
/*1479*/      OPC_RecordChild3, // #2 = $vC
/*1480*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMSUMUHM), 0,
                  1/*#VTs*/, MVT::v4i32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4i32 1541:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v4i32:$vC) - Complexity = 8
              // Dst: (VMSUMUHM:v4i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v4i32:$vC)
/*1490*/    /*Scope*/ 17, /*->1508*/
/*1491*/      OPC_CheckInteger, 6|128,12/*1542*/, 
/*1494*/      OPC_MoveParent,
/*1495*/      OPC_RecordChild1, // #0 = $vA
/*1496*/      OPC_RecordChild2, // #1 = $vB
/*1497*/      OPC_RecordChild3, // #2 = $vC
/*1498*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMSUMUHS), 0,
                  1/*#VTs*/, MVT::v4i32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4i32 1542:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v4i32:$vC) - Complexity = 8
              // Dst: (VMSUMUHS:v4i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB, VRRC:v4i32:$vC)
/*1508*/    /*Scope*/ 15, /*->1524*/
/*1509*/      OPC_CheckInteger, 7|128,12/*1543*/, 
/*1512*/      OPC_MoveParent,
/*1513*/      OPC_RecordChild1, // #0 = $vA
/*1514*/      OPC_RecordChild2, // #1 = $vB
/*1515*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMULESB), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1543:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VMULESB:v8i16 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1524*/    /*Scope*/ 15, /*->1540*/
/*1525*/      OPC_CheckInteger, 8|128,12/*1544*/, 
/*1528*/      OPC_MoveParent,
/*1529*/      OPC_RecordChild1, // #0 = $vA
/*1530*/      OPC_RecordChild2, // #1 = $vB
/*1531*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMULESH), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1544:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VMULESH:v4i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1540*/    /*Scope*/ 15, /*->1556*/
/*1541*/      OPC_CheckInteger, 9|128,12/*1545*/, 
/*1544*/      OPC_MoveParent,
/*1545*/      OPC_RecordChild1, // #0 = $vA
/*1546*/      OPC_RecordChild2, // #1 = $vB
/*1547*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMULEUB), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1545:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VMULEUB:v8i16 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1556*/    /*Scope*/ 15, /*->1572*/
/*1557*/      OPC_CheckInteger, 10|128,12/*1546*/, 
/*1560*/      OPC_MoveParent,
/*1561*/      OPC_RecordChild1, // #0 = $vA
/*1562*/      OPC_RecordChild2, // #1 = $vB
/*1563*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMULEUH), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1546:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VMULEUH:v4i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1572*/    /*Scope*/ 15, /*->1588*/
/*1573*/      OPC_CheckInteger, 11|128,12/*1547*/, 
/*1576*/      OPC_MoveParent,
/*1577*/      OPC_RecordChild1, // #0 = $vA
/*1578*/      OPC_RecordChild2, // #1 = $vB
/*1579*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMULOSB), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1547:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VMULOSB:v8i16 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1588*/    /*Scope*/ 15, /*->1604*/
/*1589*/      OPC_CheckInteger, 12|128,12/*1548*/, 
/*1592*/      OPC_MoveParent,
/*1593*/      OPC_RecordChild1, // #0 = $vA
/*1594*/      OPC_RecordChild2, // #1 = $vB
/*1595*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMULOSH), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1548:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VMULOSH:v4i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1604*/    /*Scope*/ 15, /*->1620*/
/*1605*/      OPC_CheckInteger, 13|128,12/*1549*/, 
/*1608*/      OPC_MoveParent,
/*1609*/      OPC_RecordChild1, // #0 = $vA
/*1610*/      OPC_RecordChild2, // #1 = $vB
/*1611*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMULOUB), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1549:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VMULOUB:v8i16 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1620*/    /*Scope*/ 15, /*->1636*/
/*1621*/      OPC_CheckInteger, 14|128,12/*1550*/, 
/*1624*/      OPC_MoveParent,
/*1625*/      OPC_RecordChild1, // #0 = $vA
/*1626*/      OPC_RecordChild2, // #1 = $vB
/*1627*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMULOUH), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1550:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VMULOUH:v4i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1636*/    /*Scope*/ 15, /*->1652*/
/*1637*/      OPC_CheckInteger, 47|128,12/*1583*/, 
/*1640*/      OPC_MoveParent,
/*1641*/      OPC_RecordChild1, // #0 = $vA
/*1642*/      OPC_RecordChild2, // #1 = $vB
/*1643*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBCUW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1583:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSUBCUW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1652*/    /*Scope*/ 15, /*->1668*/
/*1653*/      OPC_CheckInteger, 48|128,12/*1584*/, 
/*1656*/      OPC_MoveParent,
/*1657*/      OPC_RecordChild1, // #0 = $vA
/*1658*/      OPC_RecordChild2, // #1 = $vB
/*1659*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBSBS), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1584:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VSUBSBS:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1668*/    /*Scope*/ 15, /*->1684*/
/*1669*/      OPC_CheckInteger, 49|128,12/*1585*/, 
/*1672*/      OPC_MoveParent,
/*1673*/      OPC_RecordChild1, // #0 = $vA
/*1674*/      OPC_RecordChild2, // #1 = $vB
/*1675*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBSHS), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1585:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VSUBSHS:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1684*/    /*Scope*/ 15, /*->1700*/
/*1685*/      OPC_CheckInteger, 50|128,12/*1586*/, 
/*1688*/      OPC_MoveParent,
/*1689*/      OPC_RecordChild1, // #0 = $vA
/*1690*/      OPC_RecordChild2, // #1 = $vB
/*1691*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBSWS), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1586:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSUBSWS:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1700*/    /*Scope*/ 15, /*->1716*/
/*1701*/      OPC_CheckInteger, 51|128,12/*1587*/, 
/*1704*/      OPC_MoveParent,
/*1705*/      OPC_RecordChild1, // #0 = $vA
/*1706*/      OPC_RecordChild2, // #1 = $vB
/*1707*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBUBS), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1587:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VSUBUBS:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1716*/    /*Scope*/ 15, /*->1732*/
/*1717*/      OPC_CheckInteger, 52|128,12/*1588*/, 
/*1720*/      OPC_MoveParent,
/*1721*/      OPC_RecordChild1, // #0 = $vA
/*1722*/      OPC_RecordChild2, // #1 = $vB
/*1723*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBUHS), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1588:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VSUBUHS:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1732*/    /*Scope*/ 15, /*->1748*/
/*1733*/      OPC_CheckInteger, 53|128,12/*1589*/, 
/*1736*/      OPC_MoveParent,
/*1737*/      OPC_RecordChild1, // #0 = $vA
/*1738*/      OPC_RecordChild2, // #1 = $vB
/*1739*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBUWS), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1589:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSUBUWS:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1748*/    /*Scope*/ 15, /*->1764*/
/*1749*/      OPC_CheckInteger, 58|128,12/*1594*/, 
/*1752*/      OPC_MoveParent,
/*1753*/      OPC_RecordChild1, // #0 = $vA
/*1754*/      OPC_RecordChild2, // #1 = $vB
/*1755*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUMSWS), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1594:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSUMSWS:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1764*/    /*Scope*/ 15, /*->1780*/
/*1765*/      OPC_CheckInteger, 54|128,12/*1590*/, 
/*1768*/      OPC_MoveParent,
/*1769*/      OPC_RecordChild1, // #0 = $vA
/*1770*/      OPC_RecordChild2, // #1 = $vB
/*1771*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUM2SWS), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1590:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSUM2SWS:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1780*/    /*Scope*/ 15, /*->1796*/
/*1781*/      OPC_CheckInteger, 55|128,12/*1591*/, 
/*1784*/      OPC_MoveParent,
/*1785*/      OPC_RecordChild1, // #0 = $vA
/*1786*/      OPC_RecordChild2, // #1 = $vB
/*1787*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUM4SBS), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1591:iPTR, VRRC:v16i8:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSUM4SBS:v4i32 VRRC:v16i8:$vA, VRRC:v4i32:$vB)
/*1796*/    /*Scope*/ 15, /*->1812*/
/*1797*/      OPC_CheckInteger, 56|128,12/*1592*/, 
/*1800*/      OPC_MoveParent,
/*1801*/      OPC_RecordChild1, // #0 = $vA
/*1802*/      OPC_RecordChild2, // #1 = $vB
/*1803*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUM4SHS), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1592:iPTR, VRRC:v8i16:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSUM4SHS:v4i32 VRRC:v8i16:$vA, VRRC:v4i32:$vB)
/*1812*/    /*Scope*/ 15, /*->1828*/
/*1813*/      OPC_CheckInteger, 57|128,12/*1593*/, 
/*1816*/      OPC_MoveParent,
/*1817*/      OPC_RecordChild1, // #0 = $vA
/*1818*/      OPC_RecordChild2, // #1 = $vB
/*1819*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUM4UBS), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1593:iPTR, VRRC:v16i8:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSUM4UBS:v4i32 VRRC:v16i8:$vA, VRRC:v4i32:$vB)
/*1828*/    /*Scope*/ 15, /*->1844*/
/*1829*/      OPC_CheckInteger, 29|128,12/*1565*/, 
/*1832*/      OPC_MoveParent,
/*1833*/      OPC_RecordChild1, // #0 = $vA
/*1834*/      OPC_RecordChild2, // #1 = $vB
/*1835*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VRLB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1565:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VRLB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1844*/    /*Scope*/ 15, /*->1860*/
/*1845*/      OPC_CheckInteger, 30|128,12/*1566*/, 
/*1848*/      OPC_MoveParent,
/*1849*/      OPC_RecordChild1, // #0 = $vA
/*1850*/      OPC_RecordChild2, // #1 = $vB
/*1851*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VRLH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1566:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VRLH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1860*/    /*Scope*/ 15, /*->1876*/
/*1861*/      OPC_CheckInteger, 31|128,12/*1567*/, 
/*1864*/      OPC_MoveParent,
/*1865*/      OPC_RecordChild1, // #0 = $vA
/*1866*/      OPC_RecordChild2, // #1 = $vB
/*1867*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VRLW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1567:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VRLW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1876*/    /*Scope*/ 15, /*->1892*/
/*1877*/      OPC_CheckInteger, 34|128,12/*1570*/, 
/*1880*/      OPC_MoveParent,
/*1881*/      OPC_RecordChild1, // #0 = $vA
/*1882*/      OPC_RecordChild2, // #1 = $vB
/*1883*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSL), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1570:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSL:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1892*/    /*Scope*/ 15, /*->1908*/
/*1893*/      OPC_CheckInteger, 37|128,12/*1573*/, 
/*1896*/      OPC_MoveParent,
/*1897*/      OPC_RecordChild1, // #0 = $vA
/*1898*/      OPC_RecordChild2, // #1 = $vB
/*1899*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSLO), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1573:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSLO:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1908*/    /*Scope*/ 15, /*->1924*/
/*1909*/      OPC_CheckInteger, 35|128,12/*1571*/, 
/*1912*/      OPC_MoveParent,
/*1913*/      OPC_RecordChild1, // #0 = $vA
/*1914*/      OPC_RecordChild2, // #1 = $vB
/*1915*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSLB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1571:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VSLB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*1924*/    /*Scope*/ 15, /*->1940*/
/*1925*/      OPC_CheckInteger, 36|128,12/*1572*/, 
/*1928*/      OPC_MoveParent,
/*1929*/      OPC_RecordChild1, // #0 = $vA
/*1930*/      OPC_RecordChild2, // #1 = $vB
/*1931*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSLH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1572:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VSLH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*1940*/    /*Scope*/ 15, /*->1956*/
/*1941*/      OPC_CheckInteger, 38|128,12/*1574*/, 
/*1944*/      OPC_MoveParent,
/*1945*/      OPC_RecordChild1, // #0 = $vA
/*1946*/      OPC_RecordChild2, // #1 = $vB
/*1947*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSLW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1574:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSLW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1956*/    /*Scope*/ 15, /*->1972*/
/*1957*/      OPC_CheckInteger, 39|128,12/*1575*/, 
/*1960*/      OPC_MoveParent,
/*1961*/      OPC_RecordChild1, // #0 = $vA
/*1962*/      OPC_RecordChild2, // #1 = $vB
/*1963*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSR), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1575:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSR:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1972*/    /*Scope*/ 15, /*->1988*/
/*1973*/      OPC_CheckInteger, 45|128,12/*1581*/, 
/*1976*/      OPC_MoveParent,
/*1977*/      OPC_RecordChild1, // #0 = $vA
/*1978*/      OPC_RecordChild2, // #1 = $vB
/*1979*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRO), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1581:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSRO:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*1988*/    /*Scope*/ 15, /*->2004*/
/*1989*/      OPC_CheckInteger, 40|128,12/*1576*/, 
/*1992*/      OPC_MoveParent,
/*1993*/      OPC_RecordChild1, // #0 = $vA
/*1994*/      OPC_RecordChild2, // #1 = $vB
/*1995*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRAB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1576:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VSRAB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*2004*/    /*Scope*/ 15, /*->2020*/
/*2005*/      OPC_CheckInteger, 41|128,12/*1577*/, 
/*2008*/      OPC_MoveParent,
/*2009*/      OPC_RecordChild1, // #0 = $vA
/*2010*/      OPC_RecordChild2, // #1 = $vB
/*2011*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRAH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1577:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VSRAH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*2020*/    /*Scope*/ 15, /*->2036*/
/*2021*/      OPC_CheckInteger, 42|128,12/*1578*/, 
/*2024*/      OPC_MoveParent,
/*2025*/      OPC_RecordChild1, // #0 = $vA
/*2026*/      OPC_RecordChild2, // #1 = $vB
/*2027*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRAW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1578:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSRAW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*2036*/    /*Scope*/ 15, /*->2052*/
/*2037*/      OPC_CheckInteger, 43|128,12/*1579*/, 
/*2040*/      OPC_MoveParent,
/*2041*/      OPC_RecordChild1, // #0 = $vA
/*2042*/      OPC_RecordChild2, // #1 = $vB
/*2043*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1579:iPTR, VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VSRB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*2052*/    /*Scope*/ 15, /*->2068*/
/*2053*/      OPC_CheckInteger, 44|128,12/*1580*/, 
/*2056*/      OPC_MoveParent,
/*2057*/      OPC_RecordChild1, // #0 = $vA
/*2058*/      OPC_RecordChild2, // #1 = $vB
/*2059*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1580:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VSRH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*2068*/    /*Scope*/ 15, /*->2084*/
/*2069*/      OPC_CheckInteger, 46|128,12/*1582*/, 
/*2072*/      OPC_MoveParent,
/*2073*/      OPC_RecordChild1, // #0 = $vA
/*2074*/      OPC_RecordChild2, // #1 = $vB
/*2075*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4i32 1582:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VSRW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*2084*/    /*Scope*/ 15, /*->2100*/
/*2085*/      OPC_CheckInteger, 17|128,12/*1553*/, 
/*2088*/      OPC_MoveParent,
/*2089*/      OPC_RecordChild1, // #0 = $vA
/*2090*/      OPC_RecordChild2, // #1 = $vB
/*2091*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VPKPX), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1553:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VPKPX:v8i16 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*2100*/    /*Scope*/ 15, /*->2116*/
/*2101*/      OPC_CheckInteger, 18|128,12/*1554*/, 
/*2104*/      OPC_MoveParent,
/*2105*/      OPC_RecordChild1, // #0 = $vA
/*2106*/      OPC_RecordChild2, // #1 = $vB
/*2107*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VPKSHSS), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1554:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VPKSHSS:v16i8 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*2116*/    /*Scope*/ 15, /*->2132*/
/*2117*/      OPC_CheckInteger, 19|128,12/*1555*/, 
/*2120*/      OPC_MoveParent,
/*2121*/      OPC_RecordChild1, // #0 = $vA
/*2122*/      OPC_RecordChild2, // #1 = $vB
/*2123*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VPKSHUS), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1555:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VPKSHUS:v16i8 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*2132*/    /*Scope*/ 15, /*->2148*/
/*2133*/      OPC_CheckInteger, 20|128,12/*1556*/, 
/*2136*/      OPC_MoveParent,
/*2137*/      OPC_RecordChild1, // #0 = $vA
/*2138*/      OPC_RecordChild2, // #1 = $vB
/*2139*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VPKSWSS), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1556:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VPKSWSS:v16i8 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*2148*/    /*Scope*/ 15, /*->2164*/
/*2149*/      OPC_CheckInteger, 21|128,12/*1557*/, 
/*2152*/      OPC_MoveParent,
/*2153*/      OPC_RecordChild1, // #0 = $vA
/*2154*/      OPC_RecordChild2, // #1 = $vB
/*2155*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VPKSWUS), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1557:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VPKSWUS:v8i16 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*2164*/    /*Scope*/ 15, /*->2180*/
/*2165*/      OPC_CheckInteger, 22|128,12/*1558*/, 
/*2168*/      OPC_MoveParent,
/*2169*/      OPC_RecordChild1, // #0 = $vA
/*2170*/      OPC_RecordChild2, // #1 = $vB
/*2171*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VPKUHUS), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v16i8 1558:iPTR, VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VPKUHUS:v16i8 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*2180*/    /*Scope*/ 15, /*->2196*/
/*2181*/      OPC_CheckInteger, 23|128,12/*1559*/, 
/*2184*/      OPC_MoveParent,
/*2185*/      OPC_RecordChild1, // #0 = $vA
/*2186*/      OPC_RecordChild2, // #1 = $vB
/*2187*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VPKUWUS), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v8i16 1559:iPTR, VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 8
              // Dst: (VPKUWUS:v8i16 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*2196*/    /*Scope*/ 13, /*->2210*/
/*2197*/      OPC_CheckInteger, 59|128,12/*1595*/, 
/*2200*/      OPC_MoveParent,
/*2201*/      OPC_RecordChild1, // #0 = $vB
/*2202*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VUPKHPX), 0,
                  1/*#VTs*/, MVT::v4i32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4i32 1595:iPTR, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VUPKHPX:v4i32 VRRC:v8i16:$vB)
/*2210*/    /*Scope*/ 13, /*->2224*/
/*2211*/      OPC_CheckInteger, 60|128,12/*1596*/, 
/*2214*/      OPC_MoveParent,
/*2215*/      OPC_RecordChild1, // #0 = $vB
/*2216*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VUPKHSB), 0,
                  1/*#VTs*/, MVT::v8i16, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v8i16 1596:iPTR, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VUPKHSB:v8i16 VRRC:v16i8:$vB)
/*2224*/    /*Scope*/ 13, /*->2238*/
/*2225*/      OPC_CheckInteger, 61|128,12/*1597*/, 
/*2228*/      OPC_MoveParent,
/*2229*/      OPC_RecordChild1, // #0 = $vB
/*2230*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VUPKHSH), 0,
                  1/*#VTs*/, MVT::v4i32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4i32 1597:iPTR, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VUPKHSH:v4i32 VRRC:v8i16:$vB)
/*2238*/    /*Scope*/ 13, /*->2252*/
/*2239*/      OPC_CheckInteger, 62|128,12/*1598*/, 
/*2242*/      OPC_MoveParent,
/*2243*/      OPC_RecordChild1, // #0 = $vB
/*2244*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VUPKLPX), 0,
                  1/*#VTs*/, MVT::v4i32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4i32 1598:iPTR, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VUPKLPX:v4i32 VRRC:v8i16:$vB)
/*2252*/    /*Scope*/ 13, /*->2266*/
/*2253*/      OPC_CheckInteger, 63|128,12/*1599*/, 
/*2256*/      OPC_MoveParent,
/*2257*/      OPC_RecordChild1, // #0 = $vB
/*2258*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VUPKLSB), 0,
                  1/*#VTs*/, MVT::v8i16, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v8i16 1599:iPTR, VRRC:v16i8:$vB) - Complexity = 8
              // Dst: (VUPKLSB:v8i16 VRRC:v16i8:$vB)
/*2266*/    /*Scope*/ 13, /*->2280*/
/*2267*/      OPC_CheckInteger, 64|128,12/*1600*/, 
/*2270*/      OPC_MoveParent,
/*2271*/      OPC_RecordChild1, // #0 = $vB
/*2272*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VUPKLSH), 0,
                  1/*#VTs*/, MVT::v4i32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4i32 1600:iPTR, VRRC:v8i16:$vB) - Complexity = 8
              // Dst: (VUPKLSH:v4i32 VRRC:v8i16:$vB)
/*2280*/    /*Scope*/ 40, /*->2321*/
/*2281*/      OPC_CheckInteger, 79|128,11/*1487*/, 
/*2284*/      OPC_MoveParent,
/*2285*/      OPC_RecordChild1, // #0 = $vB
/*2286*/      OPC_Scope, 13, /*->2301*/ // 2 children in Scope
/*2288*/        OPC_MoveChild, 2,
/*2290*/        OPC_CheckInteger, 0, 
/*2292*/        OPC_MoveParent,
/*2293*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VCFSX_0), 0,
                    1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
                // Src: (intrinsic_wo_chain:v4f32 1487:iPTR, VRRC:v4i32:$vB, 0:i32) - Complexity = 13
                // Dst: (VCFSX_0:v4f32 VRRC:v4i32:$vB)
/*2301*/      /*Scope*/ 18, /*->2320*/
/*2302*/        OPC_RecordChild2, // #1 = $UIMM
/*2303*/        OPC_MoveChild, 2,
/*2305*/        OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*2308*/        OPC_MoveParent,
/*2309*/        OPC_EmitConvertToTarget, 1,
/*2311*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VCFSX), 0,
                    1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 2, 0, 
                // Src: (intrinsic_wo_chain:v4f32 1487:iPTR, VRRC:v4i32:$vB, (imm:i32):$UIMM) - Complexity = 11
                // Dst: (VCFSX:v4f32 (imm:i32):$UIMM, VRRC:v4i32:$vB)
/*2320*/      0, /*End of Scope*/
/*2321*/    /*Scope*/ 40, /*->2362*/
/*2322*/      OPC_CheckInteger, 80|128,11/*1488*/, 
/*2325*/      OPC_MoveParent,
/*2326*/      OPC_RecordChild1, // #0 = $vB
/*2327*/      OPC_Scope, 13, /*->2342*/ // 2 children in Scope
/*2329*/        OPC_MoveChild, 2,
/*2331*/        OPC_CheckInteger, 0, 
/*2333*/        OPC_MoveParent,
/*2334*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VCFUX_0), 0,
                    1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
                // Src: (intrinsic_wo_chain:v4f32 1488:iPTR, VRRC:v4i32:$vB, 0:i32) - Complexity = 13
                // Dst: (VCFUX_0:v4f32 VRRC:v4i32:$vB)
/*2342*/      /*Scope*/ 18, /*->2361*/
/*2343*/        OPC_RecordChild2, // #1 = $UIMM
/*2344*/        OPC_MoveChild, 2,
/*2346*/        OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*2349*/        OPC_MoveParent,
/*2350*/        OPC_EmitConvertToTarget, 1,
/*2352*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VCFUX), 0,
                    1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 2, 0, 
                // Src: (intrinsic_wo_chain:v4f32 1488:iPTR, VRRC:v4i32:$vB, (imm:i32):$UIMM) - Complexity = 11
                // Dst: (VCFUX:v4f32 (imm:i32):$UIMM, VRRC:v4i32:$vB)
/*2361*/      0, /*End of Scope*/
/*2362*/    /*Scope*/ 13, /*->2376*/
/*2363*/      OPC_CheckInteger, 109|128,11/*1517*/, 
/*2366*/      OPC_MoveParent,
/*2367*/      OPC_RecordChild1, // #0 = $vB
/*2368*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VEXPTEFP), 0,
                  1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4f32 1517:iPTR, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VEXPTEFP:v4f32 VRRC:v4f32:$vB)
/*2376*/    /*Scope*/ 13, /*->2390*/
/*2377*/      OPC_CheckInteger, 110|128,11/*1518*/, 
/*2380*/      OPC_MoveParent,
/*2381*/      OPC_RecordChild1, // #0 = $vB
/*2382*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VLOGEFP), 0,
                  1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4f32 1518:iPTR, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VLOGEFP:v4f32 VRRC:v4f32:$vB)
/*2390*/    /*Scope*/ 15, /*->2406*/
/*2391*/      OPC_CheckInteger, 112|128,11/*1520*/, 
/*2394*/      OPC_MoveParent,
/*2395*/      OPC_RecordChild1, // #0 = $vA
/*2396*/      OPC_RecordChild2, // #1 = $vB
/*2397*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMAXFP), 0,
                  1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4f32 1520:iPTR, VRRC:v4f32:$vA, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VMAXFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*2406*/    /*Scope*/ 15, /*->2422*/
/*2407*/      OPC_CheckInteger, 121|128,11/*1529*/, 
/*2410*/      OPC_MoveParent,
/*2411*/      OPC_RecordChild1, // #0 = $vA
/*2412*/      OPC_RecordChild2, // #1 = $vB
/*2413*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMINFP), 0,
                  1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 0, 1, 
              // Src: (intrinsic_wo_chain:v4f32 1529:iPTR, VRRC:v4f32:$vA, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VMINFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*2422*/    /*Scope*/ 13, /*->2436*/
/*2423*/      OPC_CheckInteger, 24|128,12/*1560*/, 
/*2426*/      OPC_MoveParent,
/*2427*/      OPC_RecordChild1, // #0 = $vB
/*2428*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VREFP), 0,
                  1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4f32 1560:iPTR, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VREFP:v4f32 VRRC:v4f32:$vB)
/*2436*/    /*Scope*/ 13, /*->2450*/
/*2437*/      OPC_CheckInteger, 25|128,12/*1561*/, 
/*2440*/      OPC_MoveParent,
/*2441*/      OPC_RecordChild1, // #0 = $vB
/*2442*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VRFIM), 0,
                  1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4f32 1561:iPTR, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VRFIM:v4f32 VRRC:v4f32:$vB)
/*2450*/    /*Scope*/ 13, /*->2464*/
/*2451*/      OPC_CheckInteger, 26|128,12/*1562*/, 
/*2454*/      OPC_MoveParent,
/*2455*/      OPC_RecordChild1, // #0 = $vB
/*2456*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VRFIN), 0,
                  1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4f32 1562:iPTR, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VRFIN:v4f32 VRRC:v4f32:$vB)
/*2464*/    /*Scope*/ 13, /*->2478*/
/*2465*/      OPC_CheckInteger, 27|128,12/*1563*/, 
/*2468*/      OPC_MoveParent,
/*2469*/      OPC_RecordChild1, // #0 = $vB
/*2470*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VRFIP), 0,
                  1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4f32 1563:iPTR, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VRFIP:v4f32 VRRC:v4f32:$vB)
/*2478*/    /*Scope*/ 13, /*->2492*/
/*2479*/      OPC_CheckInteger, 28|128,12/*1564*/, 
/*2482*/      OPC_MoveParent,
/*2483*/      OPC_RecordChild1, // #0 = $vB
/*2484*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VRFIZ), 0,
                  1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4f32 1564:iPTR, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VRFIZ:v4f32 VRRC:v4f32:$vB)
/*2492*/    /*Scope*/ 13, /*->2506*/
/*2493*/      OPC_CheckInteger, 32|128,12/*1568*/, 
/*2496*/      OPC_MoveParent,
/*2497*/      OPC_RecordChild1, // #0 = $vB
/*2498*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VRSQRTEFP), 0,
                  1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
              // Src: (intrinsic_wo_chain:v4f32 1568:iPTR, VRRC:v4f32:$vB) - Complexity = 8
              // Dst: (VRSQRTEFP:v4f32 VRRC:v4f32:$vB)
/*2506*/    /*Scope*/ 17, /*->2524*/
/*2507*/      OPC_CheckInteger, 111|128,11/*1519*/, 
/*2510*/      OPC_MoveParent,
/*2511*/      OPC_RecordChild1, // #0 = $A
/*2512*/      OPC_RecordChild2, // #1 = $B
/*2513*/      OPC_RecordChild3, // #2 = $C
/*2514*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMADDFP), 0,
                  1/*#VTs*/, MVT::v4f32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4f32 1519:iPTR, VRRC:v4f32:$A, VRRC:v4f32:$B, VRRC:v4f32:$C) - Complexity = 8
              // Dst: (VMADDFP:v4f32 VRRC:v4f32:$A, VRRC:v4f32:$B, VRRC:v4f32:$C)
/*2524*/    /*Scope*/ 17, /*->2542*/
/*2525*/      OPC_CheckInteger, 15|128,12/*1551*/, 
/*2528*/      OPC_MoveParent,
/*2529*/      OPC_RecordChild1, // #0 = $A
/*2530*/      OPC_RecordChild2, // #1 = $B
/*2531*/      OPC_RecordChild3, // #2 = $C
/*2532*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VNMSUBFP), 0,
                  1/*#VTs*/, MVT::v4f32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (intrinsic_wo_chain:v4f32 1551:iPTR, VRRC:v4f32:$A, VRRC:v4f32:$B, VRRC:v4f32:$C) - Complexity = 8
              // Dst: (VNMSUBFP:v4f32 VRRC:v4f32:$A, VRRC:v4f32:$B, VRRC:v4f32:$C)
/*2542*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 59|128,4/*571*/,  TARGET_VAL(ISD::ADD),// ->3118
/*2547*/    OPC_Scope, 49|128,1/*177*/, /*->2727*/ // 3 children in Scope
/*2550*/      OPC_RecordChild0, // #0 = $rA
/*2551*/      OPC_MoveChild, 1,
/*2553*/      OPC_SwitchOpcode /*2 cases */, 24,  TARGET_VAL(PPCISD::Lo),// ->2581
/*2557*/        OPC_RecordChild0, // #1 = $sym
/*2558*/        OPC_MoveChild, 0,
/*2560*/        OPC_CheckOpcode, TARGET_VAL(ISD::TargetGlobalAddress),
/*2563*/        OPC_MoveParent,
/*2564*/        OPC_MoveChild, 1,
/*2566*/        OPC_CheckInteger, 0, 
/*2568*/        OPC_MoveParent,
/*2569*/        OPC_MoveParent,
/*2570*/        OPC_CheckType, MVT::i32,
/*2572*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LA), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (add:i32 GPRC:i32:$rA, (PPClo:i32 (tglobaladdr:i32):$sym, 0:i32)) - Complexity = 14
                // Dst: (LA:i32 GPRC:i32:$rA, (tglobaladdr:i32):$sym)
              /*SwitchOpcode*/ 13|128,1/*141*/,  TARGET_VAL(PPCISD::Hi),// ->2726
/*2585*/        OPC_RecordChild0, // #1 = $g
/*2586*/        OPC_MoveChild, 0,
/*2588*/        OPC_SwitchOpcode /*4 cases */, 31,  TARGET_VAL(ISD::TargetGlobalAddress),// ->2623
/*2592*/          OPC_MoveParent,
/*2593*/          OPC_MoveChild, 1,
/*2595*/          OPC_CheckInteger, 0, 
/*2597*/          OPC_MoveParent,
/*2598*/          OPC_MoveParent,
/*2599*/          OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->2611
/*2602*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                    // Src: (add:i32 GPRC:i32:$in, (PPChi:i32 (tglobaladdr:i32):$g, 0:i32)) - Complexity = 14
                    // Dst: (ADDIS:i32 GPRC:i32:$in, (tglobaladdr:i32):$g)
                  /*SwitchType*/ 9,  MVT::i64,// ->2622
/*2613*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                    // Src: (add:i64 G8RC:i64:$in, (PPChi:i64 (tglobaladdr:i64):$g, 0:i64)) - Complexity = 14
                    // Dst: (ADDIS8:i64 G8RC:i64:$in, (tglobaladdr:i64):$g)
                  0, // EndSwitchType
                /*SwitchOpcode*/ 31,  TARGET_VAL(ISD::TargetConstantPool),// ->2657
/*2626*/          OPC_MoveParent,
/*2627*/          OPC_MoveChild, 1,
/*2629*/          OPC_CheckInteger, 0, 
/*2631*/          OPC_MoveParent,
/*2632*/          OPC_MoveParent,
/*2633*/          OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->2645
/*2636*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                    // Src: (add:i32 GPRC:i32:$in, (PPChi:i32 (tconstpool:i32):$g, 0:i32)) - Complexity = 14
                    // Dst: (ADDIS:i32 GPRC:i32:$in, (tconstpool:i32):$g)
                  /*SwitchType*/ 9,  MVT::i64,// ->2656
/*2647*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                    // Src: (add:i64 G8RC:i64:$in, (PPChi:i64 (tconstpool:i64):$g, 0:i64)) - Complexity = 14
                    // Dst: (ADDIS8:i64 G8RC:i64:$in, (tconstpool:i64):$g)
                  0, // EndSwitchType
                /*SwitchOpcode*/ 31,  TARGET_VAL(ISD::TargetJumpTable),// ->2691
/*2660*/          OPC_MoveParent,
/*2661*/          OPC_MoveChild, 1,
/*2663*/          OPC_CheckInteger, 0, 
/*2665*/          OPC_MoveParent,
/*2666*/          OPC_MoveParent,
/*2667*/          OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->2679
/*2670*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                    // Src: (add:i32 GPRC:i32:$in, (PPChi:i32 (tjumptable:i32):$g, 0:i32)) - Complexity = 14
                    // Dst: (ADDIS:i32 GPRC:i32:$in, (tjumptable:i32):$g)
                  /*SwitchType*/ 9,  MVT::i64,// ->2690
/*2681*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                    // Src: (add:i64 G8RC:i64:$in, (PPChi:i64 (tjumptable:i64):$g, 0:i64)) - Complexity = 14
                    // Dst: (ADDIS8:i64 G8RC:i64:$in, (tjumptable:i64):$g)
                  0, // EndSwitchType
                /*SwitchOpcode*/ 31,  TARGET_VAL(ISD::TargetBlockAddress),// ->2725
/*2694*/          OPC_MoveParent,
/*2695*/          OPC_MoveChild, 1,
/*2697*/          OPC_CheckInteger, 0, 
/*2699*/          OPC_MoveParent,
/*2700*/          OPC_MoveParent,
/*2701*/          OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->2713
/*2704*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                    // Src: (add:i32 GPRC:i32:$in, (PPChi:i32 (tblockaddress:i32):$g, 0:i32)) - Complexity = 14
                    // Dst: (ADDIS:i32 GPRC:i32:$in, (tblockaddress:i32):$g)
                  /*SwitchType*/ 9,  MVT::i64,// ->2724
/*2715*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                    // Src: (add:i64 G8RC:i64:$in, (PPChi:i64 (tblockaddress:i64):$g, 0:i64)) - Complexity = 14
                    // Dst: (ADDIS8:i64 G8RC:i64:$in, (tblockaddress:i64):$g)
                  0, // EndSwitchType
                0, // EndSwitchOpcode
              0, // EndSwitchOpcode
/*2727*/    /*Scope*/ 53|128,1/*181*/, /*->2910*/
/*2729*/      OPC_MoveChild, 0,
/*2731*/      OPC_SwitchOpcode /*2 cases */, 25,  TARGET_VAL(PPCISD::Lo),// ->2760
/*2735*/        OPC_RecordChild0, // #0 = $sym
/*2736*/        OPC_MoveChild, 0,
/*2738*/        OPC_CheckOpcode, TARGET_VAL(ISD::TargetGlobalAddress),
/*2741*/        OPC_MoveParent,
/*2742*/        OPC_MoveChild, 1,
/*2744*/        OPC_CheckInteger, 0, 
/*2746*/        OPC_MoveParent,
/*2747*/        OPC_MoveParent,
/*2748*/        OPC_RecordChild1, // #1 = $rA
/*2749*/        OPC_CheckType, MVT::i32,
/*2751*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LA), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                // Src: (add:i32 (PPClo:i32 (tglobaladdr:i32):$sym, 0:i32), GPRC:i32:$rA) - Complexity = 14
                // Dst: (LA:i32 GPRC:i32:$rA, (tglobaladdr:i32):$sym)
              /*SwitchOpcode*/ 17|128,1/*145*/,  TARGET_VAL(PPCISD::Hi),// ->2909
/*2764*/        OPC_RecordChild0, // #0 = $g
/*2765*/        OPC_MoveChild, 0,
/*2767*/        OPC_SwitchOpcode /*4 cases */, 32,  TARGET_VAL(ISD::TargetGlobalAddress),// ->2803
/*2771*/          OPC_MoveParent,
/*2772*/          OPC_MoveChild, 1,
/*2774*/          OPC_CheckInteger, 0, 
/*2776*/          OPC_MoveParent,
/*2777*/          OPC_MoveParent,
/*2778*/          OPC_RecordChild1, // #1 = $in
/*2779*/          OPC_SwitchType /*2 cases */, 9,  MVT::i64,// ->2791
/*2782*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                    // Src: (add:i64 (PPChi:i64 (tglobaladdr:i64):$g, 0:i64), G8RC:i64:$in) - Complexity = 14
                    // Dst: (ADDIS8:i64 G8RC:i64:$in, (tglobaladdr:i64):$g)
                  /*SwitchType*/ 9,  MVT::i32,// ->2802
/*2793*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                    // Src: (add:i32 (PPChi:i32 (tglobaladdr:i32):$g, 0:i32), GPRC:i32:$in) - Complexity = 14
                    // Dst: (ADDIS:i32 GPRC:i32:$in, (tglobaladdr:i32):$g)
                  0, // EndSwitchType
                /*SwitchOpcode*/ 32,  TARGET_VAL(ISD::TargetConstantPool),// ->2838
/*2806*/          OPC_MoveParent,
/*2807*/          OPC_MoveChild, 1,
/*2809*/          OPC_CheckInteger, 0, 
/*2811*/          OPC_MoveParent,
/*2812*/          OPC_MoveParent,
/*2813*/          OPC_RecordChild1, // #1 = $in
/*2814*/          OPC_SwitchType /*2 cases */, 9,  MVT::i64,// ->2826
/*2817*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                    // Src: (add:i64 (PPChi:i64 (tconstpool:i64):$g, 0:i64), G8RC:i64:$in) - Complexity = 14
                    // Dst: (ADDIS8:i64 G8RC:i64:$in, (tconstpool:i64):$g)
                  /*SwitchType*/ 9,  MVT::i32,// ->2837
/*2828*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                    // Src: (add:i32 (PPChi:i32 (tconstpool:i32):$g, 0:i32), GPRC:i32:$in) - Complexity = 14
                    // Dst: (ADDIS:i32 GPRC:i32:$in, (tconstpool:i32):$g)
                  0, // EndSwitchType
                /*SwitchOpcode*/ 32,  TARGET_VAL(ISD::TargetJumpTable),// ->2873
/*2841*/          OPC_MoveParent,
/*2842*/          OPC_MoveChild, 1,
/*2844*/          OPC_CheckInteger, 0, 
/*2846*/          OPC_MoveParent,
/*2847*/          OPC_MoveParent,
/*2848*/          OPC_RecordChild1, // #1 = $in
/*2849*/          OPC_SwitchType /*2 cases */, 9,  MVT::i64,// ->2861
/*2852*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                    // Src: (add:i64 (PPChi:i64 (tjumptable:i64):$g, 0:i64), G8RC:i64:$in) - Complexity = 14
                    // Dst: (ADDIS8:i64 G8RC:i64:$in, (tjumptable:i64):$g)
                  /*SwitchType*/ 9,  MVT::i32,// ->2872
/*2863*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                    // Src: (add:i32 (PPChi:i32 (tjumptable:i32):$g, 0:i32), GPRC:i32:$in) - Complexity = 14
                    // Dst: (ADDIS:i32 GPRC:i32:$in, (tjumptable:i32):$g)
                  0, // EndSwitchType
                /*SwitchOpcode*/ 32,  TARGET_VAL(ISD::TargetBlockAddress),// ->2908
/*2876*/          OPC_MoveParent,
/*2877*/          OPC_MoveChild, 1,
/*2879*/          OPC_CheckInteger, 0, 
/*2881*/          OPC_MoveParent,
/*2882*/          OPC_MoveParent,
/*2883*/          OPC_RecordChild1, // #1 = $in
/*2884*/          OPC_SwitchType /*2 cases */, 9,  MVT::i64,// ->2896
/*2887*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                    // Src: (add:i64 (PPChi:i64 (tblockaddress:i64):$g, 0:i64), G8RC:i64:$in) - Complexity = 14
                    // Dst: (ADDIS8:i64 G8RC:i64:$in, (tblockaddress:i64):$g)
                  /*SwitchType*/ 9,  MVT::i32,// ->2907
/*2898*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                    // Src: (add:i32 (PPChi:i32 (tblockaddress:i32):$g, 0:i32), GPRC:i32:$in) - Complexity = 14
                    // Dst: (ADDIS:i32 GPRC:i32:$in, (tblockaddress:i32):$g)
                  0, // EndSwitchType
                0, // EndSwitchOpcode
              0, // EndSwitchOpcode
/*2910*/    /*Scope*/ 77|128,1/*205*/, /*->3117*/
/*2912*/      OPC_RecordChild0, // #0 = $rA
/*2913*/      OPC_RecordChild1, // #1 = $imm
/*2914*/      OPC_Scope, 11|128,1/*139*/, /*->3056*/ // 6 children in Scope
/*2917*/        OPC_MoveChild, 1,
/*2919*/        OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*2922*/        OPC_Scope, 29, /*->2953*/ // 5 children in Scope
/*2924*/          OPC_CheckPredicate, 0, // Predicate_immSExt16
/*2926*/          OPC_MoveParent,
/*2927*/          OPC_CheckType, MVT::i32,
/*2929*/          OPC_EmitConvertToTarget, 1,
/*2931*/          OPC_Scope, 9, /*->2942*/ // 2 children in Scope
/*2933*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDI), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 2, 
                    // Src: (add:i32 GPRC:i32:$rA, (imm:i32)<<P:Predicate_immSExt16>>:$imm) - Complexity = 7
                    // Dst: (ADDI:i32 GPRC:i32:$rA, (imm:i32):$imm)
/*2942*/          /*Scope*/ 9, /*->2952*/
/*2943*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIL), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 2, 
                    // Src: (add:i32 GPRC:i32:$rA, (imm:i32)<<P:Predicate_immSExt16>>:$imm) - Complexity = 7
                    // Dst: (ADDIL:i32 GPRC:i32:$rA, (imm:i32):$imm)
/*2952*/          0, /*End of Scope*/
/*2953*/        /*Scope*/ 19, /*->2973*/
/*2954*/          OPC_CheckPredicate, 1, // Predicate_imm16ShiftedSExt
/*2956*/          OPC_MoveParent,
/*2957*/          OPC_CheckType, MVT::i32,
/*2959*/          OPC_EmitConvertToTarget, 1,
/*2961*/          OPC_EmitNodeXForm, 0, 2, // HI16
/*2964*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 3, 
                  // Src: (add:i32 GPRC:i32:$rA, (imm:i32)<<P:Predicate_imm16ShiftedSExt>><<X:HI16>>:$imm) - Complexity = 7
                  // Dst: (ADDIS:i32 GPRC:i32:$rA, (HI16:i32 (imm:i32):$imm))
/*2973*/        /*Scope*/ 29, /*->3003*/
/*2974*/          OPC_CheckPredicate, 0, // Predicate_immSExt16
/*2976*/          OPC_MoveParent,
/*2977*/          OPC_CheckType, MVT::i64,
/*2979*/          OPC_EmitConvertToTarget, 1,
/*2981*/          OPC_Scope, 9, /*->2992*/ // 2 children in Scope
/*2983*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDI8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 2, 
                    // Src: (add:i64 G8RC:i64:$rA, (imm:i64)<<P:Predicate_immSExt16>>:$imm) - Complexity = 7
                    // Dst: (ADDI8:i64 G8RC:i64:$rA, (imm:i64):$imm)
/*2992*/          /*Scope*/ 9, /*->3002*/
/*2993*/            OPC_MorphNodeTo, TARGET_VAL(PPC::ADDI8L), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 2, 
                    // Src: (add:i64 G8RC:i64:$rA, (imm:i64)<<P:Predicate_immSExt16>>:$imm) - Complexity = 7
                    // Dst: (ADDI8L:i64 G8RC:i64:$rA, (imm:i64):$imm)
/*3002*/          0, /*End of Scope*/
/*3003*/        /*Scope*/ 19, /*->3023*/
/*3004*/          OPC_CheckPredicate, 1, // Predicate_imm16ShiftedSExt
/*3006*/          OPC_MoveParent,
/*3007*/          OPC_CheckType, MVT::i64,
/*3009*/          OPC_EmitConvertToTarget, 1,
/*3011*/          OPC_EmitNodeXForm, 0, 2, // HI16
/*3014*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 3, 
                  // Src: (add:i64 G8RC:i64:$rA, (imm:i64)<<P:Predicate_imm16ShiftedSExt>><<X:HI16>>:$imm) - Complexity = 7
                  // Dst: (ADDIS8:i64 G8RC:i64:$rA, (HI16:i64 (imm:i64):$imm))
/*3023*/        /*Scope*/ 31, /*->3055*/
/*3024*/          OPC_MoveParent,
/*3025*/          OPC_CheckType, MVT::i32,
/*3027*/          OPC_EmitConvertToTarget, 1,
/*3029*/          OPC_EmitNodeXForm, 1, 2, // LO16
/*3032*/          OPC_EmitNode, TARGET_VAL(PPC::ADDI), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 3,  // Results = #4
/*3041*/          OPC_EmitConvertToTarget, 1,
/*3043*/          OPC_EmitNodeXForm, 2, 5, // HA16
/*3046*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 4, 6, 
                  // Src: (add:i32 GPRC:i32:$in, (imm:i32):$imm) - Complexity = 6
                  // Dst: (ADDIS:i32 (ADDI:i32 GPRC:i32:$in, (LO16:i32 (imm:i32):$imm)), (HA16:i32 (imm:i32):$imm))
/*3055*/        0, /*End of Scope*/
/*3056*/      /*Scope*/ 11, /*->3068*/
/*3057*/        OPC_CheckType, MVT::i32,
/*3059*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADD4), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (add:i32 GPRC:i32:$rA, GPRC:i32:$rB) - Complexity = 3
                // Dst: (ADD4:i32 GPRC:i32:$rA, GPRC:i32:$rB)
/*3068*/      /*Scope*/ 11, /*->3080*/
/*3069*/        OPC_CheckType, MVT::i64,
/*3071*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADD8), 0,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                // Src: (add:i64 G8RC:i64:$rA, G8RC:i64:$rB) - Complexity = 3
                // Dst: (ADD8:i64 G8RC:i64:$rA, G8RC:i64:$rB)
/*3080*/      /*Scope*/ 11, /*->3092*/
/*3081*/        OPC_CheckType, MVT::v16i8,
/*3083*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VADDUBM), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                // Src: (add:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 3
                // Dst: (VADDUBM:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*3092*/      /*Scope*/ 11, /*->3104*/
/*3093*/        OPC_CheckType, MVT::v8i16,
/*3095*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VADDUHM), 0,
                    1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
                // Src: (add:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 3
                // Dst: (VADDUHM:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*3104*/      /*Scope*/ 11, /*->3116*/
/*3105*/        OPC_CheckType, MVT::v4i32,
/*3107*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VADDUWM), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
                // Src: (add:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 3
                // Dst: (VADDUWM:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*3116*/      0, /*End of Scope*/
/*3117*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 72|128,6/*840*/,  TARGET_VAL(ISD::LOAD),// ->3962
/*3122*/    OPC_RecordMemRef,
/*3123*/    OPC_RecordNode,   // #0 = 'ld' chained node
/*3124*/    OPC_RecordChild1, // #1 = $src
/*3125*/    OPC_CheckPredicate, 2, // Predicate_unindexedload
/*3127*/    OPC_Scope, 19, /*->3148*/ // 18 children in Scope
/*3129*/      OPC_CheckPredicate, 3, // Predicate_zextload
/*3131*/      OPC_CheckPredicate, 4, // Predicate_zextloadi8
/*3133*/      OPC_CheckType, MVT::i32,
/*3135*/      OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3138*/      OPC_EmitMergeInputChains1_0,
/*3139*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LBZ), 0|OPFL_Chain|OPFL_MemRefs,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (ld:i32 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi8>> - Complexity = 13
              // Dst: (LBZ:i32 iaddr:iPTR:$src)
/*3148*/    /*Scope*/ 19, /*->3168*/
/*3149*/      OPC_CheckPredicate, 5, // Predicate_sextload
/*3151*/      OPC_CheckPredicate, 6, // Predicate_sextloadi16
/*3153*/      OPC_CheckType, MVT::i32,
/*3155*/      OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3158*/      OPC_EmitMergeInputChains1_0,
/*3159*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LHA), 0|OPFL_Chain|OPFL_MemRefs,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (ld:i32 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_sextload>><<P:Predicate_sextloadi16>> - Complexity = 13
              // Dst: (LHA:i32 iaddr:iPTR:$src)
/*3168*/    /*Scope*/ 19, /*->3188*/
/*3169*/      OPC_CheckPredicate, 3, // Predicate_zextload
/*3171*/      OPC_CheckPredicate, 7, // Predicate_zextloadi16
/*3173*/      OPC_CheckType, MVT::i32,
/*3175*/      OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3178*/      OPC_EmitMergeInputChains1_0,
/*3179*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LHZ), 0|OPFL_Chain|OPFL_MemRefs,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (ld:i32 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi16>> - Complexity = 13
              // Dst: (LHZ:i32 iaddr:iPTR:$src)
/*3188*/    /*Scope*/ 17, /*->3206*/
/*3189*/      OPC_CheckPredicate, 8, // Predicate_load
/*3191*/      OPC_CheckType, MVT::i32,
/*3193*/      OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3196*/      OPC_EmitMergeInputChains1_0,
/*3197*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LWZ), 0|OPFL_Chain|OPFL_MemRefs,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (ld:i32 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_load>> - Complexity = 13
              // Dst: (LWZ:i32 iaddr:iPTR:$src)
/*3206*/    /*Scope*/ 19, /*->3226*/
/*3207*/      OPC_CheckPredicate, 3, // Predicate_zextload
/*3209*/      OPC_CheckPredicate, 4, // Predicate_zextloadi8
/*3211*/      OPC_CheckType, MVT::i32,
/*3213*/      OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3216*/      OPC_EmitMergeInputChains1_0,
/*3217*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LBZX), 0|OPFL_Chain|OPFL_MemRefs,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (ld:i32 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi8>> - Complexity = 13
              // Dst: (LBZX:i32 xaddr:iPTR:$src)
/*3226*/    /*Scope*/ 19, /*->3246*/
/*3227*/      OPC_CheckPredicate, 5, // Predicate_sextload
/*3229*/      OPC_CheckPredicate, 6, // Predicate_sextloadi16
/*3231*/      OPC_CheckType, MVT::i32,
/*3233*/      OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3236*/      OPC_EmitMergeInputChains1_0,
/*3237*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LHAX), 0|OPFL_Chain|OPFL_MemRefs,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (ld:i32 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_sextload>><<P:Predicate_sextloadi16>> - Complexity = 13
              // Dst: (LHAX:i32 xaddr:iPTR:$src)
/*3246*/    /*Scope*/ 19, /*->3266*/
/*3247*/      OPC_CheckPredicate, 3, // Predicate_zextload
/*3249*/      OPC_CheckPredicate, 7, // Predicate_zextloadi16
/*3251*/      OPC_CheckType, MVT::i32,
/*3253*/      OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3256*/      OPC_EmitMergeInputChains1_0,
/*3257*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LHZX), 0|OPFL_Chain|OPFL_MemRefs,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (ld:i32 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi16>> - Complexity = 13
              // Dst: (LHZX:i32 xaddr:iPTR:$src)
/*3266*/    /*Scope*/ 17, /*->3284*/
/*3267*/      OPC_CheckPredicate, 8, // Predicate_load
/*3269*/      OPC_CheckType, MVT::i32,
/*3271*/      OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3274*/      OPC_EmitMergeInputChains1_0,
/*3275*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LWZX), 0|OPFL_Chain|OPFL_MemRefs,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (ld:i32 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_load>> - Complexity = 13
              // Dst: (LWZX:i32 xaddr:iPTR:$src)
/*3284*/    /*Scope*/ 36, /*->3321*/
/*3285*/      OPC_CheckPredicate, 3, // Predicate_zextload
/*3287*/      OPC_CheckPredicate, 9, // Predicate_zextloadi1
/*3289*/      OPC_CheckType, MVT::i32,
/*3291*/      OPC_Scope, 13, /*->3306*/ // 2 children in Scope
/*3293*/        OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3296*/        OPC_EmitMergeInputChains1_0,
/*3297*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LBZ), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i32 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi1>> - Complexity = 13
                // Dst: (LBZ:i32 iaddr:iPTR:$src)
/*3306*/      /*Scope*/ 13, /*->3320*/
/*3307*/        OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3310*/        OPC_EmitMergeInputChains1_0,
/*3311*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LBZX), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i32 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi1>> - Complexity = 13
                // Dst: (LBZX:i32 xaddr:iPTR:$src)
/*3320*/      0, /*End of Scope*/
/*3321*/    /*Scope*/ 105, /*->3427*/
/*3322*/      OPC_CheckPredicate, 10, // Predicate_extload
/*3324*/      OPC_CheckType, MVT::i32,
/*3326*/      OPC_Scope, 32, /*->3360*/ // 3 children in Scope
/*3328*/        OPC_CheckPredicate, 11, // Predicate_extloadi1
/*3330*/        OPC_Scope, 13, /*->3345*/ // 2 children in Scope
/*3332*/          OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3335*/          OPC_EmitMergeInputChains1_0,
/*3336*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LBZ), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i32 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi1>> - Complexity = 13
                  // Dst: (LBZ:i32 iaddr:iPTR:$src)
/*3345*/        /*Scope*/ 13, /*->3359*/
/*3346*/          OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3349*/          OPC_EmitMergeInputChains1_0,
/*3350*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LBZX), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i32 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi1>> - Complexity = 13
                  // Dst: (LBZX:i32 xaddr:iPTR:$src)
/*3359*/        0, /*End of Scope*/
/*3360*/      /*Scope*/ 32, /*->3393*/
/*3361*/        OPC_CheckPredicate, 12, // Predicate_extloadi8
/*3363*/        OPC_Scope, 13, /*->3378*/ // 2 children in Scope
/*3365*/          OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3368*/          OPC_EmitMergeInputChains1_0,
/*3369*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LBZ), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i32 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi8>> - Complexity = 13
                  // Dst: (LBZ:i32 iaddr:iPTR:$src)
/*3378*/        /*Scope*/ 13, /*->3392*/
/*3379*/          OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3382*/          OPC_EmitMergeInputChains1_0,
/*3383*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LBZX), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i32 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi8>> - Complexity = 13
                  // Dst: (LBZX:i32 xaddr:iPTR:$src)
/*3392*/        0, /*End of Scope*/
/*3393*/      /*Scope*/ 32, /*->3426*/
/*3394*/        OPC_CheckPredicate, 13, // Predicate_extloadi16
/*3396*/        OPC_Scope, 13, /*->3411*/ // 2 children in Scope
/*3398*/          OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3401*/          OPC_EmitMergeInputChains1_0,
/*3402*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LHZ), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i32 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi16>> - Complexity = 13
                  // Dst: (LHZ:i32 iaddr:iPTR:$src)
/*3411*/        /*Scope*/ 13, /*->3425*/
/*3412*/          OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3415*/          OPC_EmitMergeInputChains1_0,
/*3416*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LHZX), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i32 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi16>> - Complexity = 13
                  // Dst: (LHZX:i32 xaddr:iPTR:$src)
/*3425*/        0, /*End of Scope*/
/*3426*/      0, /*End of Scope*/
/*3427*/    /*Scope*/ 70, /*->3498*/
/*3428*/      OPC_CheckPredicate, 5, // Predicate_sextload
/*3430*/      OPC_CheckType, MVT::i64,
/*3432*/      OPC_Scope, 15, /*->3449*/ // 4 children in Scope
/*3434*/        OPC_CheckPredicate, 6, // Predicate_sextloadi16
/*3436*/        OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3439*/        OPC_EmitMergeInputChains1_0,
/*3440*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LHA8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_sextload>><<P:Predicate_sextloadi16>> - Complexity = 13
                // Dst: (LHA8:i64 iaddr:iPTR:$src)
/*3449*/      /*Scope*/ 15, /*->3465*/
/*3450*/        OPC_CheckPredicate, 14, // Predicate_sextloadi32
/*3452*/        OPC_CheckComplexPat, /*CP*/3, /*#*/1, // SelectAddrImmShift:$src #2 #3
/*3455*/        OPC_EmitMergeInputChains1_0,
/*3456*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LWA), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 ixaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_sextload>><<P:Predicate_sextloadi32>> - Complexity = 13
                // Dst: (LWA:i64 ixaddr:iPTR:$src)
/*3465*/      /*Scope*/ 15, /*->3481*/
/*3466*/        OPC_CheckPredicate, 6, // Predicate_sextloadi16
/*3468*/        OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3471*/        OPC_EmitMergeInputChains1_0,
/*3472*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LHAX8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_sextload>><<P:Predicate_sextloadi16>> - Complexity = 13
                // Dst: (LHAX8:i64 xaddr:iPTR:$src)
/*3481*/      /*Scope*/ 15, /*->3497*/
/*3482*/        OPC_CheckPredicate, 14, // Predicate_sextloadi32
/*3484*/        OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3487*/        OPC_EmitMergeInputChains1_0,
/*3488*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LWAX), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_sextload>><<P:Predicate_sextloadi32>> - Complexity = 13
                // Dst: (LWAX:i64 xaddr:iPTR:$src)
/*3497*/      0, /*End of Scope*/
/*3498*/    /*Scope*/ 102, /*->3601*/
/*3499*/      OPC_CheckPredicate, 3, // Predicate_zextload
/*3501*/      OPC_CheckType, MVT::i64,
/*3503*/      OPC_Scope, 15, /*->3520*/ // 6 children in Scope
/*3505*/        OPC_CheckPredicate, 4, // Predicate_zextloadi8
/*3507*/        OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3510*/        OPC_EmitMergeInputChains1_0,
/*3511*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LBZ8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi8>> - Complexity = 13
                // Dst: (LBZ8:i64 iaddr:iPTR:$src)
/*3520*/      /*Scope*/ 15, /*->3536*/
/*3521*/        OPC_CheckPredicate, 7, // Predicate_zextloadi16
/*3523*/        OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3526*/        OPC_EmitMergeInputChains1_0,
/*3527*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LHZ8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi16>> - Complexity = 13
                // Dst: (LHZ8:i64 iaddr:iPTR:$src)
/*3536*/      /*Scope*/ 15, /*->3552*/
/*3537*/        OPC_CheckPredicate, 15, // Predicate_zextloadi32
/*3539*/        OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3542*/        OPC_EmitMergeInputChains1_0,
/*3543*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LWZ8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi32>> - Complexity = 13
                // Dst: (LWZ8:i64 iaddr:iPTR:$src)
/*3552*/      /*Scope*/ 15, /*->3568*/
/*3553*/        OPC_CheckPredicate, 4, // Predicate_zextloadi8
/*3555*/        OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3558*/        OPC_EmitMergeInputChains1_0,
/*3559*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LBZX8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi8>> - Complexity = 13
                // Dst: (LBZX8:i64 xaddr:iPTR:$src)
/*3568*/      /*Scope*/ 15, /*->3584*/
/*3569*/        OPC_CheckPredicate, 7, // Predicate_zextloadi16
/*3571*/        OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3574*/        OPC_EmitMergeInputChains1_0,
/*3575*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LHZX8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi16>> - Complexity = 13
                // Dst: (LHZX8:i64 xaddr:iPTR:$src)
/*3584*/      /*Scope*/ 15, /*->3600*/
/*3585*/        OPC_CheckPredicate, 15, // Predicate_zextloadi32
/*3587*/        OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3590*/        OPC_EmitMergeInputChains1_0,
/*3591*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LWZX8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi32>> - Complexity = 13
                // Dst: (LWZX8:i64 xaddr:iPTR:$src)
/*3600*/      0, /*End of Scope*/
/*3601*/    /*Scope*/ 34, /*->3636*/
/*3602*/      OPC_CheckPredicate, 8, // Predicate_load
/*3604*/      OPC_CheckType, MVT::i64,
/*3606*/      OPC_Scope, 13, /*->3621*/ // 2 children in Scope
/*3608*/        OPC_CheckComplexPat, /*CP*/3, /*#*/1, // SelectAddrImmShift:$src #2 #3
/*3611*/        OPC_EmitMergeInputChains1_0,
/*3612*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LD), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 ixaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_load>> - Complexity = 13
                // Dst: (LD:i64 ixaddr:iPTR:$src)
/*3621*/      /*Scope*/ 13, /*->3635*/
/*3622*/        OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3625*/        OPC_EmitMergeInputChains1_0,
/*3626*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LDX), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_load>> - Complexity = 13
                // Dst: (LDX:i64 xaddr:iPTR:$src)
/*3635*/      0, /*End of Scope*/
/*3636*/    /*Scope*/ 36, /*->3673*/
/*3637*/      OPC_CheckPredicate, 3, // Predicate_zextload
/*3639*/      OPC_CheckPredicate, 9, // Predicate_zextloadi1
/*3641*/      OPC_CheckType, MVT::i64,
/*3643*/      OPC_Scope, 13, /*->3658*/ // 2 children in Scope
/*3645*/        OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3648*/        OPC_EmitMergeInputChains1_0,
/*3649*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LBZ8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi1>> - Complexity = 13
                // Dst: (LBZ8:i64 iaddr:iPTR:$src)
/*3658*/      /*Scope*/ 13, /*->3672*/
/*3659*/        OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3662*/        OPC_EmitMergeInputChains1_0,
/*3663*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LBZX8), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_zextload>><<P:Predicate_zextloadi1>> - Complexity = 13
                // Dst: (LBZX8:i64 xaddr:iPTR:$src)
/*3672*/      0, /*End of Scope*/
/*3673*/    /*Scope*/ 10|128,1/*138*/, /*->3813*/
/*3675*/      OPC_CheckPredicate, 10, // Predicate_extload
/*3677*/      OPC_CheckType, MVT::i64,
/*3679*/      OPC_Scope, 32, /*->3713*/ // 4 children in Scope
/*3681*/        OPC_CheckPredicate, 11, // Predicate_extloadi1
/*3683*/        OPC_Scope, 13, /*->3698*/ // 2 children in Scope
/*3685*/          OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3688*/          OPC_EmitMergeInputChains1_0,
/*3689*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LBZ8), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi1>> - Complexity = 13
                  // Dst: (LBZ8:i64 iaddr:iPTR:$src)
/*3698*/        /*Scope*/ 13, /*->3712*/
/*3699*/          OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3702*/          OPC_EmitMergeInputChains1_0,
/*3703*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LBZX8), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi1>> - Complexity = 13
                  // Dst: (LBZX8:i64 xaddr:iPTR:$src)
/*3712*/        0, /*End of Scope*/
/*3713*/      /*Scope*/ 32, /*->3746*/
/*3714*/        OPC_CheckPredicate, 12, // Predicate_extloadi8
/*3716*/        OPC_Scope, 13, /*->3731*/ // 2 children in Scope
/*3718*/          OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3721*/          OPC_EmitMergeInputChains1_0,
/*3722*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LBZ8), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi8>> - Complexity = 13
                  // Dst: (LBZ8:i64 iaddr:iPTR:$src)
/*3731*/        /*Scope*/ 13, /*->3745*/
/*3732*/          OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3735*/          OPC_EmitMergeInputChains1_0,
/*3736*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LBZX8), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi8>> - Complexity = 13
                  // Dst: (LBZX8:i64 xaddr:iPTR:$src)
/*3745*/        0, /*End of Scope*/
/*3746*/      /*Scope*/ 32, /*->3779*/
/*3747*/        OPC_CheckPredicate, 13, // Predicate_extloadi16
/*3749*/        OPC_Scope, 13, /*->3764*/ // 2 children in Scope
/*3751*/          OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3754*/          OPC_EmitMergeInputChains1_0,
/*3755*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LHZ8), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi16>> - Complexity = 13
                  // Dst: (LHZ8:i64 iaddr:iPTR:$src)
/*3764*/        /*Scope*/ 13, /*->3778*/
/*3765*/          OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3768*/          OPC_EmitMergeInputChains1_0,
/*3769*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LHZX8), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi16>> - Complexity = 13
                  // Dst: (LHZX8:i64 xaddr:iPTR:$src)
/*3778*/        0, /*End of Scope*/
/*3779*/      /*Scope*/ 32, /*->3812*/
/*3780*/        OPC_CheckPredicate, 16, // Predicate_extloadi32
/*3782*/        OPC_Scope, 13, /*->3797*/ // 2 children in Scope
/*3784*/          OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3787*/          OPC_EmitMergeInputChains1_0,
/*3788*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LWZ8), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi32>> - Complexity = 13
                  // Dst: (LWZ8:i64 iaddr:iPTR:$src)
/*3797*/        /*Scope*/ 13, /*->3811*/
/*3798*/          OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3801*/          OPC_EmitMergeInputChains1_0,
/*3802*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LWZX8), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:i64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadi32>> - Complexity = 13
                  // Dst: (LWZX8:i64 xaddr:iPTR:$src)
/*3811*/        0, /*End of Scope*/
/*3812*/      0, /*End of Scope*/
/*3813*/    /*Scope*/ 68, /*->3882*/
/*3814*/      OPC_CheckPredicate, 8, // Predicate_load
/*3816*/      OPC_SwitchType /*2 cases */, 30,  MVT::f32,// ->3849
/*3819*/        OPC_Scope, 13, /*->3834*/ // 2 children in Scope
/*3821*/          OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3824*/          OPC_EmitMergeInputChains1_0,
/*3825*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LFS), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::f32, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:f32 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_load>> - Complexity = 13
                  // Dst: (LFS:f32 iaddr:iPTR:$src)
/*3834*/        /*Scope*/ 13, /*->3848*/
/*3835*/          OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3838*/          OPC_EmitMergeInputChains1_0,
/*3839*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LFSX), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::f32, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:f32 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_load>> - Complexity = 13
                  // Dst: (LFSX:f32 xaddr:iPTR:$src)
/*3848*/        0, /*End of Scope*/
              /*SwitchType*/ 30,  MVT::f64,// ->3881
/*3851*/        OPC_Scope, 13, /*->3866*/ // 2 children in Scope
/*3853*/          OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3856*/          OPC_EmitMergeInputChains1_0,
/*3857*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LFD), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::f64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:f64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_load>> - Complexity = 13
                  // Dst: (LFD:f64 iaddr:iPTR:$src)
/*3866*/        /*Scope*/ 13, /*->3880*/
/*3867*/          OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3870*/          OPC_EmitMergeInputChains1_0,
/*3871*/          OPC_MorphNodeTo, TARGET_VAL(PPC::LFDX), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::f64, 2/*#Ops*/, 2, 3, 
                  // Src: (ld:f64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_load>> - Complexity = 13
                  // Dst: (LFDX:f64 xaddr:iPTR:$src)
/*3880*/        0, /*End of Scope*/
              0, // EndSwitchType
/*3882*/    /*Scope*/ 60, /*->3943*/
/*3883*/      OPC_CheckPredicate, 10, // Predicate_extload
/*3885*/      OPC_CheckPredicate, 17, // Predicate_extloadf32
/*3887*/      OPC_CheckType, MVT::f64,
/*3889*/      OPC_Scope, 25, /*->3916*/ // 2 children in Scope
/*3891*/        OPC_CheckComplexPat, /*CP*/1, /*#*/1, // SelectAddrImm:$src #2 #3
/*3894*/        OPC_EmitMergeInputChains1_0,
/*3895*/        OPC_EmitNode, TARGET_VAL(PPC::LFS), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::f32, 2/*#Ops*/, 2, 3,  // Results = #4
/*3904*/        OPC_EmitInteger, MVT::i32, PPC::F8RCRegClassID,
/*3907*/        OPC_MorphNodeTo, TARGET_VAL(TargetOpcode::COPY_TO_REGCLASS), 0|OPFL_Chain,
                    1/*#VTs*/, MVT::f64, 2/*#Ops*/, 4, 5, 
                // Src: (ld:f64 iaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadf32>> - Complexity = 13
                // Dst: (COPY_TO_REGCLASS:f64 (LFS:f32 iaddr:iPTR:$src), F8RC:f64)
/*3916*/      /*Scope*/ 25, /*->3942*/
/*3917*/        OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*3920*/        OPC_EmitMergeInputChains1_0,
/*3921*/        OPC_EmitNode, TARGET_VAL(PPC::LFSX), 0|OPFL_Chain|OPFL_MemRefs,
                    1/*#VTs*/, MVT::f32, 2/*#Ops*/, 2, 3,  // Results = #4
/*3930*/        OPC_EmitInteger, MVT::i32, PPC::F8RCRegClassID,
/*3933*/        OPC_MorphNodeTo, TARGET_VAL(TargetOpcode::COPY_TO_REGCLASS), 0|OPFL_Chain,
                    1/*#VTs*/, MVT::f64, 2/*#Ops*/, 4, 5, 
                // Src: (ld:f64 xaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_extload>><<P:Predicate_extloadf32>> - Complexity = 13
                // Dst: (COPY_TO_REGCLASS:f64 (LFSX:f32 xaddr:iPTR:$src), F8RC:f64)
/*3942*/      0, /*End of Scope*/
/*3943*/    /*Scope*/ 17, /*->3961*/
/*3944*/      OPC_CheckPredicate, 8, // Predicate_load
/*3946*/      OPC_CheckType, MVT::v4i32,
/*3948*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$src #2 #3
/*3951*/      OPC_EmitMergeInputChains1_0,
/*3952*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LVX), 0|OPFL_Chain|OPFL_MemRefs,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 2, 3, 
              // Src: (ld:v4i32 xoaddr:iPTR:$src)<<P:Predicate_unindexedload>><<P:Predicate_load>> - Complexity = 13
              // Dst: (LVX:v4i32 xoaddr:iPTR:$src)
/*3961*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 92|128,5/*732*/,  TARGET_VAL(ISD::STORE),// ->4698
/*3966*/    OPC_RecordMemRef,
/*3967*/    OPC_RecordNode,   // #0 = 'st' chained node
/*3968*/    OPC_RecordChild1, // #1 = $rS
/*3969*/    OPC_Scope, 112|128,1/*240*/, /*->4212*/ // 5 children in Scope
/*3972*/      OPC_CheckChild1Type, MVT::i32,
/*3974*/      OPC_RecordChild2, // #2 = $src
/*3975*/      OPC_Scope, 110, /*->4087*/ // 2 children in Scope
/*3977*/        OPC_CheckPredicate, 18, // Predicate_unindexedstore
/*3979*/        OPC_Scope, 36, /*->4017*/ // 4 children in Scope
/*3981*/          OPC_CheckPredicate, 19, // Predicate_truncstore
/*3983*/          OPC_Scope, 15, /*->4000*/ // 2 children in Scope
/*3985*/            OPC_CheckPredicate, 20, // Predicate_truncstorei8
/*3987*/            OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$src #3 #4
/*3990*/            OPC_EmitMergeInputChains1_0,
/*3991*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STB), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st GPRC:i32:$rS, iaddr:iPTR:$src)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei8>> - Complexity = 13
                    // Dst: (STB GPRC:i32:$rS, iaddr:iPTR:$src)
/*4000*/          /*Scope*/ 15, /*->4016*/
/*4001*/            OPC_CheckPredicate, 21, // Predicate_truncstorei16
/*4003*/            OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$src #3 #4
/*4006*/            OPC_EmitMergeInputChains1_0,
/*4007*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STH), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st GPRC:i32:$rS, iaddr:iPTR:$src)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei16>> - Complexity = 13
                    // Dst: (STH GPRC:i32:$rS, iaddr:iPTR:$src)
/*4016*/          0, /*End of Scope*/
/*4017*/        /*Scope*/ 15, /*->4033*/
/*4018*/          OPC_CheckPredicate, 22, // Predicate_store
/*4020*/          OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$src #3 #4
/*4023*/          OPC_EmitMergeInputChains1_0,
/*4024*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STW), 0|OPFL_Chain|OPFL_MemRefs,
                      0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                  // Src: (st GPRC:i32:$rS, iaddr:iPTR:$src)<<P:Predicate_unindexedstore>><<P:Predicate_store>> - Complexity = 13
                  // Dst: (STW GPRC:i32:$rS, iaddr:iPTR:$src)
/*4033*/        /*Scope*/ 36, /*->4070*/
/*4034*/          OPC_CheckPredicate, 19, // Predicate_truncstore
/*4036*/          OPC_Scope, 15, /*->4053*/ // 2 children in Scope
/*4038*/            OPC_CheckPredicate, 20, // Predicate_truncstorei8
/*4040*/            OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*4043*/            OPC_EmitMergeInputChains1_0,
/*4044*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STBX), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st GPRC:i32:$rS, xaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei8>> - Complexity = 13
                    // Dst: (STBX GPRC:i32:$rS, xaddr:iPTR:$dst)
/*4053*/          /*Scope*/ 15, /*->4069*/
/*4054*/            OPC_CheckPredicate, 21, // Predicate_truncstorei16
/*4056*/            OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*4059*/            OPC_EmitMergeInputChains1_0,
/*4060*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STHX), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st GPRC:i32:$rS, xaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei16>> - Complexity = 13
                    // Dst: (STHX GPRC:i32:$rS, xaddr:iPTR:$dst)
/*4069*/          0, /*End of Scope*/
/*4070*/        /*Scope*/ 15, /*->4086*/
/*4071*/          OPC_CheckPredicate, 22, // Predicate_store
/*4073*/          OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*4076*/          OPC_EmitMergeInputChains1_0,
/*4077*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STWX), 0|OPFL_Chain|OPFL_MemRefs,
                      0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                  // Src: (st GPRC:i32:$rS, xaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_store>> - Complexity = 13
                  // Dst: (STWX GPRC:i32:$rS, xaddr:iPTR:$dst)
/*4086*/        0, /*End of Scope*/
/*4087*/      /*Scope*/ 123, /*->4211*/
/*4088*/        OPC_RecordChild3, // #3 = $ptroff
/*4089*/        OPC_Scope, 40, /*->4131*/ // 4 children in Scope
/*4091*/          OPC_CheckPredicate, 23, // Predicate_itruncstore
/*4093*/          OPC_CheckPredicate, 24, // Predicate_pre_truncst
/*4095*/          OPC_Scope, 16, /*->4113*/ // 2 children in Scope
/*4097*/            OPC_CheckPredicate, 25, // Predicate_pre_truncsti8
/*4099*/            OPC_CheckComplexPat, /*CP*/4, /*#*/3, // SelectAddrImmOffs:$ptroff #4
/*4102*/            OPC_EmitMergeInputChains1_0,
/*4103*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STBU), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR GPRC:i32:$rS, ptr_rc:iPTR:$ptrreg, iaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti8>> - Complexity = 10
                    // Dst: (STBU:iPTR GPRC:i32:$rS, iaddroff:i32:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4113*/          /*Scope*/ 16, /*->4130*/
/*4114*/            OPC_CheckPredicate, 26, // Predicate_pre_truncsti16
/*4116*/            OPC_CheckComplexPat, /*CP*/4, /*#*/3, // SelectAddrImmOffs:$ptroff #4
/*4119*/            OPC_EmitMergeInputChains1_0,
/*4120*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STHU), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR GPRC:i32:$rS, ptr_rc:iPTR:$ptrreg, iaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti16>> - Complexity = 10
                    // Dst: (STHU:iPTR GPRC:i32:$rS, iaddroff:i32:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4130*/          0, /*End of Scope*/
/*4131*/        /*Scope*/ 18, /*->4150*/
/*4132*/          OPC_CheckPredicate, 27, // Predicate_istore
/*4134*/          OPC_CheckPredicate, 28, // Predicate_pre_store
/*4136*/          OPC_CheckComplexPat, /*CP*/4, /*#*/3, // SelectAddrImmOffs:$ptroff #4
/*4139*/          OPC_EmitMergeInputChains1_0,
/*4140*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STWU), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                  // Src: (ist:iPTR GPRC:i32:$rS, ptr_rc:iPTR:$ptrreg, iaddroff:iPTR:$ptroff)<<P:Predicate_istore>><<P:Predicate_pre_store>> - Complexity = 10
                  // Dst: (STWU:iPTR GPRC:i32:$rS, iaddroff:i32:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4150*/        /*Scope*/ 40, /*->4191*/
/*4151*/          OPC_CheckPredicate, 23, // Predicate_itruncstore
/*4153*/          OPC_CheckPredicate, 24, // Predicate_pre_truncst
/*4155*/          OPC_Scope, 16, /*->4173*/ // 2 children in Scope
/*4157*/            OPC_CheckPredicate, 25, // Predicate_pre_truncsti8
/*4159*/            OPC_CheckComplexPat, /*CP*/5, /*#*/3, // SelectAddrIdxOffs:$ptroff #4
/*4162*/            OPC_EmitMergeInputChains1_0,
/*4163*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STBUX), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR GPRC:i32:$rS, ptr_rc:iPTR:$ptrreg, xaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti8>> - Complexity = 10
                    // Dst: (STBUX:iPTR GPRC:i32:$rS, xaddroff:iPTR:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4173*/          /*Scope*/ 16, /*->4190*/
/*4174*/            OPC_CheckPredicate, 26, // Predicate_pre_truncsti16
/*4176*/            OPC_CheckComplexPat, /*CP*/5, /*#*/3, // SelectAddrIdxOffs:$ptroff #4
/*4179*/            OPC_EmitMergeInputChains1_0,
/*4180*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STHUX), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR GPRC:i32:$rS, ptr_rc:iPTR:$ptrreg, xaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti16>> - Complexity = 10
                    // Dst: (STHUX:iPTR GPRC:i32:$rS, xaddroff:iPTR:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4190*/          0, /*End of Scope*/
/*4191*/        /*Scope*/ 18, /*->4210*/
/*4192*/          OPC_CheckPredicate, 27, // Predicate_istore
/*4194*/          OPC_CheckPredicate, 28, // Predicate_pre_store
/*4196*/          OPC_CheckComplexPat, /*CP*/5, /*#*/3, // SelectAddrIdxOffs:$ptroff #4
/*4199*/          OPC_EmitMergeInputChains1_0,
/*4200*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STWUX), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                  // Src: (ist:iPTR GPRC:i32:$rS, ptr_rc:iPTR:$ptrreg, xaddroff:iPTR:$ptroff)<<P:Predicate_istore>><<P:Predicate_pre_store>> - Complexity = 10
                  // Dst: (STWUX:iPTR GPRC:i32:$rS, xaddroff:iPTR:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4210*/        0, /*End of Scope*/
/*4211*/      0, /*End of Scope*/
/*4212*/    /*Scope*/ 78, /*->4291*/
/*4213*/      OPC_CheckChild1Type, MVT::f32,
/*4215*/      OPC_RecordChild2, // #2 = $dst
/*4216*/      OPC_Scope, 34, /*->4252*/ // 2 children in Scope
/*4218*/        OPC_CheckPredicate, 18, // Predicate_unindexedstore
/*4220*/        OPC_CheckPredicate, 22, // Predicate_store
/*4222*/        OPC_Scope, 13, /*->4237*/ // 2 children in Scope
/*4224*/          OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$dst #3 #4
/*4227*/          OPC_EmitMergeInputChains1_0,
/*4228*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STFS), 0|OPFL_Chain|OPFL_MemRefs,
                      0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                  // Src: (st F4RC:f32:$rS, iaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_store>> - Complexity = 13
                  // Dst: (STFS F4RC:f32:$rS, iaddr:iPTR:$dst)
/*4237*/        /*Scope*/ 13, /*->4251*/
/*4238*/          OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*4241*/          OPC_EmitMergeInputChains1_0,
/*4242*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STFSX), 0|OPFL_Chain|OPFL_MemRefs,
                      0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                  // Src: (st F4RC:f32:$frS, xaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_store>> - Complexity = 13
                  // Dst: (STFSX F4RC:f32:$frS, xaddr:iPTR:$dst)
/*4251*/        0, /*End of Scope*/
/*4252*/      /*Scope*/ 37, /*->4290*/
/*4253*/        OPC_RecordChild3, // #3 = $ptroff
/*4254*/        OPC_CheckPredicate, 27, // Predicate_istore
/*4256*/        OPC_CheckPredicate, 28, // Predicate_pre_store
/*4258*/        OPC_Scope, 14, /*->4274*/ // 2 children in Scope
/*4260*/          OPC_CheckComplexPat, /*CP*/4, /*#*/3, // SelectAddrImmOffs:$ptroff #4
/*4263*/          OPC_EmitMergeInputChains1_0,
/*4264*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STFSU), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                  // Src: (ist:iPTR F4RC:f32:$rS, ptr_rc:iPTR:$ptrreg, iaddroff:iPTR:$ptroff)<<P:Predicate_istore>><<P:Predicate_pre_store>> - Complexity = 10
                  // Dst: (STFSU:iPTR F4RC:f32:$rS, iaddroff:i32:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4274*/        /*Scope*/ 14, /*->4289*/
/*4275*/          OPC_CheckComplexPat, /*CP*/5, /*#*/3, // SelectAddrIdxOffs:$ptroff #4
/*4278*/          OPC_EmitMergeInputChains1_0,
/*4279*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STFSUX), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                  // Src: (ist:iPTR F4RC:f32:$rS, ptr_rc:iPTR:$ptrreg, xaddroff:iPTR:$ptroff)<<P:Predicate_istore>><<P:Predicate_pre_store>> - Complexity = 10
                  // Dst: (STFSUX:iPTR F4RC:f32:$rS, xaddroff:iPTR:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4289*/        0, /*End of Scope*/
/*4290*/      0, /*End of Scope*/
/*4291*/    /*Scope*/ 78, /*->4370*/
/*4292*/      OPC_CheckChild1Type, MVT::f64,
/*4294*/      OPC_RecordChild2, // #2 = $dst
/*4295*/      OPC_Scope, 34, /*->4331*/ // 2 children in Scope
/*4297*/        OPC_CheckPredicate, 18, // Predicate_unindexedstore
/*4299*/        OPC_CheckPredicate, 22, // Predicate_store
/*4301*/        OPC_Scope, 13, /*->4316*/ // 2 children in Scope
/*4303*/          OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$dst #3 #4
/*4306*/          OPC_EmitMergeInputChains1_0,
/*4307*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STFD), 0|OPFL_Chain|OPFL_MemRefs,
                      0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                  // Src: (st F8RC:f64:$rS, iaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_store>> - Complexity = 13
                  // Dst: (STFD F8RC:f64:$rS, iaddr:iPTR:$dst)
/*4316*/        /*Scope*/ 13, /*->4330*/
/*4317*/          OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*4320*/          OPC_EmitMergeInputChains1_0,
/*4321*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STFDX), 0|OPFL_Chain|OPFL_MemRefs,
                      0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                  // Src: (st F8RC:f64:$frS, xaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_store>> - Complexity = 13
                  // Dst: (STFDX F8RC:f64:$frS, xaddr:iPTR:$dst)
/*4330*/        0, /*End of Scope*/
/*4331*/      /*Scope*/ 37, /*->4369*/
/*4332*/        OPC_RecordChild3, // #3 = $ptroff
/*4333*/        OPC_CheckPredicate, 27, // Predicate_istore
/*4335*/        OPC_CheckPredicate, 28, // Predicate_pre_store
/*4337*/        OPC_Scope, 14, /*->4353*/ // 2 children in Scope
/*4339*/          OPC_CheckComplexPat, /*CP*/4, /*#*/3, // SelectAddrImmOffs:$ptroff #4
/*4342*/          OPC_EmitMergeInputChains1_0,
/*4343*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STFDU), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                  // Src: (ist:iPTR F8RC:f64:$rS, ptr_rc:iPTR:$ptrreg, iaddroff:iPTR:$ptroff)<<P:Predicate_istore>><<P:Predicate_pre_store>> - Complexity = 10
                  // Dst: (STFDU:iPTR F8RC:f64:$rS, iaddroff:i32:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4353*/        /*Scope*/ 14, /*->4368*/
/*4354*/          OPC_CheckComplexPat, /*CP*/5, /*#*/3, // SelectAddrIdxOffs:$ptroff #4
/*4357*/          OPC_EmitMergeInputChains1_0,
/*4358*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STFDUX), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                  // Src: (ist:iPTR F8RC:f64:$rS, ptr_rc:iPTR:$ptrreg, xaddroff:iPTR:$ptroff)<<P:Predicate_istore>><<P:Predicate_pre_store>> - Complexity = 10
                  // Dst: (STFDUX:iPTR F8RC:f64:$rS, xaddroff:iPTR:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4368*/        0, /*End of Scope*/
/*4369*/      0, /*End of Scope*/
/*4370*/    /*Scope*/ 20, /*->4391*/
/*4371*/      OPC_CheckChild1Type, MVT::v4i32,
/*4373*/      OPC_RecordChild2, // #2 = $dst
/*4374*/      OPC_CheckPredicate, 18, // Predicate_unindexedstore
/*4376*/      OPC_CheckPredicate, 22, // Predicate_store
/*4378*/      OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*4381*/      OPC_EmitMergeInputChains1_0,
/*4382*/      OPC_MorphNodeTo, TARGET_VAL(PPC::STVX), 0|OPFL_Chain|OPFL_MemRefs,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (st VRRC:v4i32:$rS, xoaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_store>> - Complexity = 13
              // Dst: (STVX VRRC:v4i32:$rS, xoaddr:iPTR:$dst)
/*4391*/    /*Scope*/ 48|128,2/*304*/, /*->4697*/
/*4393*/      OPC_CheckChild1Type, MVT::i64,
/*4395*/      OPC_RecordChild2, // #2 = $src
/*4396*/      OPC_Scope, 10|128,1/*138*/, /*->4537*/ // 2 children in Scope
/*4399*/        OPC_CheckPredicate, 18, // Predicate_unindexedstore
/*4401*/        OPC_Scope, 100, /*->4503*/ // 2 children in Scope
/*4403*/          OPC_CheckPredicate, 19, // Predicate_truncstore
/*4405*/          OPC_Scope, 15, /*->4422*/ // 6 children in Scope
/*4407*/            OPC_CheckPredicate, 20, // Predicate_truncstorei8
/*4409*/            OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$src #3 #4
/*4412*/            OPC_EmitMergeInputChains1_0,
/*4413*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STB8), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st G8RC:i64:$rS, iaddr:iPTR:$src)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei8>> - Complexity = 13
                    // Dst: (STB8 G8RC:i64:$rS, iaddr:iPTR:$src)
/*4422*/          /*Scope*/ 15, /*->4438*/
/*4423*/            OPC_CheckPredicate, 21, // Predicate_truncstorei16
/*4425*/            OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$src #3 #4
/*4428*/            OPC_EmitMergeInputChains1_0,
/*4429*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STH8), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st G8RC:i64:$rS, iaddr:iPTR:$src)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei16>> - Complexity = 13
                    // Dst: (STH8 G8RC:i64:$rS, iaddr:iPTR:$src)
/*4438*/          /*Scope*/ 15, /*->4454*/
/*4439*/            OPC_CheckPredicate, 29, // Predicate_truncstorei32
/*4441*/            OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$src #3 #4
/*4444*/            OPC_EmitMergeInputChains1_0,
/*4445*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STW8), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st G8RC:i64:$rS, iaddr:iPTR:$src)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei32>> - Complexity = 13
                    // Dst: (STW8 G8RC:i64:$rS, iaddr:iPTR:$src)
/*4454*/          /*Scope*/ 15, /*->4470*/
/*4455*/            OPC_CheckPredicate, 20, // Predicate_truncstorei8
/*4457*/            OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*4460*/            OPC_EmitMergeInputChains1_0,
/*4461*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STBX8), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st G8RC:i64:$rS, xaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei8>> - Complexity = 13
                    // Dst: (STBX8 G8RC:i64:$rS, xaddr:iPTR:$dst)
/*4470*/          /*Scope*/ 15, /*->4486*/
/*4471*/            OPC_CheckPredicate, 21, // Predicate_truncstorei16
/*4473*/            OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*4476*/            OPC_EmitMergeInputChains1_0,
/*4477*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STHX8), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st G8RC:i64:$rS, xaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei16>> - Complexity = 13
                    // Dst: (STHX8 G8RC:i64:$rS, xaddr:iPTR:$dst)
/*4486*/          /*Scope*/ 15, /*->4502*/
/*4487*/            OPC_CheckPredicate, 29, // Predicate_truncstorei32
/*4489*/            OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*4492*/            OPC_EmitMergeInputChains1_0,
/*4493*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STWX8), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st G8RC:i64:$rS, xaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_truncstore>><<P:Predicate_truncstorei32>> - Complexity = 13
                    // Dst: (STWX8 G8RC:i64:$rS, xaddr:iPTR:$dst)
/*4502*/          0, /*End of Scope*/
/*4503*/        /*Scope*/ 32, /*->4536*/
/*4504*/          OPC_CheckPredicate, 22, // Predicate_store
/*4506*/          OPC_Scope, 13, /*->4521*/ // 2 children in Scope
/*4508*/            OPC_CheckComplexPat, /*CP*/3, /*#*/2, // SelectAddrImmShift:$dst #3 #4
/*4511*/            OPC_EmitMergeInputChains1_0,
/*4512*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STD), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st G8RC:i64:$rS, ixaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_store>> - Complexity = 13
                    // Dst: (STD G8RC:i64:$rS, ixaddr:iPTR:$dst)
/*4521*/          /*Scope*/ 13, /*->4535*/
/*4522*/            OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*4525*/            OPC_EmitMergeInputChains1_0,
/*4526*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STDX), 0|OPFL_Chain|OPFL_MemRefs,
                        0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
                    // Src: (st G8RC:i64:$rS, xaddr:iPTR:$dst)<<P:Predicate_unindexedstore>><<P:Predicate_store>> - Complexity = 13
                    // Dst: (STDX G8RC:i64:$rS, xaddr:iPTR:$dst)
/*4535*/          0, /*End of Scope*/
/*4536*/        0, /*End of Scope*/
/*4537*/      /*Scope*/ 29|128,1/*157*/, /*->4696*/
/*4539*/        OPC_RecordChild3, // #3 = $ptroff
/*4540*/        OPC_Scope, 57, /*->4599*/ // 4 children in Scope
/*4542*/          OPC_CheckPredicate, 23, // Predicate_itruncstore
/*4544*/          OPC_CheckPredicate, 24, // Predicate_pre_truncst
/*4546*/          OPC_Scope, 16, /*->4564*/ // 3 children in Scope
/*4548*/            OPC_CheckPredicate, 25, // Predicate_pre_truncsti8
/*4550*/            OPC_CheckComplexPat, /*CP*/4, /*#*/3, // SelectAddrImmOffs:$ptroff #4
/*4553*/            OPC_EmitMergeInputChains1_0,
/*4554*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STBU8), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR G8RC:i64:$rS, ptr_rc:iPTR:$ptrreg, iaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti8>> - Complexity = 10
                    // Dst: (STBU8:iPTR G8RC:i64:$rS, iaddroff:i32:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4564*/          /*Scope*/ 16, /*->4581*/
/*4565*/            OPC_CheckPredicate, 26, // Predicate_pre_truncsti16
/*4567*/            OPC_CheckComplexPat, /*CP*/4, /*#*/3, // SelectAddrImmOffs:$ptroff #4
/*4570*/            OPC_EmitMergeInputChains1_0,
/*4571*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STHU8), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR G8RC:i64:$rS, ptr_rc:iPTR:$ptrreg, iaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti16>> - Complexity = 10
                    // Dst: (STHU8:iPTR G8RC:i64:$rS, iaddroff:i32:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4581*/          /*Scope*/ 16, /*->4598*/
/*4582*/            OPC_CheckPredicate, 30, // Predicate_pre_truncsti32
/*4584*/            OPC_CheckComplexPat, /*CP*/4, /*#*/3, // SelectAddrImmOffs:$ptroff #4
/*4587*/            OPC_EmitMergeInputChains1_0,
/*4588*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STWU8), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR G8RC:i64:$rS, ptr_rc:iPTR:$ptrreg, iaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti32>> - Complexity = 10
                    // Dst: (STWU8:iPTR G8RC:i64:$rS, iaddroff:i32:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4598*/          0, /*End of Scope*/
/*4599*/        /*Scope*/ 18, /*->4618*/
/*4600*/          OPC_CheckPredicate, 27, // Predicate_istore
/*4602*/          OPC_CheckPredicate, 28, // Predicate_pre_store
/*4604*/          OPC_CheckComplexPat, /*CP*/4, /*#*/3, // SelectAddrImmOffs:$ptroff #4
/*4607*/          OPC_EmitMergeInputChains1_0,
/*4608*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STDU), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                  // Src: (ist:iPTR G8RC:i64:$rS, ptr_rc:iPTR:$ptrreg, iaddroff:iPTR:$ptroff)<<P:Predicate_istore>><<P:Predicate_pre_store>> - Complexity = 10
                  // Dst: (STDU:iPTR G8RC:i64:$rS, iaddroff:i32:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4618*/        /*Scope*/ 57, /*->4676*/
/*4619*/          OPC_CheckPredicate, 23, // Predicate_itruncstore
/*4621*/          OPC_CheckPredicate, 24, // Predicate_pre_truncst
/*4623*/          OPC_Scope, 16, /*->4641*/ // 3 children in Scope
/*4625*/            OPC_CheckPredicate, 25, // Predicate_pre_truncsti8
/*4627*/            OPC_CheckComplexPat, /*CP*/5, /*#*/3, // SelectAddrIdxOffs:$ptroff #4
/*4630*/            OPC_EmitMergeInputChains1_0,
/*4631*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STBUX8), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR G8RC:i64:$rS, ptr_rc:iPTR:$ptrreg, xaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti8>> - Complexity = 10
                    // Dst: (STBUX8:iPTR G8RC:i64:$rS, xaddroff:iPTR:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4641*/          /*Scope*/ 16, /*->4658*/
/*4642*/            OPC_CheckPredicate, 26, // Predicate_pre_truncsti16
/*4644*/            OPC_CheckComplexPat, /*CP*/5, /*#*/3, // SelectAddrIdxOffs:$ptroff #4
/*4647*/            OPC_EmitMergeInputChains1_0,
/*4648*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STHUX8), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR G8RC:i64:$rS, ptr_rc:iPTR:$ptrreg, xaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti16>> - Complexity = 10
                    // Dst: (STHUX8:iPTR G8RC:i64:$rS, xaddroff:iPTR:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4658*/          /*Scope*/ 16, /*->4675*/
/*4659*/            OPC_CheckPredicate, 30, // Predicate_pre_truncsti32
/*4661*/            OPC_CheckComplexPat, /*CP*/5, /*#*/3, // SelectAddrIdxOffs:$ptroff #4
/*4664*/            OPC_EmitMergeInputChains1_0,
/*4665*/            OPC_MorphNodeTo, TARGET_VAL(PPC::STWUX8), 0|OPFL_Chain|OPFL_MemRefs,
                        1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                    // Src: (ist:iPTR G8RC:i64:$rS, ptr_rc:iPTR:$ptrreg, xaddroff:iPTR:$ptroff)<<P:Predicate_itruncstore>><<P:Predicate_pre_truncst>><<P:Predicate_pre_truncsti32>> - Complexity = 10
                    // Dst: (STWUX8:iPTR G8RC:i64:$rS, xaddroff:iPTR:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4675*/          0, /*End of Scope*/
/*4676*/        /*Scope*/ 18, /*->4695*/
/*4677*/          OPC_CheckPredicate, 27, // Predicate_istore
/*4679*/          OPC_CheckPredicate, 28, // Predicate_pre_store
/*4681*/          OPC_CheckComplexPat, /*CP*/5, /*#*/3, // SelectAddrIdxOffs:$ptroff #4
/*4684*/          OPC_EmitMergeInputChains1_0,
/*4685*/          OPC_MorphNodeTo, TARGET_VAL(PPC::STDUX), 0|OPFL_Chain|OPFL_MemRefs,
                      1/*#VTs*/, MVT::iPTR, 3/*#Ops*/, 1, 4, 2, 
                  // Src: (ist:iPTR G8RC:i64:$rS, ptr_rc:iPTR:$ptrreg, xaddroff:iPTR:$ptroff)<<P:Predicate_istore>><<P:Predicate_pre_store>> - Complexity = 10
                  // Dst: (STDUX:iPTR G8RC:i64:$rS, xaddroff:iPTR:$ptroff, ptr_rc:iPTR:$ptrreg)
/*4695*/        0, /*End of Scope*/
/*4696*/      0, /*End of Scope*/
/*4697*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 83,  TARGET_VAL(ISD::ATOMIC_LOAD_ADD),// ->4784
/*4701*/    OPC_RecordMemRef,
/*4702*/    OPC_RecordNode,   // #0 = 'atomic_load_add' chained node
/*4703*/    OPC_RecordChild1, // #1 = $ptr
/*4704*/    OPC_RecordChild2, // #2 = $incr
/*4705*/    OPC_SwitchType /*2 cases */, 56,  MVT::i32,// ->4764
/*4708*/      OPC_Scope, 17, /*->4727*/ // 3 children in Scope
/*4710*/        OPC_CheckPredicate, 31, // Predicate_atomic_load_add_8
/*4712*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4715*/        OPC_EmitMergeInputChains1_0,
/*4716*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_ADD_I8), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_add:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_add_8>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_ADD_I8:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4727*/      /*Scope*/ 17, /*->4745*/
/*4728*/        OPC_CheckPredicate, 32, // Predicate_atomic_load_add_16
/*4730*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4733*/        OPC_EmitMergeInputChains1_0,
/*4734*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_ADD_I16), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_add:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_add_16>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_ADD_I16:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4745*/      /*Scope*/ 17, /*->4763*/
/*4746*/        OPC_CheckPredicate, 33, // Predicate_atomic_load_add_32
/*4748*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4751*/        OPC_EmitMergeInputChains1_0,
/*4752*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_ADD_I32), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_add:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_add_32>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_ADD_I32:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4763*/      0, /*End of Scope*/
            /*SwitchType*/ 17,  MVT::i64,// ->4783
/*4766*/      OPC_CheckPredicate, 34, // Predicate_atomic_load_add_64
/*4768*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4771*/      OPC_EmitMergeInputChains1_0,
/*4772*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_ADD_I64), 0|OPFL_Chain|OPFL_MemRefs,
                  2/*#VTs*/, MVT::i64, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
              // Src: (atomic_load_add:i64 xoaddr:iPTR:$ptr, G8RC:i64:$incr)<<P:Predicate_atomic_load_add_64>> - Complexity = 13
              // Dst: (ATOMIC_LOAD_ADD_I64:i64:i32 xoaddr:iPTR:$ptr, G8RC:i64:$incr)
            0, // EndSwitchType
          /*SwitchOpcode*/ 83,  TARGET_VAL(ISD::ATOMIC_LOAD_SUB),// ->4870
/*4787*/    OPC_RecordMemRef,
/*4788*/    OPC_RecordNode,   // #0 = 'atomic_load_sub' chained node
/*4789*/    OPC_RecordChild1, // #1 = $ptr
/*4790*/    OPC_RecordChild2, // #2 = $incr
/*4791*/    OPC_SwitchType /*2 cases */, 56,  MVT::i32,// ->4850
/*4794*/      OPC_Scope, 17, /*->4813*/ // 3 children in Scope
/*4796*/        OPC_CheckPredicate, 35, // Predicate_atomic_load_sub_8
/*4798*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4801*/        OPC_EmitMergeInputChains1_0,
/*4802*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_SUB_I8), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_sub:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_sub_8>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_SUB_I8:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4813*/      /*Scope*/ 17, /*->4831*/
/*4814*/        OPC_CheckPredicate, 36, // Predicate_atomic_load_sub_16
/*4816*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4819*/        OPC_EmitMergeInputChains1_0,
/*4820*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_SUB_I16), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_sub:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_sub_16>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_SUB_I16:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4831*/      /*Scope*/ 17, /*->4849*/
/*4832*/        OPC_CheckPredicate, 37, // Predicate_atomic_load_sub_32
/*4834*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4837*/        OPC_EmitMergeInputChains1_0,
/*4838*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_SUB_I32), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_sub:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_sub_32>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_SUB_I32:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4849*/      0, /*End of Scope*/
            /*SwitchType*/ 17,  MVT::i64,// ->4869
/*4852*/      OPC_CheckPredicate, 38, // Predicate_atomic_load_sub_64
/*4854*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4857*/      OPC_EmitMergeInputChains1_0,
/*4858*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_SUB_I64), 0|OPFL_Chain|OPFL_MemRefs,
                  2/*#VTs*/, MVT::i64, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
              // Src: (atomic_load_sub:i64 xoaddr:iPTR:$ptr, G8RC:i64:$incr)<<P:Predicate_atomic_load_sub_64>> - Complexity = 13
              // Dst: (ATOMIC_LOAD_SUB_I64:i64:i32 xoaddr:iPTR:$ptr, G8RC:i64:$incr)
            0, // EndSwitchType
          /*SwitchOpcode*/ 83,  TARGET_VAL(ISD::ATOMIC_LOAD_AND),// ->4956
/*4873*/    OPC_RecordMemRef,
/*4874*/    OPC_RecordNode,   // #0 = 'atomic_load_and' chained node
/*4875*/    OPC_RecordChild1, // #1 = $ptr
/*4876*/    OPC_RecordChild2, // #2 = $incr
/*4877*/    OPC_SwitchType /*2 cases */, 56,  MVT::i32,// ->4936
/*4880*/      OPC_Scope, 17, /*->4899*/ // 3 children in Scope
/*4882*/        OPC_CheckPredicate, 39, // Predicate_atomic_load_and_8
/*4884*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4887*/        OPC_EmitMergeInputChains1_0,
/*4888*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_AND_I8), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_and:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_and_8>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_AND_I8:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4899*/      /*Scope*/ 17, /*->4917*/
/*4900*/        OPC_CheckPredicate, 40, // Predicate_atomic_load_and_16
/*4902*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4905*/        OPC_EmitMergeInputChains1_0,
/*4906*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_AND_I16), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_and:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_and_16>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_AND_I16:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4917*/      /*Scope*/ 17, /*->4935*/
/*4918*/        OPC_CheckPredicate, 41, // Predicate_atomic_load_and_32
/*4920*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4923*/        OPC_EmitMergeInputChains1_0,
/*4924*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_AND_I32), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_and:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_and_32>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_AND_I32:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4935*/      0, /*End of Scope*/
            /*SwitchType*/ 17,  MVT::i64,// ->4955
/*4938*/      OPC_CheckPredicate, 42, // Predicate_atomic_load_and_64
/*4940*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4943*/      OPC_EmitMergeInputChains1_0,
/*4944*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_AND_I64), 0|OPFL_Chain|OPFL_MemRefs,
                  2/*#VTs*/, MVT::i64, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
              // Src: (atomic_load_and:i64 xoaddr:iPTR:$ptr, G8RC:i64:$incr)<<P:Predicate_atomic_load_and_64>> - Complexity = 13
              // Dst: (ATOMIC_LOAD_AND_I64:i64:i32 xoaddr:iPTR:$ptr, G8RC:i64:$incr)
            0, // EndSwitchType
          /*SwitchOpcode*/ 83,  TARGET_VAL(ISD::ATOMIC_LOAD_OR),// ->5042
/*4959*/    OPC_RecordMemRef,
/*4960*/    OPC_RecordNode,   // #0 = 'atomic_load_or' chained node
/*4961*/    OPC_RecordChild1, // #1 = $ptr
/*4962*/    OPC_RecordChild2, // #2 = $incr
/*4963*/    OPC_SwitchType /*2 cases */, 56,  MVT::i32,// ->5022
/*4966*/      OPC_Scope, 17, /*->4985*/ // 3 children in Scope
/*4968*/        OPC_CheckPredicate, 43, // Predicate_atomic_load_or_8
/*4970*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4973*/        OPC_EmitMergeInputChains1_0,
/*4974*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_OR_I8), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_or:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_or_8>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_OR_I8:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*4985*/      /*Scope*/ 17, /*->5003*/
/*4986*/        OPC_CheckPredicate, 44, // Predicate_atomic_load_or_16
/*4988*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*4991*/        OPC_EmitMergeInputChains1_0,
/*4992*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_OR_I16), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_or:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_or_16>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_OR_I16:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*5003*/      /*Scope*/ 17, /*->5021*/
/*5004*/        OPC_CheckPredicate, 45, // Predicate_atomic_load_or_32
/*5006*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5009*/        OPC_EmitMergeInputChains1_0,
/*5010*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_OR_I32), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_or:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_or_32>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_OR_I32:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*5021*/      0, /*End of Scope*/
            /*SwitchType*/ 17,  MVT::i64,// ->5041
/*5024*/      OPC_CheckPredicate, 46, // Predicate_atomic_load_or_64
/*5026*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5029*/      OPC_EmitMergeInputChains1_0,
/*5030*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_OR_I64), 0|OPFL_Chain|OPFL_MemRefs,
                  2/*#VTs*/, MVT::i64, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
              // Src: (atomic_load_or:i64 xoaddr:iPTR:$ptr, G8RC:i64:$incr)<<P:Predicate_atomic_load_or_64>> - Complexity = 13
              // Dst: (ATOMIC_LOAD_OR_I64:i64:i32 xoaddr:iPTR:$ptr, G8RC:i64:$incr)
            0, // EndSwitchType
          /*SwitchOpcode*/ 83,  TARGET_VAL(ISD::ATOMIC_LOAD_XOR),// ->5128
/*5045*/    OPC_RecordMemRef,
/*5046*/    OPC_RecordNode,   // #0 = 'atomic_load_xor' chained node
/*5047*/    OPC_RecordChild1, // #1 = $ptr
/*5048*/    OPC_RecordChild2, // #2 = $incr
/*5049*/    OPC_SwitchType /*2 cases */, 56,  MVT::i32,// ->5108
/*5052*/      OPC_Scope, 17, /*->5071*/ // 3 children in Scope
/*5054*/        OPC_CheckPredicate, 47, // Predicate_atomic_load_xor_8
/*5056*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5059*/        OPC_EmitMergeInputChains1_0,
/*5060*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_XOR_I8), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_xor:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_xor_8>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_XOR_I8:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*5071*/      /*Scope*/ 17, /*->5089*/
/*5072*/        OPC_CheckPredicate, 48, // Predicate_atomic_load_xor_16
/*5074*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5077*/        OPC_EmitMergeInputChains1_0,
/*5078*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_XOR_I16), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_xor:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_xor_16>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_XOR_I16:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*5089*/      /*Scope*/ 17, /*->5107*/
/*5090*/        OPC_CheckPredicate, 49, // Predicate_atomic_load_xor_32
/*5092*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5095*/        OPC_EmitMergeInputChains1_0,
/*5096*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_XOR_I32), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_xor:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_xor_32>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_XOR_I32:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*5107*/      0, /*End of Scope*/
            /*SwitchType*/ 17,  MVT::i64,// ->5127
/*5110*/      OPC_CheckPredicate, 50, // Predicate_atomic_load_xor_64
/*5112*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5115*/      OPC_EmitMergeInputChains1_0,
/*5116*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_XOR_I64), 0|OPFL_Chain|OPFL_MemRefs,
                  2/*#VTs*/, MVT::i64, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
              // Src: (atomic_load_xor:i64 xoaddr:iPTR:$ptr, G8RC:i64:$incr)<<P:Predicate_atomic_load_xor_64>> - Complexity = 13
              // Dst: (ATOMIC_LOAD_XOR_I64:i64:i32 xoaddr:iPTR:$ptr, G8RC:i64:$incr)
            0, // EndSwitchType
          /*SwitchOpcode*/ 83,  TARGET_VAL(ISD::ATOMIC_LOAD_NAND),// ->5214
/*5131*/    OPC_RecordMemRef,
/*5132*/    OPC_RecordNode,   // #0 = 'atomic_load_nand' chained node
/*5133*/    OPC_RecordChild1, // #1 = $ptr
/*5134*/    OPC_RecordChild2, // #2 = $incr
/*5135*/    OPC_SwitchType /*2 cases */, 56,  MVT::i32,// ->5194
/*5138*/      OPC_Scope, 17, /*->5157*/ // 3 children in Scope
/*5140*/        OPC_CheckPredicate, 51, // Predicate_atomic_load_nand_8
/*5142*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5145*/        OPC_EmitMergeInputChains1_0,
/*5146*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_NAND_I8), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_nand:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_nand_8>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_NAND_I8:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*5157*/      /*Scope*/ 17, /*->5175*/
/*5158*/        OPC_CheckPredicate, 52, // Predicate_atomic_load_nand_16
/*5160*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5163*/        OPC_EmitMergeInputChains1_0,
/*5164*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_NAND_I16), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_nand:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_nand_16>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_NAND_I16:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*5175*/      /*Scope*/ 17, /*->5193*/
/*5176*/        OPC_CheckPredicate, 53, // Predicate_atomic_load_nand_32
/*5178*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5181*/        OPC_EmitMergeInputChains1_0,
/*5182*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_NAND_I32), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_load_nand:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)<<P:Predicate_atomic_load_nand_32>> - Complexity = 13
                // Dst: (ATOMIC_LOAD_NAND_I32:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$incr)
/*5193*/      0, /*End of Scope*/
            /*SwitchType*/ 17,  MVT::i64,// ->5213
/*5196*/      OPC_CheckPredicate, 54, // Predicate_atomic_load_nand_64
/*5198*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5201*/      OPC_EmitMergeInputChains1_0,
/*5202*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_LOAD_NAND_I64), 0|OPFL_Chain|OPFL_MemRefs,
                  2/*#VTs*/, MVT::i64, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
              // Src: (atomic_load_nand:i64 xoaddr:iPTR:$ptr, G8RC:i64:$incr)<<P:Predicate_atomic_load_nand_64>> - Complexity = 13
              // Dst: (ATOMIC_LOAD_NAND_I64:i64:i32 xoaddr:iPTR:$ptr, G8RC:i64:$incr)
            0, // EndSwitchType
          /*SwitchOpcode*/ 88,  TARGET_VAL(ISD::ATOMIC_CMP_SWAP),// ->5305
/*5217*/    OPC_RecordMemRef,
/*5218*/    OPC_RecordNode,   // #0 = 'atomic_cmp_swap' chained node
/*5219*/    OPC_RecordChild1, // #1 = $ptr
/*5220*/    OPC_RecordChild2, // #2 = $old
/*5221*/    OPC_RecordChild3, // #3 = $new
/*5222*/    OPC_SwitchType /*2 cases */, 59,  MVT::i32,// ->5284
/*5225*/      OPC_Scope, 18, /*->5245*/ // 3 children in Scope
/*5227*/        OPC_CheckPredicate, 55, // Predicate_atomic_cmp_swap_8
/*5229*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #4 #5
/*5232*/        OPC_EmitMergeInputChains1_0,
/*5233*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_CMP_SWAP_I8), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 4/*#Ops*/, 4, 5, 2, 3, 
                // Src: (atomic_cmp_swap:i32 xoaddr:iPTR:$ptr, GPRC:i32:$old, GPRC:i32:$new)<<P:Predicate_atomic_cmp_swap_8>> - Complexity = 13
                // Dst: (ATOMIC_CMP_SWAP_I8:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$old, GPRC:i32:$new)
/*5245*/      /*Scope*/ 18, /*->5264*/
/*5246*/        OPC_CheckPredicate, 56, // Predicate_atomic_cmp_swap_16
/*5248*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #4 #5
/*5251*/        OPC_EmitMergeInputChains1_0,
/*5252*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_CMP_SWAP_I16), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 4/*#Ops*/, 4, 5, 2, 3, 
                // Src: (atomic_cmp_swap:i32 xoaddr:iPTR:$ptr, GPRC:i32:$old, GPRC:i32:$new)<<P:Predicate_atomic_cmp_swap_16>> - Complexity = 13
                // Dst: (ATOMIC_CMP_SWAP_I16:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$old, GPRC:i32:$new)
/*5264*/      /*Scope*/ 18, /*->5283*/
/*5265*/        OPC_CheckPredicate, 57, // Predicate_atomic_cmp_swap_32
/*5267*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #4 #5
/*5270*/        OPC_EmitMergeInputChains1_0,
/*5271*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_CMP_SWAP_I32), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 4/*#Ops*/, 4, 5, 2, 3, 
                // Src: (atomic_cmp_swap:i32 xoaddr:iPTR:$ptr, GPRC:i32:$old, GPRC:i32:$new)<<P:Predicate_atomic_cmp_swap_32>> - Complexity = 13
                // Dst: (ATOMIC_CMP_SWAP_I32:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$old, GPRC:i32:$new)
/*5283*/      0, /*End of Scope*/
            /*SwitchType*/ 18,  MVT::i64,// ->5304
/*5286*/      OPC_CheckPredicate, 58, // Predicate_atomic_cmp_swap_64
/*5288*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #4 #5
/*5291*/      OPC_EmitMergeInputChains1_0,
/*5292*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_CMP_SWAP_I64), 0|OPFL_Chain|OPFL_MemRefs,
                  2/*#VTs*/, MVT::i64, MVT::i32, 4/*#Ops*/, 4, 5, 2, 3, 
              // Src: (atomic_cmp_swap:i64 xoaddr:iPTR:$ptr, G8RC:i64:$old, G8RC:i64:$new)<<P:Predicate_atomic_cmp_swap_64>> - Complexity = 13
              // Dst: (ATOMIC_CMP_SWAP_I64:i64:i32 xoaddr:iPTR:$ptr, G8RC:i64:$old, G8RC:i64:$new)
            0, // EndSwitchType
          /*SwitchOpcode*/ 83,  TARGET_VAL(ISD::ATOMIC_SWAP),// ->5391
/*5308*/    OPC_RecordMemRef,
/*5309*/    OPC_RecordNode,   // #0 = 'atomic_swap' chained node
/*5310*/    OPC_RecordChild1, // #1 = $ptr
/*5311*/    OPC_RecordChild2, // #2 = $new
/*5312*/    OPC_SwitchType /*2 cases */, 56,  MVT::i32,// ->5371
/*5315*/      OPC_Scope, 17, /*->5334*/ // 3 children in Scope
/*5317*/        OPC_CheckPredicate, 59, // Predicate_atomic_swap_8
/*5319*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5322*/        OPC_EmitMergeInputChains1_0,
/*5323*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_SWAP_I8), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_swap:i32 xoaddr:iPTR:$ptr, GPRC:i32:$new)<<P:Predicate_atomic_swap_8>> - Complexity = 13
                // Dst: (ATOMIC_SWAP_I8:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$new)
/*5334*/      /*Scope*/ 17, /*->5352*/
/*5335*/        OPC_CheckPredicate, 60, // Predicate_atomic_swap_16
/*5337*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5340*/        OPC_EmitMergeInputChains1_0,
/*5341*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_SWAP_I16), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_swap:i32 xoaddr:iPTR:$ptr, GPRC:i32:$new)<<P:Predicate_atomic_swap_16>> - Complexity = 13
                // Dst: (ATOMIC_SWAP_I16:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$new)
/*5352*/      /*Scope*/ 17, /*->5370*/
/*5353*/        OPC_CheckPredicate, 61, // Predicate_atomic_swap_32
/*5355*/        OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5358*/        OPC_EmitMergeInputChains1_0,
/*5359*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_SWAP_I32), 0|OPFL_Chain|OPFL_MemRefs,
                    2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
                // Src: (atomic_swap:i32 xoaddr:iPTR:$ptr, GPRC:i32:$new)<<P:Predicate_atomic_swap_32>> - Complexity = 13
                // Dst: (ATOMIC_SWAP_I32:i32:i32 xoaddr:iPTR:$ptr, GPRC:i32:$new)
/*5370*/      0, /*End of Scope*/
            /*SwitchType*/ 17,  MVT::i64,// ->5390
/*5373*/      OPC_CheckPredicate, 62, // Predicate_atomic_swap_64
/*5375*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #3 #4
/*5378*/      OPC_EmitMergeInputChains1_0,
/*5379*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ATOMIC_SWAP_I64), 0|OPFL_Chain|OPFL_MemRefs,
                  2/*#VTs*/, MVT::i64, MVT::i32, 3/*#Ops*/, 3, 4, 2, 
              // Src: (atomic_swap:i64 xoaddr:iPTR:$ptr, G8RC:i64:$new)<<P:Predicate_atomic_swap_64>> - Complexity = 13
              // Dst: (ATOMIC_SWAP_I64:i64:i32 xoaddr:iPTR:$ptr, G8RC:i64:$new)
            0, // EndSwitchType
          /*SwitchOpcode*/ 48,  TARGET_VAL(PPCISD::DYNALLOC),// ->5442
/*5394*/    OPC_RecordNode,   // #0 = 'PPCdynalloc' chained node
/*5395*/    OPC_RecordChild1, // #1 = $negsize
/*5396*/    OPC_SwitchType /*2 cases */, 20,  MVT::i32,// ->5419
/*5399*/      OPC_CheckChild1Type, MVT::i32,
/*5401*/      OPC_RecordChild2, // #2 = $fpsi
/*5402*/      OPC_CheckChild2Type, MVT::iPTR,
/*5404*/      OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$fpsi #3 #4
/*5407*/      OPC_EmitMergeInputChains1_0,
/*5408*/      OPC_MorphNodeTo, TARGET_VAL(PPC::DYNALLOC), 0|OPFL_Chain,
                  2/*#VTs*/, MVT::i32, MVT::i32, 3/*#Ops*/, 1, 3, 4, 
              // Src: (PPCdynalloc:i32 GPRC:i32:$negsize, iaddr:iPTR:$fpsi) - Complexity = 12
              // Dst: (DYNALLOC:i32:i32 GPRC:i32:$negsize, iaddr:iPTR:$fpsi)
            /*SwitchType*/ 20,  MVT::i64,// ->5441
/*5421*/      OPC_CheckChild1Type, MVT::i64,
/*5423*/      OPC_RecordChild2, // #2 = $fpsi
/*5424*/      OPC_CheckChild2Type, MVT::iPTR,
/*5426*/      OPC_CheckComplexPat, /*CP*/1, /*#*/2, // SelectAddrImm:$fpsi #3 #4
/*5429*/      OPC_EmitMergeInputChains1_0,
/*5430*/      OPC_MorphNodeTo, TARGET_VAL(PPC::DYNALLOC8), 0|OPFL_Chain,
                  2/*#VTs*/, MVT::i64, MVT::i64, 3/*#Ops*/, 1, 3, 4, 
              // Src: (PPCdynalloc:i64 G8RC:i64:$negsize, iaddr:iPTR:$fpsi) - Complexity = 12
              // Dst: (DYNALLOC8:i64:i64 G8RC:i64:$negsize, iaddr:iPTR:$fpsi)
            0, // EndSwitchType
          /*SwitchOpcode*/ 34,  TARGET_VAL(PPCISD::LARX),// ->5479
/*5445*/    OPC_RecordNode,   // #0 = 'PPClarx' chained node
/*5446*/    OPC_RecordChild1, // #1 = $src
/*5447*/    OPC_SwitchType /*2 cases */, 13,  MVT::i32,// ->5463
/*5450*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$src #2 #3
/*5453*/      OPC_EmitMergeInputChains1_0,
/*5454*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LWARX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (PPClarx:i32 xoaddr:iPTR:$src) - Complexity = 12
              // Dst: (LWARX:i32 xoaddr:iPTR:$src)
            /*SwitchType*/ 13,  MVT::i64,// ->5478
/*5465*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$ptr #2 #3
/*5468*/      OPC_EmitMergeInputChains1_0,
/*5469*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LDARX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
              // Src: (PPClarx:i64 xoaddr:iPTR:$ptr) - Complexity = 12
              // Dst: (LDARX:i64 xoaddr:iPTR:$ptr)
            0, // EndSwitchType
          /*SwitchOpcode*/ 40,  TARGET_VAL(PPCISD::LBRX),// ->5522
/*5482*/    OPC_RecordNode,   // #0 = 'PPClbrx' chained node
/*5483*/    OPC_RecordChild1, // #1 = $src
/*5484*/    OPC_MoveChild, 2,
/*5486*/    OPC_Scope, 16, /*->5504*/ // 2 children in Scope
/*5488*/      OPC_CheckValueType, MVT::i16,
/*5490*/      OPC_MoveParent,
/*5491*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$src #2 #3
/*5494*/      OPC_EmitMergeInputChains1_0,
/*5495*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LHBRX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (PPClbrx:i32 xoaddr:iPTR:$src, i16:Other) - Complexity = 12
              // Dst: (LHBRX:i32 xoaddr:iPTR:$src)
/*5504*/    /*Scope*/ 16, /*->5521*/
/*5505*/      OPC_CheckValueType, MVT::i32,
/*5507*/      OPC_MoveParent,
/*5508*/      OPC_CheckComplexPat, /*CP*/0, /*#*/1, // SelectAddrIdxOnly:$src #2 #3
/*5511*/      OPC_EmitMergeInputChains1_0,
/*5512*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LWBRX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 2, 3, 
              // Src: (PPClbrx:i32 xoaddr:iPTR:$src, i32:Other) - Complexity = 12
              // Dst: (LWBRX:i32 xoaddr:iPTR:$src)
/*5521*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 37,  TARGET_VAL(PPCISD::LOAD),// ->5562
/*5525*/    OPC_RecordNode,   // #0 = 'PPCload' chained node
/*5526*/    OPC_CaptureGlueInput,
/*5527*/    OPC_RecordChild1, // #1 = $src
/*5528*/    OPC_CheckChild1Type, MVT::iPTR,
/*5530*/    OPC_CheckType, MVT::i64,
/*5532*/    OPC_Scope, 13, /*->5547*/ // 2 children in Scope
/*5534*/      OPC_CheckComplexPat, /*CP*/3, /*#*/1, // SelectAddrImmShift:$src #2 #3
/*5537*/      OPC_EmitMergeInputChains1_0,
/*5538*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LD), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
              // Src: (PPCload:i64 ixaddr:iPTR:$src) - Complexity = 12
              // Dst: (LD:i64 ixaddr:iPTR:$src)
/*5547*/    /*Scope*/ 13, /*->5561*/
/*5548*/      OPC_CheckComplexPat, /*CP*/2, /*#*/1, // SelectAddrIdx:$src #2 #3
/*5551*/      OPC_EmitMergeInputChains1_0,
/*5552*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LDX), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 2, 3, 
              // Src: (PPCload:i64 xaddr:iPTR:$src) - Complexity = 12
              // Dst: (LDX:i64 xaddr:iPTR:$src)
/*5561*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 85|128,4/*597*/,  TARGET_VAL(ISD::XOR),// ->6163
/*5566*/    OPC_Scope, 112|128,1/*240*/, /*->5809*/ // 6 children in Scope
/*5569*/      OPC_MoveChild, 0,
/*5571*/      OPC_SwitchOpcode /*4 cases */, 41,  TARGET_VAL(ISD::AND),// ->5616
/*5575*/        OPC_RecordChild0, // #0 = $rS
/*5576*/        OPC_RecordChild1, // #1 = $rB
/*5577*/        OPC_MoveParent,
/*5578*/        OPC_MoveChild, 1,
/*5580*/        OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*5591*/        OPC_MoveParent,
/*5592*/        OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->5604
/*5595*/          OPC_MorphNodeTo, TARGET_VAL(PPC::NAND), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                  // Src: (xor:i32 (and:i32 GPRC:i32:$rS, GPRC:i32:$rB), -1:i32) - Complexity = 11
                  // Dst: (NAND:i32 GPRC:i32:$rS, GPRC:i32:$rB)
                /*SwitchType*/ 9,  MVT::i64,// ->5615
/*5606*/          OPC_MorphNodeTo, TARGET_VAL(PPC::NAND8), 0,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                  // Src: (xor:i64 (and:i64 G8RC:i64:$rS, G8RC:i64:$rB), -1:i64) - Complexity = 11
                  // Dst: (NAND8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
                0, // EndSwitchType
              /*SwitchOpcode*/ 81,  TARGET_VAL(ISD::OR),// ->5700
/*5619*/        OPC_RecordChild0, // #0 = $rS
/*5620*/        OPC_RecordChild1, // #1 = $rB
/*5621*/        OPC_MoveParent,
/*5622*/        OPC_MoveChild, 1,
/*5624*/        OPC_Scope, 23, /*->5649*/ // 3 children in Scope
/*5626*/          OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*5637*/          OPC_MoveParent,
/*5638*/          OPC_CheckType, MVT::i32,
/*5640*/          OPC_MorphNodeTo, TARGET_VAL(PPC::NOR), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                  // Src: (xor:i32 (or:i32 GPRC:i32:$rS, GPRC:i32:$rB), -1:i32) - Complexity = 11
                  // Dst: (NOR:i32 GPRC:i32:$rS, GPRC:i32:$rB)
/*5649*/        /*Scope*/ 25, /*->5675*/
/*5650*/          OPC_CheckOpcode, TARGET_VAL(ISD::BITCAST),
/*5653*/          OPC_MoveChild, 0,
/*5655*/          OPC_CheckOpcode, TARGET_VAL(ISD::BUILD_VECTOR),
/*5658*/          OPC_CheckPredicate, 63, // Predicate_immAllOnesV
/*5660*/          OPC_CheckType, MVT::v16i8,
/*5662*/          OPC_MoveParent,
/*5663*/          OPC_MoveParent,
/*5664*/          OPC_CheckType, MVT::v4i32,
/*5666*/          OPC_MorphNodeTo, TARGET_VAL(PPC::VNOR), 0,
                      1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
                  // Src: (xor:v4i32 (or:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB), (bitconvert:v4i32 (build_vector:v16i8)<<P:Predicate_immAllOnesV>>)) - Complexity = 13
                  // Dst: (VNOR:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*5675*/        /*Scope*/ 23, /*->5699*/
/*5676*/          OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*5687*/          OPC_MoveParent,
/*5688*/          OPC_CheckType, MVT::i64,
/*5690*/          OPC_MorphNodeTo, TARGET_VAL(PPC::NOR8), 0,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                  // Src: (xor:i64 (or:i64 G8RC:i64:$rS, G8RC:i64:$rB), -1:i64) - Complexity = 11
                  // Dst: (NOR8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
/*5699*/        0, /*End of Scope*/
              /*SwitchOpcode*/ 72,  TARGET_VAL(ISD::XOR),// ->5775
/*5703*/        OPC_RecordChild0, // #0 = $rS
/*5704*/        OPC_Scope, 40, /*->5746*/ // 2 children in Scope
/*5706*/          OPC_RecordChild1, // #1 = $rB
/*5707*/          OPC_MoveParent,
/*5708*/          OPC_MoveChild, 1,
/*5710*/          OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*5721*/          OPC_MoveParent,
/*5722*/          OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->5734
/*5725*/            OPC_MorphNodeTo, TARGET_VAL(PPC::EQV), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                    // Src: (xor:i32 (xor:i32 GPRC:i32:$rS, GPRC:i32:$rB), -1:i32) - Complexity = 11
                    // Dst: (EQV:i32 GPRC:i32:$rS, GPRC:i32:$rB)
                  /*SwitchType*/ 9,  MVT::i64,// ->5745
/*5736*/            OPC_MorphNodeTo, TARGET_VAL(PPC::EQV8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                    // Src: (xor:i64 (xor:i64 G8RC:i64:$rS, G8RC:i64:$rB), -1:i64) - Complexity = 11
                    // Dst: (EQV8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
                  0, // EndSwitchType
/*5746*/        /*Scope*/ 27, /*->5774*/
/*5747*/          OPC_MoveChild, 1,
/*5749*/          OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*5760*/          OPC_MoveParent,
/*5761*/          OPC_MoveParent,
/*5762*/          OPC_RecordChild1, // #1 = $rB
/*5763*/          OPC_CheckType, MVT::i32,
/*5765*/          OPC_MorphNodeTo, TARGET_VAL(PPC::EQV), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                  // Src: (xor:i32 (xor:i32 GPRC:i32:$rS, -1:i32), GPRC:i32:$rB) - Complexity = 11
                  // Dst: (EQV:i32 GPRC:i32:$rS, GPRC:i32:$rB)
/*5774*/        0, /*End of Scope*/
              /*SwitchOpcode*/ 30,  TARGET_VAL(ISD::BITCAST),// ->5808
/*5778*/        OPC_MoveChild, 0,
/*5780*/        OPC_CheckOpcode, TARGET_VAL(ISD::BUILD_VECTOR),
/*5783*/        OPC_CheckPredicate, 63, // Predicate_immAllOnesV
/*5785*/        OPC_CheckType, MVT::v16i8,
/*5787*/        OPC_MoveParent,
/*5788*/        OPC_MoveParent,
/*5789*/        OPC_MoveChild, 1,
/*5791*/        OPC_CheckOpcode, TARGET_VAL(ISD::OR),
/*5794*/        OPC_RecordChild0, // #0 = $vA
/*5795*/        OPC_RecordChild1, // #1 = $vB
/*5796*/        OPC_MoveParent,
/*5797*/        OPC_CheckType, MVT::v4i32,
/*5799*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VNOR), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
                // Src: (xor:v4i32 (bitconvert:v4i32 (build_vector:v16i8)<<P:Predicate_immAllOnesV>>), (or:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)) - Complexity = 13
                // Dst: (VNOR:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
              0, // EndSwitchOpcode
/*5809*/    /*Scope*/ 33, /*->5843*/
/*5810*/      OPC_RecordChild0, // #0 = $rB
/*5811*/      OPC_MoveChild, 1,
/*5813*/      OPC_CheckOpcode, TARGET_VAL(ISD::XOR),
/*5816*/      OPC_RecordChild0, // #1 = $rS
/*5817*/      OPC_MoveChild, 1,
/*5819*/      OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*5830*/      OPC_MoveParent,
/*5831*/      OPC_MoveParent,
/*5832*/      OPC_CheckType, MVT::i32,
/*5834*/      OPC_MorphNodeTo, TARGET_VAL(PPC::EQV), 0,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
              // Src: (xor:i32 GPRC:i32:$rB, (xor:i32 GPRC:i32:$rS, -1:i32)) - Complexity = 11
              // Dst: (EQV:i32 GPRC:i32:$rS, GPRC:i32:$rB)
/*5843*/    /*Scope*/ 33, /*->5877*/
/*5844*/      OPC_MoveChild, 0,
/*5846*/      OPC_CheckOpcode, TARGET_VAL(ISD::XOR),
/*5849*/      OPC_RecordChild0, // #0 = $rS
/*5850*/      OPC_MoveChild, 1,
/*5852*/      OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*5863*/      OPC_MoveParent,
/*5864*/      OPC_MoveParent,
/*5865*/      OPC_RecordChild1, // #1 = $rB
/*5866*/      OPC_CheckType, MVT::i64,
/*5868*/      OPC_MorphNodeTo, TARGET_VAL(PPC::EQV8), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (xor:i64 (xor:i64 G8RC:i64:$rS, -1:i64), G8RC:i64:$rB) - Complexity = 11
              // Dst: (EQV8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
/*5877*/    /*Scope*/ 112|128,1/*240*/, /*->6119*/
/*5879*/      OPC_RecordChild0, // #0 = $rB
/*5880*/      OPC_Scope, 59, /*->5941*/ // 3 children in Scope
/*5882*/        OPC_MoveChild, 1,
/*5884*/        OPC_Scope, 30, /*->5916*/ // 2 children in Scope
/*5886*/          OPC_CheckOpcode, TARGET_VAL(ISD::XOR),
/*5889*/          OPC_RecordChild0, // #1 = $rS
/*5890*/          OPC_MoveChild, 1,
/*5892*/          OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*5903*/          OPC_MoveParent,
/*5904*/          OPC_MoveParent,
/*5905*/          OPC_CheckType, MVT::i64,
/*5907*/          OPC_MorphNodeTo, TARGET_VAL(PPC::EQV8), 0,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                  // Src: (xor:i64 G8RC:i64:$rB, (xor:i64 G8RC:i64:$rS, -1:i64)) - Complexity = 11
                  // Dst: (EQV8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
/*5916*/        /*Scope*/ 23, /*->5940*/
/*5917*/          OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*5928*/          OPC_MoveParent,
/*5929*/          OPC_CheckType, MVT::i32,
/*5931*/          OPC_MorphNodeTo, TARGET_VAL(PPC::NOR), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 0, 
                  // Src: (xor:i32 GPRC:i32:$in, -1:i32) - Complexity = 8
                  // Dst: (NOR:i32 GPRC:i32:$in, GPRC:i32:$in)
/*5940*/        0, /*End of Scope*/
/*5941*/      /*Scope*/ 19|128,1/*147*/, /*->6090*/
/*5943*/        OPC_RecordChild1, // #1 = $src2
/*5944*/        OPC_Scope, 119, /*->6065*/ // 3 children in Scope
/*5946*/          OPC_MoveChild, 1,
/*5948*/          OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*5951*/          OPC_Scope, 19, /*->5972*/ // 5 children in Scope
/*5953*/            OPC_CheckPredicate, 64, // Predicate_immZExt16
/*5955*/            OPC_MoveParent,
/*5956*/            OPC_CheckType, MVT::i32,
/*5958*/            OPC_EmitConvertToTarget, 1,
/*5960*/            OPC_EmitNodeXForm, 1, 2, // LO16
/*5963*/            OPC_MorphNodeTo, TARGET_VAL(PPC::XORI), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 3, 
                    // Src: (xor:i32 GPRC:i32:$src1, (imm:i32)<<P:Predicate_immZExt16>><<X:LO16>>:$src2) - Complexity = 7
                    // Dst: (XORI:i32 GPRC:i32:$src1, (LO16:i32 (imm:i32):$src2))
/*5972*/          /*Scope*/ 19, /*->5992*/
/*5973*/            OPC_CheckPredicate, 65, // Predicate_imm16ShiftedZExt
/*5975*/            OPC_MoveParent,
/*5976*/            OPC_CheckType, MVT::i32,
/*5978*/            OPC_EmitConvertToTarget, 1,
/*5980*/            OPC_EmitNodeXForm, 0, 2, // HI16
/*5983*/            OPC_MorphNodeTo, TARGET_VAL(PPC::XORIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 3, 
                    // Src: (xor:i32 GPRC:i32:$src1, (imm:i32)<<P:Predicate_imm16ShiftedZExt>><<X:HI16>>:$src2) - Complexity = 7
                    // Dst: (XORIS:i32 GPRC:i32:$src1, (HI16:i32 (imm:i32):$src2))
/*5992*/          /*Scope*/ 19, /*->6012*/
/*5993*/            OPC_CheckPredicate, 64, // Predicate_immZExt16
/*5995*/            OPC_MoveParent,
/*5996*/            OPC_CheckType, MVT::i64,
/*5998*/            OPC_EmitConvertToTarget, 1,
/*6000*/            OPC_EmitNodeXForm, 1, 2, // LO16
/*6003*/            OPC_MorphNodeTo, TARGET_VAL(PPC::XORI8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 3, 
                    // Src: (xor:i64 G8RC:i64:$src1, (imm:i64)<<P:Predicate_immZExt16>><<X:LO16>>:$src2) - Complexity = 7
                    // Dst: (XORI8:i64 G8RC:i64:$src1, (LO16:i32 (imm:i64):$src2))
/*6012*/          /*Scope*/ 19, /*->6032*/
/*6013*/            OPC_CheckPredicate, 65, // Predicate_imm16ShiftedZExt
/*6015*/            OPC_MoveParent,
/*6016*/            OPC_CheckType, MVT::i64,
/*6018*/            OPC_EmitConvertToTarget, 1,
/*6020*/            OPC_EmitNodeXForm, 0, 2, // HI16
/*6023*/            OPC_MorphNodeTo, TARGET_VAL(PPC::XORIS8), 0,
                        1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 3, 
                    // Src: (xor:i64 G8RC:i64:$src1, (imm:i64)<<P:Predicate_imm16ShiftedZExt>><<X:HI16>>:$src2) - Complexity = 7
                    // Dst: (XORIS8:i64 G8RC:i64:$src1, (HI16:i32 (imm:i64):$src2))
/*6032*/          /*Scope*/ 31, /*->6064*/
/*6033*/            OPC_MoveParent,
/*6034*/            OPC_CheckType, MVT::i32,
/*6036*/            OPC_EmitConvertToTarget, 1,
/*6038*/            OPC_EmitNodeXForm, 1, 2, // LO16
/*6041*/            OPC_EmitNode, TARGET_VAL(PPC::XORI), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 3,  // Results = #4
/*6050*/            OPC_EmitConvertToTarget, 1,
/*6052*/            OPC_EmitNodeXForm, 0, 5, // HI16
/*6055*/            OPC_MorphNodeTo, TARGET_VAL(PPC::XORIS), 0,
                        1/*#VTs*/, MVT::i32, 2/*#Ops*/, 4, 6, 
                    // Src: (xor:i32 GPRC:i32:$in, (imm:i32):$imm) - Complexity = 6
                    // Dst: (XORIS:i32 (XORI:i32 GPRC:i32:$in, (LO16:i32 (imm:i32):$imm)), (HI16:i32 (imm:i32):$imm))
/*6064*/          0, /*End of Scope*/
/*6065*/        /*Scope*/ 11, /*->6077*/
/*6066*/          OPC_CheckType, MVT::i32,
/*6068*/          OPC_MorphNodeTo, TARGET_VAL(PPC::XOR), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                  // Src: (xor:i32 GPRC:i32:$rS, GPRC:i32:$rB) - Complexity = 3
                  // Dst: (XOR:i32 GPRC:i32:$rS, GPRC:i32:$rB)
/*6077*/        /*Scope*/ 11, /*->6089*/
/*6078*/          OPC_CheckType, MVT::i64,
/*6080*/          OPC_MorphNodeTo, TARGET_VAL(PPC::XOR8), 0,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                  // Src: (xor:i64 G8RC:i64:$rS, G8RC:i64:$rB) - Complexity = 3
                  // Dst: (XOR8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
/*6089*/        0, /*End of Scope*/
/*6090*/      /*Scope*/ 27, /*->6118*/
/*6091*/        OPC_MoveChild, 1,
/*6093*/        OPC_CheckOpcode, TARGET_VAL(ISD::BITCAST),
/*6096*/        OPC_MoveChild, 0,
/*6098*/        OPC_CheckOpcode, TARGET_VAL(ISD::BUILD_VECTOR),
/*6101*/        OPC_CheckPredicate, 63, // Predicate_immAllOnesV
/*6103*/        OPC_CheckType, MVT::v16i8,
/*6105*/        OPC_MoveParent,
/*6106*/        OPC_MoveParent,
/*6107*/        OPC_CheckType, MVT::v4i32,
/*6109*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VNOR), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 0, 
                // Src: (xor:v4i32 VRRC:v4i32:$vA, (bitconvert:v4i32 (build_vector:v16i8)<<P:Predicate_immAllOnesV>>)) - Complexity = 10
                // Dst: (VNOR:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vA)
/*6118*/      0, /*End of Scope*/
/*6119*/    /*Scope*/ 28, /*->6148*/
/*6120*/      OPC_MoveChild, 0,
/*6122*/      OPC_CheckOpcode, TARGET_VAL(ISD::BITCAST),
/*6125*/      OPC_MoveChild, 0,
/*6127*/      OPC_CheckOpcode, TARGET_VAL(ISD::BUILD_VECTOR),
/*6130*/      OPC_CheckPredicate, 63, // Predicate_immAllOnesV
/*6132*/      OPC_CheckType, MVT::v16i8,
/*6134*/      OPC_MoveParent,
/*6135*/      OPC_MoveParent,
/*6136*/      OPC_RecordChild1, // #0 = $vA
/*6137*/      OPC_CheckType, MVT::v4i32,
/*6139*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VNOR), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 0, 
              // Src: (xor:v4i32 (bitconvert:v4i32 (build_vector:v16i8)<<P:Predicate_immAllOnesV>>), VRRC:v4i32:$vA) - Complexity = 10
              // Dst: (VNOR:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vA)
/*6148*/    /*Scope*/ 13, /*->6162*/
/*6149*/      OPC_RecordChild0, // #0 = $vA
/*6150*/      OPC_RecordChild1, // #1 = $vB
/*6151*/      OPC_CheckType, MVT::v4i32,
/*6153*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VXOR), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (xor:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 3
              // Dst: (VXOR:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*6162*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 42|128,3/*426*/,  TARGET_VAL(ISD::AND),// ->6593
/*6167*/    OPC_Scope, 96, /*->6265*/ // 5 children in Scope
/*6169*/      OPC_RecordChild0, // #0 = $rS
/*6170*/      OPC_MoveChild, 1,
/*6172*/      OPC_CheckOpcode, TARGET_VAL(ISD::XOR),
/*6175*/      OPC_Scope, 57, /*->6234*/ // 2 children in Scope
/*6177*/        OPC_RecordChild0, // #1 = $rB
/*6178*/        OPC_MoveChild, 1,
/*6180*/        OPC_Scope, 24, /*->6206*/ // 2 children in Scope
/*6182*/          OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*6193*/          OPC_MoveParent,
/*6194*/          OPC_MoveParent,
/*6195*/          OPC_CheckType, MVT::i32,
/*6197*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ANDC), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                  // Src: (and:i32 GPRC:i32:$rS, (xor:i32 GPRC:i32:$rB, -1:i32)) - Complexity = 11
                  // Dst: (ANDC:i32 GPRC:i32:$rS, GPRC:i32:$rB)
/*6206*/        /*Scope*/ 26, /*->6233*/
/*6207*/          OPC_CheckOpcode, TARGET_VAL(ISD::BITCAST),
/*6210*/          OPC_MoveChild, 0,
/*6212*/          OPC_CheckOpcode, TARGET_VAL(ISD::BUILD_VECTOR),
/*6215*/          OPC_CheckPredicate, 63, // Predicate_immAllOnesV
/*6217*/          OPC_CheckType, MVT::v16i8,
/*6219*/          OPC_MoveParent,
/*6220*/          OPC_MoveParent,
/*6221*/          OPC_MoveParent,
/*6222*/          OPC_CheckType, MVT::v4i32,
/*6224*/          OPC_MorphNodeTo, TARGET_VAL(PPC::VANDC), 0,
                      1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
                  // Src: (and:v4i32 VRRC:v4i32:$vA, (xor:v4i32 VRRC:v4i32:$vB, (bitconvert:v4i32 (build_vector:v16i8)<<P:Predicate_immAllOnesV>>))) - Complexity = 13
                  // Dst: (VANDC:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*6233*/        0, /*End of Scope*/
/*6234*/      /*Scope*/ 29, /*->6264*/
/*6235*/        OPC_MoveChild, 0,
/*6237*/        OPC_CheckOpcode, TARGET_VAL(ISD::BITCAST),
/*6240*/        OPC_MoveChild, 0,
/*6242*/        OPC_CheckOpcode, TARGET_VAL(ISD::BUILD_VECTOR),
/*6245*/        OPC_CheckPredicate, 63, // Predicate_immAllOnesV
/*6247*/        OPC_CheckType, MVT::v16i8,
/*6249*/        OPC_MoveParent,
/*6250*/        OPC_MoveParent,
/*6251*/        OPC_RecordChild1, // #1 = $vB
/*6252*/        OPC_MoveParent,
/*6253*/        OPC_CheckType, MVT::v4i32,
/*6255*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VANDC), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
                // Src: (and:v4i32 VRRC:v4i32:$vA, (xor:v4i32 (bitconvert:v4i32 (build_vector:v16i8)<<P:Predicate_immAllOnesV>>), VRRC:v4i32:$vB)) - Complexity = 13
                // Dst: (VANDC:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*6264*/      0, /*End of Scope*/
/*6265*/    /*Scope*/ 69, /*->6335*/
/*6266*/      OPC_MoveChild, 0,
/*6268*/      OPC_CheckOpcode, TARGET_VAL(ISD::XOR),
/*6271*/      OPC_Scope, 30, /*->6303*/ // 2 children in Scope
/*6273*/        OPC_RecordChild0, // #0 = $vB
/*6274*/        OPC_MoveChild, 1,
/*6276*/        OPC_CheckOpcode, TARGET_VAL(ISD::BITCAST),
/*6279*/        OPC_MoveChild, 0,
/*6281*/        OPC_CheckOpcode, TARGET_VAL(ISD::BUILD_VECTOR),
/*6284*/        OPC_CheckPredicate, 63, // Predicate_immAllOnesV
/*6286*/        OPC_CheckType, MVT::v16i8,
/*6288*/        OPC_MoveParent,
/*6289*/        OPC_MoveParent,
/*6290*/        OPC_MoveParent,
/*6291*/        OPC_RecordChild1, // #1 = $vA
/*6292*/        OPC_CheckType, MVT::v4i32,
/*6294*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VANDC), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 1, 0, 
                // Src: (and:v4i32 (xor:v4i32 VRRC:v4i32:$vB, (bitconvert:v4i32 (build_vector:v16i8)<<P:Predicate_immAllOnesV>>)), VRRC:v4i32:$vA) - Complexity = 13
                // Dst: (VANDC:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*6303*/      /*Scope*/ 30, /*->6334*/
/*6304*/        OPC_MoveChild, 0,
/*6306*/        OPC_CheckOpcode, TARGET_VAL(ISD::BITCAST),
/*6309*/        OPC_MoveChild, 0,
/*6311*/        OPC_CheckOpcode, TARGET_VAL(ISD::BUILD_VECTOR),
/*6314*/        OPC_CheckPredicate, 63, // Predicate_immAllOnesV
/*6316*/        OPC_CheckType, MVT::v16i8,
/*6318*/        OPC_MoveParent,
/*6319*/        OPC_MoveParent,
/*6320*/        OPC_RecordChild1, // #0 = $vB
/*6321*/        OPC_MoveParent,
/*6322*/        OPC_RecordChild1, // #1 = $vA
/*6323*/        OPC_CheckType, MVT::v4i32,
/*6325*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VANDC), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 1, 0, 
                // Src: (and:v4i32 (xor:v4i32 (bitconvert:v4i32 (build_vector:v16i8)<<P:Predicate_immAllOnesV>>), VRRC:v4i32:$vB), VRRC:v4i32:$vA) - Complexity = 13
                // Dst: (VANDC:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*6334*/      0, /*End of Scope*/
/*6335*/    /*Scope*/ 33, /*->6369*/
/*6336*/      OPC_RecordChild0, // #0 = $rS
/*6337*/      OPC_MoveChild, 1,
/*6339*/      OPC_CheckOpcode, TARGET_VAL(ISD::XOR),
/*6342*/      OPC_RecordChild0, // #1 = $rB
/*6343*/      OPC_MoveChild, 1,
/*6345*/      OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*6356*/      OPC_MoveParent,
/*6357*/      OPC_MoveParent,
/*6358*/      OPC_CheckType, MVT::i64,
/*6360*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ANDC8), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (and:i64 G8RC:i64:$rS, (xor:i64 G8RC:i64:$rB, -1:i64)) - Complexity = 11
              // Dst: (ANDC8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
/*6369*/    /*Scope*/ 88, /*->6458*/
/*6370*/      OPC_MoveChild, 0,
/*6372*/      OPC_SwitchOpcode /*2 cases */, 41,  TARGET_VAL(ISD::XOR),// ->6417
/*6376*/        OPC_RecordChild0, // #0 = $rB
/*6377*/        OPC_MoveChild, 1,
/*6379*/        OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*6390*/        OPC_MoveParent,
/*6391*/        OPC_MoveParent,
/*6392*/        OPC_RecordChild1, // #1 = $rS
/*6393*/        OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->6405
/*6396*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ANDC), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                  // Src: (and:i32 (xor:i32 GPRC:i32:$rB, -1:i32), GPRC:i32:$rS) - Complexity = 11
                  // Dst: (ANDC:i32 GPRC:i32:$rS, GPRC:i32:$rB)
                /*SwitchType*/ 9,  MVT::i64,// ->6416
/*6407*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ANDC8), 0,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                  // Src: (and:i64 (xor:i64 G8RC:i64:$rB, -1:i64), G8RC:i64:$rS) - Complexity = 11
                  // Dst: (ANDC8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
                0, // EndSwitchType
              /*SwitchOpcode*/ 37,  TARGET_VAL(ISD::ROTL),// ->6457
/*6420*/        OPC_RecordChild0, // #0 = $in
/*6421*/        OPC_RecordChild1, // #1 = $sh
/*6422*/        OPC_CheckChild1Type, MVT::i32,
/*6424*/        OPC_MoveParent,
/*6425*/        OPC_RecordChild1, // #2 = $imm
/*6426*/        OPC_MoveChild, 1,
/*6428*/        OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*6431*/        OPC_CheckPredicate, 66, // Predicate_maskimm32
/*6433*/        OPC_MoveParent,
/*6434*/        OPC_CheckType, MVT::i32,
/*6436*/        OPC_EmitConvertToTarget, 2,
/*6438*/        OPC_EmitNodeXForm, 3, 3, // MB
/*6441*/        OPC_EmitConvertToTarget, 2,
/*6443*/        OPC_EmitNodeXForm, 4, 5, // ME
/*6446*/        OPC_MorphNodeTo, TARGET_VAL(PPC::RLWNM), 0,
                    1/*#VTs*/, MVT::i32, 4/*#Ops*/, 0, 1, 4, 6, 
                // Src: (and:i32 (rotl:i32 GPRC:i32:$in, GPRC:i32:$sh), (imm:i32)<<P:Predicate_maskimm32>>:$imm) - Complexity = 10
                // Dst: (RLWNM:i32 GPRC:i32:$in, GPRC:i32:$sh, (MB:i32 (imm:i32)<<P:Predicate_maskimm32>>:$imm), (ME:i32 (imm:i32)<<P:Predicate_maskimm32>>:$imm))
              0, // EndSwitchOpcode
/*6458*/    /*Scope*/ 4|128,1/*132*/, /*->6592*/
/*6460*/      OPC_RecordChild0, // #0 = $src1
/*6461*/      OPC_RecordChild1, // #1 = $src2
/*6462*/      OPC_Scope, 91, /*->6555*/ // 4 children in Scope
/*6464*/        OPC_MoveChild, 1,
/*6466*/        OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*6469*/        OPC_Scope, 20, /*->6491*/ // 4 children in Scope
/*6471*/          OPC_CheckPredicate, 64, // Predicate_immZExt16
/*6473*/          OPC_MoveParent,
/*6474*/          OPC_CheckType, MVT::i32,
/*6476*/          OPC_EmitConvertToTarget, 1,
/*6478*/          OPC_EmitNodeXForm, 1, 2, // LO16
/*6481*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ANDIo), 0,
                      2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 0, 3, 
                  // Src: (and:i32 GPRC:i32:$src1, (imm:i32)<<P:Predicate_immZExt16>><<X:LO16>>:$src2) - Complexity = 7
                  // Dst: (ANDIo:i32:i32 GPRC:i32:$src1, (LO16:i32 (imm:i32):$src2))
/*6491*/        /*Scope*/ 20, /*->6512*/
/*6492*/          OPC_CheckPredicate, 65, // Predicate_imm16ShiftedZExt
/*6494*/          OPC_MoveParent,
/*6495*/          OPC_CheckType, MVT::i32,
/*6497*/          OPC_EmitConvertToTarget, 1,
/*6499*/          OPC_EmitNodeXForm, 0, 2, // HI16
/*6502*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ANDISo), 0,
                      2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 0, 3, 
                  // Src: (and:i32 GPRC:i32:$src1, (imm:i32)<<P:Predicate_imm16ShiftedZExt>><<X:HI16>>:$src2) - Complexity = 7
                  // Dst: (ANDISo:i32:i32 GPRC:i32:$src1, (HI16:i32 (imm:i32):$src2))
/*6512*/        /*Scope*/ 20, /*->6533*/
/*6513*/          OPC_CheckPredicate, 64, // Predicate_immZExt16
/*6515*/          OPC_MoveParent,
/*6516*/          OPC_CheckType, MVT::i64,
/*6518*/          OPC_EmitConvertToTarget, 1,
/*6520*/          OPC_EmitNodeXForm, 1, 2, // LO16
/*6523*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ANDIo8), 0,
                      2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 0, 3, 
                  // Src: (and:i64 G8RC:i64:$src1, (imm:i64)<<P:Predicate_immZExt16>><<X:LO16>>:$src2) - Complexity = 7
                  // Dst: (ANDIo8:i64:i32 G8RC:i64:$src1, (LO16:i32 (imm:i64):$src2))
/*6533*/        /*Scope*/ 20, /*->6554*/
/*6534*/          OPC_CheckPredicate, 65, // Predicate_imm16ShiftedZExt
/*6536*/          OPC_MoveParent,
/*6537*/          OPC_CheckType, MVT::i64,
/*6539*/          OPC_EmitConvertToTarget, 1,
/*6541*/          OPC_EmitNodeXForm, 0, 2, // HI16
/*6544*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ANDISo8), 0,
                      2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 0, 3, 
                  // Src: (and:i64 G8RC:i64:$src1, (imm:i64)<<P:Predicate_imm16ShiftedZExt>><<X:HI16>>:$src2) - Complexity = 7
                  // Dst: (ANDISo8:i64:i32 G8RC:i64:$src1, (HI16:i32 (imm:i64):$src2))
/*6554*/        0, /*End of Scope*/
/*6555*/      /*Scope*/ 11, /*->6567*/
/*6556*/        OPC_CheckType, MVT::i32,
/*6558*/        OPC_MorphNodeTo, TARGET_VAL(PPC::AND), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (and:i32 GPRC:i32:$rS, GPRC:i32:$rB) - Complexity = 3
                // Dst: (AND:i32 GPRC:i32:$rS, GPRC:i32:$rB)
/*6567*/      /*Scope*/ 11, /*->6579*/
/*6568*/        OPC_CheckType, MVT::i64,
/*6570*/        OPC_MorphNodeTo, TARGET_VAL(PPC::AND8), 0,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                // Src: (and:i64 G8RC:i64:$rS, G8RC:i64:$rB) - Complexity = 3
                // Dst: (AND8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
/*6579*/      /*Scope*/ 11, /*->6591*/
/*6580*/        OPC_CheckType, MVT::v4i32,
/*6582*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VAND), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
                // Src: (and:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 3
                // Dst: (VAND:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*6591*/      0, /*End of Scope*/
/*6592*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 2|128,2/*258*/,  TARGET_VAL(ISD::OR),// ->6855
/*6597*/    OPC_Scope, 46, /*->6645*/ // 3 children in Scope
/*6599*/      OPC_RecordChild0, // #0 = $rS
/*6600*/      OPC_MoveChild, 1,
/*6602*/      OPC_CheckOpcode, TARGET_VAL(ISD::XOR),
/*6605*/      OPC_RecordChild0, // #1 = $rB
/*6606*/      OPC_MoveChild, 1,
/*6608*/      OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*6619*/      OPC_MoveParent,
/*6620*/      OPC_MoveParent,
/*6621*/      OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->6633
/*6624*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ORC), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (or:i32 GPRC:i32:$rS, (xor:i32 GPRC:i32:$rB, -1:i32)) - Complexity = 11
                // Dst: (ORC:i32 GPRC:i32:$rS, GPRC:i32:$rB)
              /*SwitchType*/ 9,  MVT::i64,// ->6644
/*6635*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ORC8), 0,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                // Src: (or:i64 G8RC:i64:$rS, (xor:i64 G8RC:i64:$rB, -1:i64)) - Complexity = 11
                // Dst: (ORC8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
              0, // EndSwitchType
/*6645*/    /*Scope*/ 46, /*->6692*/
/*6646*/      OPC_MoveChild, 0,
/*6648*/      OPC_CheckOpcode, TARGET_VAL(ISD::XOR),
/*6651*/      OPC_RecordChild0, // #0 = $rB
/*6652*/      OPC_MoveChild, 1,
/*6654*/      OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*6665*/      OPC_MoveParent,
/*6666*/      OPC_MoveParent,
/*6667*/      OPC_RecordChild1, // #1 = $rS
/*6668*/      OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->6680
/*6671*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ORC), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                // Src: (or:i32 (xor:i32 GPRC:i32:$rB, -1:i32), GPRC:i32:$rS) - Complexity = 11
                // Dst: (ORC:i32 GPRC:i32:$rS, GPRC:i32:$rB)
              /*SwitchType*/ 9,  MVT::i64,// ->6691
/*6682*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ORC8), 0,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                // Src: (or:i64 (xor:i64 G8RC:i64:$rB, -1:i64), G8RC:i64:$rS) - Complexity = 11
                // Dst: (ORC8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
              0, // EndSwitchType
/*6692*/    /*Scope*/ 32|128,1/*160*/, /*->6854*/
/*6694*/      OPC_RecordChild0, // #0 = $src1
/*6695*/      OPC_RecordChild1, // #1 = $src2
/*6696*/      OPC_Scope, 119, /*->6817*/ // 4 children in Scope
/*6698*/        OPC_MoveChild, 1,
/*6700*/        OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*6703*/        OPC_Scope, 19, /*->6724*/ // 5 children in Scope
/*6705*/          OPC_CheckPredicate, 64, // Predicate_immZExt16
/*6707*/          OPC_MoveParent,
/*6708*/          OPC_CheckType, MVT::i32,
/*6710*/          OPC_EmitConvertToTarget, 1,
/*6712*/          OPC_EmitNodeXForm, 1, 2, // LO16
/*6715*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ORI), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 3, 
                  // Src: (or:i32 GPRC:i32:$src1, (imm:i32)<<P:Predicate_immZExt16>><<X:LO16>>:$src2) - Complexity = 7
                  // Dst: (ORI:i32 GPRC:i32:$src1, (LO16:i32 (imm:i32):$src2))
/*6724*/        /*Scope*/ 19, /*->6744*/
/*6725*/          OPC_CheckPredicate, 65, // Predicate_imm16ShiftedZExt
/*6727*/          OPC_MoveParent,
/*6728*/          OPC_CheckType, MVT::i32,
/*6730*/          OPC_EmitConvertToTarget, 1,
/*6732*/          OPC_EmitNodeXForm, 0, 2, // HI16
/*6735*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ORIS), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 3, 
                  // Src: (or:i32 GPRC:i32:$src1, (imm:i32)<<P:Predicate_imm16ShiftedZExt>><<X:HI16>>:$src2) - Complexity = 7
                  // Dst: (ORIS:i32 GPRC:i32:$src1, (HI16:i32 (imm:i32):$src2))
/*6744*/        /*Scope*/ 19, /*->6764*/
/*6745*/          OPC_CheckPredicate, 64, // Predicate_immZExt16
/*6747*/          OPC_MoveParent,
/*6748*/          OPC_CheckType, MVT::i64,
/*6750*/          OPC_EmitConvertToTarget, 1,
/*6752*/          OPC_EmitNodeXForm, 1, 2, // LO16
/*6755*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ORI8), 0,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 3, 
                  // Src: (or:i64 G8RC:i64:$src1, (imm:i64)<<P:Predicate_immZExt16>><<X:LO16>>:$src2) - Complexity = 7
                  // Dst: (ORI8:i64 G8RC:i64:$src1, (LO16:i32 (imm:i64):$src2))
/*6764*/        /*Scope*/ 19, /*->6784*/
/*6765*/          OPC_CheckPredicate, 65, // Predicate_imm16ShiftedZExt
/*6767*/          OPC_MoveParent,
/*6768*/          OPC_CheckType, MVT::i64,
/*6770*/          OPC_EmitConvertToTarget, 1,
/*6772*/          OPC_EmitNodeXForm, 0, 2, // HI16
/*6775*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ORIS8), 0,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 3, 
                  // Src: (or:i64 G8RC:i64:$src1, (imm:i64)<<P:Predicate_imm16ShiftedZExt>><<X:HI16>>:$src2) - Complexity = 7
                  // Dst: (ORIS8:i64 G8RC:i64:$src1, (HI16:i32 (imm:i64):$src2))
/*6784*/        /*Scope*/ 31, /*->6816*/
/*6785*/          OPC_MoveParent,
/*6786*/          OPC_CheckType, MVT::i32,
/*6788*/          OPC_EmitConvertToTarget, 1,
/*6790*/          OPC_EmitNodeXForm, 1, 2, // LO16
/*6793*/          OPC_EmitNode, TARGET_VAL(PPC::ORI), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 3,  // Results = #4
/*6802*/          OPC_EmitConvertToTarget, 1,
/*6804*/          OPC_EmitNodeXForm, 0, 5, // HI16
/*6807*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ORIS), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 4, 6, 
                  // Src: (or:i32 GPRC:i32:$in, (imm:i32):$imm) - Complexity = 6
                  // Dst: (ORIS:i32 (ORI:i32 GPRC:i32:$in, (LO16:i32 (imm:i32):$imm)), (HI16:i32 (imm:i32):$imm))
/*6816*/        0, /*End of Scope*/
/*6817*/      /*Scope*/ 11, /*->6829*/
/*6818*/        OPC_CheckType, MVT::i32,
/*6820*/        OPC_MorphNodeTo, TARGET_VAL(PPC::OR), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (or:i32 GPRC:i32:$rS, GPRC:i32:$rB) - Complexity = 3
                // Dst: (OR:i32 GPRC:i32:$rS, GPRC:i32:$rB)
/*6829*/      /*Scope*/ 11, /*->6841*/
/*6830*/        OPC_CheckType, MVT::i64,
/*6832*/        OPC_MorphNodeTo, TARGET_VAL(PPC::OR8), 0,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                // Src: (or:i64 G8RC:i64:$rS, G8RC:i64:$rB) - Complexity = 3
                // Dst: (OR8:i64 G8RC:i64:$rS, G8RC:i64:$rB)
/*6841*/      /*Scope*/ 11, /*->6853*/
/*6842*/        OPC_CheckType, MVT::v4i32,
/*6844*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VOR), 0,
                    1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
                // Src: (or:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 3
                // Dst: (VOR:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*6853*/      0, /*End of Scope*/
/*6854*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 30|128,1/*158*/,  TARGET_VAL(PPCISD::Hi),// ->7017
/*6859*/    OPC_RecordChild0, // #0 = $in
/*6860*/    OPC_MoveChild, 0,
/*6862*/    OPC_SwitchOpcode /*5 cases */, 28,  TARGET_VAL(ISD::TargetGlobalAddress),// ->6894
/*6866*/      OPC_MoveParent,
/*6867*/      OPC_MoveChild, 1,
/*6869*/      OPC_CheckInteger, 0, 
/*6871*/      OPC_MoveParent,
/*6872*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->6883
/*6875*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (PPChi:i32 (tglobaladdr:i32):$in, 0:i32) - Complexity = 11
                // Dst: (LIS:i32 (tglobaladdr:i32):$in)
              /*SwitchType*/ 8,  MVT::i64,// ->6893
/*6885*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (PPChi:i64 (tglobaladdr:i64):$in, 0:i64) - Complexity = 11
                // Dst: (LIS8:i64 (tglobaladdr:i64):$in)
              0, // EndSwitchType
            /*SwitchOpcode*/ 28,  TARGET_VAL(ISD::TargetConstantPool),// ->6925
/*6897*/      OPC_MoveParent,
/*6898*/      OPC_MoveChild, 1,
/*6900*/      OPC_CheckInteger, 0, 
/*6902*/      OPC_MoveParent,
/*6903*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->6914
/*6906*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (PPChi:i32 (tconstpool:i32):$in, 0:i32) - Complexity = 11
                // Dst: (LIS:i32 (tconstpool:i32):$in)
              /*SwitchType*/ 8,  MVT::i64,// ->6924
/*6916*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (PPChi:i64 (tconstpool:i64):$in, 0:i64) - Complexity = 11
                // Dst: (LIS8:i64 (tconstpool:i64):$in)
              0, // EndSwitchType
            /*SwitchOpcode*/ 28,  TARGET_VAL(ISD::TargetJumpTable),// ->6956
/*6928*/      OPC_MoveParent,
/*6929*/      OPC_MoveChild, 1,
/*6931*/      OPC_CheckInteger, 0, 
/*6933*/      OPC_MoveParent,
/*6934*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->6945
/*6937*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (PPChi:i32 (tjumptable:i32):$in, 0:i32) - Complexity = 11
                // Dst: (LIS:i32 (tjumptable:i32):$in)
              /*SwitchType*/ 8,  MVT::i64,// ->6955
/*6947*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (PPChi:i64 (tjumptable:i64):$in, 0:i64) - Complexity = 11
                // Dst: (LIS8:i64 (tjumptable:i64):$in)
              0, // EndSwitchType
            /*SwitchOpcode*/ 28,  TARGET_VAL(ISD::TargetBlockAddress),// ->6987
/*6959*/      OPC_MoveParent,
/*6960*/      OPC_MoveChild, 1,
/*6962*/      OPC_CheckInteger, 0, 
/*6964*/      OPC_MoveParent,
/*6965*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->6976
/*6968*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (PPChi:i32 (tblockaddress:i32):$in, 0:i32) - Complexity = 11
                // Dst: (LIS:i32 (tblockaddress:i32):$in)
              /*SwitchType*/ 8,  MVT::i64,// ->6986
/*6978*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (PPChi:i64 (tblockaddress:i64):$in, 0:i64) - Complexity = 11
                // Dst: (LIS8:i64 (tblockaddress:i64):$in)
              0, // EndSwitchType
            /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::TargetGlobalTLSAddress),// ->7016
/*6990*/      OPC_MoveParent,
/*6991*/      OPC_RecordChild1, // #1 = $in
/*6992*/      OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->7004
/*6995*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                // Src: (PPChi:i32 (tglobaltlsaddr:i32):$g, GPRC:i32:$in) - Complexity = 6
                // Dst: (ADDIS:i32 GPRC:i32:$in, (tglobaltlsaddr:i32):$g)
              /*SwitchType*/ 9,  MVT::i64,// ->7015
/*7006*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIS8), 0,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                // Src: (PPChi:i64 (tglobaltlsaddr:i64):$g, G8RC:i64:$in) - Complexity = 6
                // Dst: (ADDIS8:i64 G8RC:i64:$in, (tglobaltlsaddr:i64):$g)
              0, // EndSwitchType
            0, // EndSwitchOpcode
          /*SwitchOpcode*/ 30|128,1/*158*/,  TARGET_VAL(PPCISD::Lo),// ->7179
/*7021*/    OPC_RecordChild0, // #0 = $in
/*7022*/    OPC_MoveChild, 0,
/*7024*/    OPC_SwitchOpcode /*5 cases */, 28,  TARGET_VAL(ISD::TargetGlobalAddress),// ->7056
/*7028*/      OPC_MoveParent,
/*7029*/      OPC_MoveChild, 1,
/*7031*/      OPC_CheckInteger, 0, 
/*7033*/      OPC_MoveParent,
/*7034*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->7045
/*7037*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (PPClo:i32 (tglobaladdr:i32):$in, 0:i32) - Complexity = 11
                // Dst: (LI:i32 (tglobaladdr:i32):$in)
              /*SwitchType*/ 8,  MVT::i64,// ->7055
/*7047*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (PPClo:i64 (tglobaladdr:i64):$in, 0:i64) - Complexity = 11
                // Dst: (LI8:i64 (tglobaladdr:i64):$in)
              0, // EndSwitchType
            /*SwitchOpcode*/ 28,  TARGET_VAL(ISD::TargetConstantPool),// ->7087
/*7059*/      OPC_MoveParent,
/*7060*/      OPC_MoveChild, 1,
/*7062*/      OPC_CheckInteger, 0, 
/*7064*/      OPC_MoveParent,
/*7065*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->7076
/*7068*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (PPClo:i32 (tconstpool:i32):$in, 0:i32) - Complexity = 11
                // Dst: (LI:i32 (tconstpool:i32):$in)
              /*SwitchType*/ 8,  MVT::i64,// ->7086
/*7078*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (PPClo:i64 (tconstpool:i64):$in, 0:i64) - Complexity = 11
                // Dst: (LI8:i64 (tconstpool:i64):$in)
              0, // EndSwitchType
            /*SwitchOpcode*/ 28,  TARGET_VAL(ISD::TargetJumpTable),// ->7118
/*7090*/      OPC_MoveParent,
/*7091*/      OPC_MoveChild, 1,
/*7093*/      OPC_CheckInteger, 0, 
/*7095*/      OPC_MoveParent,
/*7096*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->7107
/*7099*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (PPClo:i32 (tjumptable:i32):$in, 0:i32) - Complexity = 11
                // Dst: (LI:i32 (tjumptable:i32):$in)
              /*SwitchType*/ 8,  MVT::i64,// ->7117
/*7109*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (PPClo:i64 (tjumptable:i64):$in, 0:i64) - Complexity = 11
                // Dst: (LI8:i64 (tjumptable:i64):$in)
              0, // EndSwitchType
            /*SwitchOpcode*/ 28,  TARGET_VAL(ISD::TargetBlockAddress),// ->7149
/*7121*/      OPC_MoveParent,
/*7122*/      OPC_MoveChild, 1,
/*7124*/      OPC_CheckInteger, 0, 
/*7126*/      OPC_MoveParent,
/*7127*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->7138
/*7130*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (PPClo:i32 (tblockaddress:i32):$in, 0:i32) - Complexity = 11
                // Dst: (LI:i32 (tblockaddress:i32):$in)
              /*SwitchType*/ 8,  MVT::i64,// ->7148
/*7140*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (PPClo:i64 (tblockaddress:i64):$in, 0:i64) - Complexity = 11
                // Dst: (LI8:i64 (tblockaddress:i64):$in)
              0, // EndSwitchType
            /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::TargetGlobalTLSAddress),// ->7178
/*7152*/      OPC_MoveParent,
/*7153*/      OPC_RecordChild1, // #1 = $in
/*7154*/      OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->7166
/*7157*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIL), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                // Src: (PPClo:i32 (tglobaltlsaddr:i32):$g, GPRC:i32:$in) - Complexity = 6
                // Dst: (ADDIL:i32 GPRC:i32:$in, (tglobaltlsaddr:i32):$g)
              /*SwitchType*/ 9,  MVT::i64,// ->7177
/*7168*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADDI8L), 0,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                // Src: (PPClo:i64 (tglobaltlsaddr:i64):$g, G8RC:i64:$in) - Complexity = 6
                // Dst: (ADDI8L:i64 G8RC:i64:$in, (tglobaltlsaddr:i64):$g)
              0, // EndSwitchType
            0, // EndSwitchOpcode
          /*SwitchOpcode*/ 40,  TARGET_VAL(PPCISD::STCX),// ->7222
/*7182*/    OPC_RecordNode,   // #0 = 'PPCstcx' chained node
/*7183*/    OPC_RecordChild1, // #1 = $rS
/*7184*/    OPC_Scope, 17, /*->7203*/ // 2 children in Scope
/*7186*/      OPC_CheckChild1Type, MVT::i32,
/*7188*/      OPC_RecordChild2, // #2 = $dst
/*7189*/      OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*7192*/      OPC_EmitMergeInputChains1_0,
/*7193*/      OPC_MorphNodeTo, TARGET_VAL(PPC::STWCX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::i32, 3/*#Ops*/, 1, 3, 4, 
              // Src: (PPCstcx GPRC:i32:$rS, xoaddr:iPTR:$dst) - Complexity = 12
              // Dst: (STWCX:i32 GPRC:i32:$rS, xoaddr:iPTR:$dst)
/*7203*/    /*Scope*/ 17, /*->7221*/
/*7204*/      OPC_CheckChild1Type, MVT::i64,
/*7206*/      OPC_RecordChild2, // #2 = $dst
/*7207*/      OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*7210*/      OPC_EmitMergeInputChains1_0,
/*7211*/      OPC_MorphNodeTo, TARGET_VAL(PPC::STDCX), 0|OPFL_Chain,
                  1/*#VTs*/, MVT::i32, 3/*#Ops*/, 1, 3, 4, 
              // Src: (PPCstcx G8RC:i64:$rS, xoaddr:iPTR:$dst) - Complexity = 12
              // Dst: (STDCX:i32 G8RC:i64:$rS, xoaddr:iPTR:$dst)
/*7221*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 41,  TARGET_VAL(PPCISD::STBRX),// ->7266
/*7225*/    OPC_RecordNode,   // #0 = 'PPCstbrx' chained node
/*7226*/    OPC_RecordChild1, // #1 = $rS
/*7227*/    OPC_RecordChild2, // #2 = $dst
/*7228*/    OPC_MoveChild, 3,
/*7230*/    OPC_Scope, 16, /*->7248*/ // 2 children in Scope
/*7232*/      OPC_CheckValueType, MVT::i16,
/*7234*/      OPC_MoveParent,
/*7235*/      OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*7238*/      OPC_EmitMergeInputChains1_0,
/*7239*/      OPC_MorphNodeTo, TARGET_VAL(PPC::STHBRX), 0|OPFL_Chain,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (PPCstbrx GPRC:i32:$rS, xoaddr:iPTR:$dst, i16:Other) - Complexity = 12
              // Dst: (STHBRX GPRC:i32:$rS, xoaddr:iPTR:$dst)
/*7248*/    /*Scope*/ 16, /*->7265*/
/*7249*/      OPC_CheckValueType, MVT::i32,
/*7251*/      OPC_MoveParent,
/*7252*/      OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*7255*/      OPC_EmitMergeInputChains1_0,
/*7256*/      OPC_MorphNodeTo, TARGET_VAL(PPC::STWBRX), 0|OPFL_Chain,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (PPCstbrx GPRC:i32:$rS, xoaddr:iPTR:$dst, i32:Other) - Complexity = 12
              // Dst: (STWBRX GPRC:i32:$rS, xoaddr:iPTR:$dst)
/*7265*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 16,  TARGET_VAL(PPCISD::STFIWX),// ->7285
/*7269*/    OPC_RecordNode,   // #0 = 'PPCstfiwx' chained node
/*7270*/    OPC_RecordChild1, // #1 = $frS
/*7271*/    OPC_RecordChild2, // #2 = $dst
/*7272*/    OPC_CheckComplexPat, /*CP*/0, /*#*/2, // SelectAddrIdxOnly:$dst #3 #4
/*7275*/    OPC_EmitMergeInputChains1_0,
/*7276*/    OPC_MorphNodeTo, TARGET_VAL(PPC::STFIWX), 0|OPFL_Chain,
                0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
            // Src: (PPCstfiwx F8RC:f64:$frS, xoaddr:iPTR:$dst) - Complexity = 12
            // Dst: (STFIWX F8RC:f64:$frS, xoaddr:iPTR:$dst)
          /*SwitchOpcode*/ 35,  TARGET_VAL(PPCISD::STD_32),// ->7323
/*7288*/    OPC_RecordNode,   // #0 = 'PPCstd_32' chained node
/*7289*/    OPC_RecordChild1, // #1 = $rT
/*7290*/    OPC_CheckChild1Type, MVT::i32,
/*7292*/    OPC_RecordChild2, // #2 = $dst
/*7293*/    OPC_Scope, 13, /*->7308*/ // 2 children in Scope
/*7295*/      OPC_CheckComplexPat, /*CP*/3, /*#*/2, // SelectAddrImmShift:$dst #3 #4
/*7298*/      OPC_EmitMergeInputChains1_0,
/*7299*/      OPC_MorphNodeTo, TARGET_VAL(PPC::STD_32), 0|OPFL_Chain,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (PPCstd_32 GPRC:i32:$rT, ixaddr:iPTR:$dst) - Complexity = 12
              // Dst: (STD_32 GPRC:i32:$rT, ixaddr:iPTR:$dst)
/*7308*/    /*Scope*/ 13, /*->7322*/
/*7309*/      OPC_CheckComplexPat, /*CP*/2, /*#*/2, // SelectAddrIdx:$dst #3 #4
/*7312*/      OPC_EmitMergeInputChains1_0,
/*7313*/      OPC_MorphNodeTo, TARGET_VAL(PPC::STDX_32), 0|OPFL_Chain,
                  0/*#VTs*/, 3/*#Ops*/, 1, 3, 4, 
              // Src: (PPCstd_32 GPRC:i32:$rT, xaddr:iPTR:$dst) - Complexity = 12
              // Dst: (STDX_32 GPRC:i32:$rT, xaddr:iPTR:$dst)
/*7322*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::CALLSEQ_END),// ->7352
/*7326*/    OPC_RecordNode,   // #0 = 'callseq_end' chained node
/*7327*/    OPC_CaptureGlueInput,
/*7328*/    OPC_RecordChild1, // #1 = $amt1
/*7329*/    OPC_MoveChild, 1,
/*7331*/    OPC_CheckOpcode, TARGET_VAL(ISD::TargetConstant),
/*7334*/    OPC_MoveParent,
/*7335*/    OPC_RecordChild2, // #2 = $amt2
/*7336*/    OPC_MoveChild, 2,
/*7338*/    OPC_CheckOpcode, TARGET_VAL(ISD::TargetConstant),
/*7341*/    OPC_MoveParent,
/*7342*/    OPC_EmitMergeInputChains1_0,
/*7343*/    OPC_MorphNodeTo, TARGET_VAL(PPC::ADJCALLSTACKUP), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput,
                1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 2, 
            // Src: (callseq_end (timm:i32):$amt1, (timm:i32):$amt2) - Complexity = 9
            // Dst: (ADJCALLSTACKUP:i32 (timm:i32):$amt1, (timm:i32):$amt2)
          /*SwitchOpcode*/ 70|128,1/*198*/,  TARGET_VAL(PPCISD::TC_RETURN),// ->7554
/*7356*/    OPC_RecordNode,   // #0 = 'PPCtc_return' chained node
/*7357*/    OPC_CaptureGlueInput,
/*7358*/    OPC_RecordChild1, // #1 = $func
/*7359*/    OPC_Scope, 21|128,1/*149*/, /*->7511*/ // 3 children in Scope
/*7362*/      OPC_MoveChild, 1,
/*7364*/      OPC_SwitchOpcode /*3 cases */, 48,  TARGET_VAL(ISD::Constant),// ->7416
/*7368*/        OPC_SwitchType /*2 cases */, 21,  MVT::i32,// ->7392
/*7371*/          OPC_MoveParent,
/*7372*/          OPC_RecordChild2, // #2 = $offset
/*7373*/          OPC_MoveChild, 2,
/*7375*/          OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7378*/          OPC_MoveParent,
/*7379*/          OPC_EmitMergeInputChains1_0,
/*7380*/          OPC_EmitConvertToTarget, 1,
/*7382*/          OPC_EmitConvertToTarget, 2,
/*7384*/          OPC_MorphNodeTo, TARGET_VAL(PPC::TCRETURNai), 0|OPFL_Chain|OPFL_GlueInput|OPFL_Variadic2,
                      0/*#VTs*/, 2/*#Ops*/, 3, 4, 
                  // Src: (PPCtc_return (imm:i32):$func, (imm:i32):$offset) - Complexity = 9
                  // Dst: (TCRETURNai (imm:i32):$func, (imm:i32):$offset)
                /*SwitchType*/ 21,  MVT::i64,// ->7415
/*7394*/          OPC_MoveParent,
/*7395*/          OPC_RecordChild2, // #2 = $offset
/*7396*/          OPC_MoveChild, 2,
/*7398*/          OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7401*/          OPC_MoveParent,
/*7402*/          OPC_EmitMergeInputChains1_0,
/*7403*/          OPC_EmitConvertToTarget, 1,
/*7405*/          OPC_EmitConvertToTarget, 2,
/*7407*/          OPC_MorphNodeTo, TARGET_VAL(PPC::TCRETURNai8), 0|OPFL_Chain|OPFL_GlueInput|OPFL_Variadic2,
                      0/*#VTs*/, 2/*#Ops*/, 3, 4, 
                  // Src: (PPCtc_return (imm:i64):$func, (imm:i32):$offset) - Complexity = 9
                  // Dst: (TCRETURNai8 (imm:i64):$func, (imm:i32):$offset)
                0, // EndSwitchType
              /*SwitchOpcode*/ 44,  TARGET_VAL(ISD::TargetGlobalAddress),// ->7463
/*7419*/        OPC_SwitchType /*2 cases */, 19,  MVT::i32,// ->7441
/*7422*/          OPC_MoveParent,
/*7423*/          OPC_RecordChild2, // #2 = $imm
/*7424*/          OPC_MoveChild, 2,
/*7426*/          OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7429*/          OPC_MoveParent,
/*7430*/          OPC_EmitMergeInputChains1_0,
/*7431*/          OPC_EmitConvertToTarget, 2,
/*7433*/          OPC_MorphNodeTo, TARGET_VAL(PPC::TCRETURNdi), 0|OPFL_Chain|OPFL_GlueInput|OPFL_Variadic2,
                      0/*#VTs*/, 2/*#Ops*/, 1, 3, 
                  // Src: (PPCtc_return (tglobaladdr:i32):$dst, (imm:i32):$imm) - Complexity = 9
                  // Dst: (TCRETURNdi (tglobaladdr:i32):$dst, (imm:i32):$imm)
                /*SwitchType*/ 19,  MVT::i64,// ->7462
/*7443*/          OPC_MoveParent,
/*7444*/          OPC_RecordChild2, // #2 = $imm
/*7445*/          OPC_MoveChild, 2,
/*7447*/          OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7450*/          OPC_MoveParent,
/*7451*/          OPC_EmitMergeInputChains1_0,
/*7452*/          OPC_EmitConvertToTarget, 2,
/*7454*/          OPC_MorphNodeTo, TARGET_VAL(PPC::TCRETURNdi8), 0|OPFL_Chain|OPFL_GlueInput|OPFL_Variadic2,
                      0/*#VTs*/, 2/*#Ops*/, 1, 3, 
                  // Src: (PPCtc_return (tglobaladdr:i64):$dst, (imm:i32):$imm) - Complexity = 9
                  // Dst: (TCRETURNdi8 (tglobaladdr:i64):$dst, (imm:i32):$imm)
                0, // EndSwitchType
              /*SwitchOpcode*/ 44,  TARGET_VAL(ISD::TargetExternalSymbol),// ->7510
/*7466*/        OPC_SwitchType /*2 cases */, 19,  MVT::i32,// ->7488
/*7469*/          OPC_MoveParent,
/*7470*/          OPC_RecordChild2, // #2 = $imm
/*7471*/          OPC_MoveChild, 2,
/*7473*/          OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7476*/          OPC_MoveParent,
/*7477*/          OPC_EmitMergeInputChains1_0,
/*7478*/          OPC_EmitConvertToTarget, 2,
/*7480*/          OPC_MorphNodeTo, TARGET_VAL(PPC::TCRETURNdi), 0|OPFL_Chain|OPFL_GlueInput|OPFL_Variadic2,
                      0/*#VTs*/, 2/*#Ops*/, 1, 3, 
                  // Src: (PPCtc_return (texternalsym:i32):$dst, (imm:i32):$imm) - Complexity = 9
                  // Dst: (TCRETURNdi (texternalsym:i32):$dst, (imm:i32):$imm)
                /*SwitchType*/ 19,  MVT::i64,// ->7509
/*7490*/          OPC_MoveParent,
/*7491*/          OPC_RecordChild2, // #2 = $imm
/*7492*/          OPC_MoveChild, 2,
/*7494*/          OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7497*/          OPC_MoveParent,
/*7498*/          OPC_EmitMergeInputChains1_0,
/*7499*/          OPC_EmitConvertToTarget, 2,
/*7501*/          OPC_MorphNodeTo, TARGET_VAL(PPC::TCRETURNdi8), 0|OPFL_Chain|OPFL_GlueInput|OPFL_Variadic2,
                      0/*#VTs*/, 2/*#Ops*/, 1, 3, 
                  // Src: (PPCtc_return (texternalsym:i64):$dst, (imm:i32):$imm) - Complexity = 9
                  // Dst: (TCRETURNdi8 (texternalsym:i64):$dst, (imm:i32):$imm)
                0, // EndSwitchType
              0, // EndSwitchOpcode
/*7511*/    /*Scope*/ 20, /*->7532*/
/*7512*/      OPC_CheckChild1Type, MVT::i32,
/*7514*/      OPC_RecordChild2, // #2 = $imm
/*7515*/      OPC_MoveChild, 2,
/*7517*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7520*/      OPC_MoveParent,
/*7521*/      OPC_EmitMergeInputChains1_0,
/*7522*/      OPC_EmitConvertToTarget, 2,
/*7524*/      OPC_MorphNodeTo, TARGET_VAL(PPC::TCRETURNri), 0|OPFL_Chain|OPFL_GlueInput|OPFL_Variadic2,
                  0/*#VTs*/, 2/*#Ops*/, 1, 3, 
              // Src: (PPCtc_return CTRRC:i32:$dst, (imm:i32):$imm) - Complexity = 6
              // Dst: (TCRETURNri CTRRC:i32:$dst, (imm:i32):$imm)
/*7532*/    /*Scope*/ 20, /*->7553*/
/*7533*/      OPC_CheckChild1Type, MVT::i64,
/*7535*/      OPC_RecordChild2, // #2 = $imm
/*7536*/      OPC_MoveChild, 2,
/*7538*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7541*/      OPC_MoveParent,
/*7542*/      OPC_EmitMergeInputChains1_0,
/*7543*/      OPC_EmitConvertToTarget, 2,
/*7545*/      OPC_MorphNodeTo, TARGET_VAL(PPC::TCRETURNri8), 0|OPFL_Chain|OPFL_GlueInput|OPFL_Variadic2,
                  0/*#VTs*/, 2/*#Ops*/, 1, 3, 
              // Src: (PPCtc_return CTRRC8:i64:$dst, (imm:i32):$imm) - Complexity = 6
              // Dst: (TCRETURNri8 CTRRC8:i64:$dst, (imm:i32):$imm)
/*7553*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 20,  TARGET_VAL(ISD::ATOMIC_FENCE),// ->7577
/*7557*/    OPC_RecordNode,   // #0 = 'atomic_fence' chained node
/*7558*/    OPC_MoveChild, 1,
/*7560*/    OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7563*/    OPC_MoveParent,
/*7564*/    OPC_MoveChild, 2,
/*7566*/    OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7569*/    OPC_MoveParent,
/*7570*/    OPC_EmitMergeInputChains1_0,
/*7571*/    OPC_MorphNodeTo, TARGET_VAL(PPC::SYNC), 0|OPFL_Chain,
                0/*#VTs*/, 0/*#Ops*/, 
            // Src: (atomic_fence (imm:iPTR), (imm:iPTR)) - Complexity = 9
            // Dst: (SYNC)
          /*SwitchOpcode*/ 118,  TARGET_VAL(ISD::SUB),// ->7698
/*7580*/    OPC_Scope, 28, /*->7610*/ // 2 children in Scope
/*7582*/      OPC_MoveChild, 0,
/*7584*/      OPC_CheckInteger, 0, 
/*7586*/      OPC_MoveParent,
/*7587*/      OPC_RecordChild1, // #0 = $rA
/*7588*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->7599
/*7591*/        OPC_MorphNodeTo, TARGET_VAL(PPC::NEG), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (sub:i32 0:i32, GPRC:i32:$rA) - Complexity = 8
                // Dst: (NEG:i32 GPRC:i32:$rA)
              /*SwitchType*/ 8,  MVT::i64,// ->7609
/*7601*/        OPC_MorphNodeTo, TARGET_VAL(PPC::NEG8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (sub:i64 0:i64, G8RC:i64:$rA) - Complexity = 8
                // Dst: (NEG8:i64 G8RC:i64:$rA)
              0, // EndSwitchType
/*7610*/    /*Scope*/ 86, /*->7697*/
/*7611*/      OPC_RecordChild0, // #0 = $imm
/*7612*/      OPC_Scope, 23, /*->7637*/ // 2 children in Scope
/*7614*/        OPC_MoveChild, 0,
/*7616*/        OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7619*/        OPC_CheckPredicate, 0, // Predicate_immSExt16
/*7621*/        OPC_MoveParent,
/*7622*/        OPC_RecordChild1, // #1 = $in
/*7623*/        OPC_CheckType, MVT::i32,
/*7625*/        OPC_EmitConvertToTarget, 0,
/*7627*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFIC), 0,
                    2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 1, 2, 
                // Src: (sub:i32 (imm:i32)<<P:Predicate_immSExt16>>:$imm, GPRC:i32:$in) - Complexity = 7
                // Dst: (SUBFIC:i32:i32 GPRC:i32:$in, (imm:i32):$imm)
/*7637*/      /*Scope*/ 58, /*->7696*/
/*7638*/        OPC_RecordChild1, // #1 = $rA
/*7639*/        OPC_SwitchType /*5 cases */, 9,  MVT::i32,// ->7651
/*7642*/          OPC_MorphNodeTo, TARGET_VAL(PPC::SUBF), 0,
                      1/*#VTs*/, MVT::i32, 2/*#Ops*/, 1, 0, 
                  // Src: (sub:i32 GPRC:i32:$rB, GPRC:i32:$rA) - Complexity = 3
                  // Dst: (SUBF:i32 GPRC:i32:$rA, GPRC:i32:$rB)
                /*SwitchType*/ 9,  MVT::i64,// ->7662
/*7653*/          OPC_MorphNodeTo, TARGET_VAL(PPC::SUBF8), 0,
                      1/*#VTs*/, MVT::i64, 2/*#Ops*/, 1, 0, 
                  // Src: (sub:i64 G8RC:i64:$rB, G8RC:i64:$rA) - Complexity = 3
                  // Dst: (SUBF8:i64 G8RC:i64:$rA, G8RC:i64:$rB)
                /*SwitchType*/ 9,  MVT::v16i8,// ->7673
/*7664*/          OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBUBM), 0,
                      1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                  // Src: (sub:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 3
                  // Dst: (VSUBUBM:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
                /*SwitchType*/ 9,  MVT::v8i16,// ->7684
/*7675*/          OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBUHM), 0,
                      1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
                  // Src: (sub:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 3
                  // Dst: (VSUBUHM:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
                /*SwitchType*/ 9,  MVT::v4i32,// ->7695
/*7686*/          OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBUWM), 0,
                      1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
                  // Src: (sub:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 3
                  // Dst: (VSUBUWM:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
                0, // EndSwitchType
/*7696*/      0, /*End of Scope*/
/*7697*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 102,  TARGET_VAL(ISD::ADDE),// ->7803
/*7701*/    OPC_CaptureGlueInput,
/*7702*/    OPC_RecordChild0, // #0 = $rA
/*7703*/    OPC_Scope, 69, /*->7774*/ // 2 children in Scope
/*7705*/      OPC_MoveChild, 1,
/*7707*/      OPC_Scope, 36, /*->7745*/ // 2 children in Scope
/*7709*/        OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*7720*/        OPC_MoveParent,
/*7721*/        OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->7733
/*7724*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ADDME), 0|OPFL_GlueInput|OPFL_GlueOutput,
                      2/*#VTs*/, MVT::i32, MVT::i32, 1/*#Ops*/, 0, 
                  // Src: (adde:i32 GPRC:i32:$rA, -1:i32) - Complexity = 8
                  // Dst: (ADDME:i32:i32 GPRC:i32:$rA)
                /*SwitchType*/ 9,  MVT::i64,// ->7744
/*7735*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ADDME8), 0|OPFL_GlueInput|OPFL_GlueOutput,
                      2/*#VTs*/, MVT::i64, MVT::i32, 1/*#Ops*/, 0, 
                  // Src: (adde:i64 G8RC:i64:$rA, -1:i64) - Complexity = 8
                  // Dst: (ADDME8:i64:i32 G8RC:i64:$rA)
                0, // EndSwitchType
/*7745*/      /*Scope*/ 27, /*->7773*/
/*7746*/        OPC_CheckInteger, 0, 
/*7748*/        OPC_MoveParent,
/*7749*/        OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->7761
/*7752*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ADDZE), 0|OPFL_GlueInput|OPFL_GlueOutput,
                      2/*#VTs*/, MVT::i32, MVT::i32, 1/*#Ops*/, 0, 
                  // Src: (adde:i32 GPRC:i32:$rA, 0:i32) - Complexity = 8
                  // Dst: (ADDZE:i32:i32 GPRC:i32:$rA)
                /*SwitchType*/ 9,  MVT::i64,// ->7772
/*7763*/          OPC_MorphNodeTo, TARGET_VAL(PPC::ADDZE8), 0|OPFL_GlueInput|OPFL_GlueOutput,
                      2/*#VTs*/, MVT::i64, MVT::i32, 1/*#Ops*/, 0, 
                  // Src: (adde:i64 G8RC:i64:$rA, 0:i64) - Complexity = 8
                  // Dst: (ADDZE8:i64:i32 G8RC:i64:$rA)
                0, // EndSwitchType
/*7773*/      0, /*End of Scope*/
/*7774*/    /*Scope*/ 27, /*->7802*/
/*7775*/      OPC_RecordChild1, // #1 = $rB
/*7776*/      OPC_SwitchType /*2 cases */, 10,  MVT::i32,// ->7789
/*7779*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADDE), 0|OPFL_GlueInput|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (adde:i32 GPRC:i32:$rA, GPRC:i32:$rB) - Complexity = 3
                // Dst: (ADDE:i32:i32 GPRC:i32:$rA, GPRC:i32:$rB)
              /*SwitchType*/ 10,  MVT::i64,// ->7801
/*7791*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADDE8), 0|OPFL_GlueInput|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (adde:i64 G8RC:i64:$rA, G8RC:i64:$rB) - Complexity = 3
                // Dst: (ADDE8:i64:i32 G8RC:i64:$rA, G8RC:i64:$rB)
              0, // EndSwitchType
/*7802*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 104,  TARGET_VAL(ISD::SUBE),// ->7910
/*7806*/    OPC_CaptureGlueInput,
/*7807*/    OPC_Scope, 71, /*->7880*/ // 2 children in Scope
/*7809*/      OPC_MoveChild, 0,
/*7811*/      OPC_Scope, 37, /*->7850*/ // 2 children in Scope
/*7813*/        OPC_CheckInteger, 127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,127|128,1/*18446744073709551615*/, 
/*7824*/        OPC_MoveParent,
/*7825*/        OPC_RecordChild1, // #0 = $rA
/*7826*/        OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->7838
/*7829*/          OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFME), 0|OPFL_GlueInput|OPFL_GlueOutput,
                      2/*#VTs*/, MVT::i32, MVT::i32, 1/*#Ops*/, 0, 
                  // Src: (sube:i32 -1:i32, GPRC:i32:$rA) - Complexity = 8
                  // Dst: (SUBFME:i32:i32 GPRC:i32:$rA)
                /*SwitchType*/ 9,  MVT::i64,// ->7849
/*7840*/          OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFME8), 0|OPFL_GlueInput|OPFL_GlueOutput,
                      2/*#VTs*/, MVT::i64, MVT::i32, 1/*#Ops*/, 0, 
                  // Src: (sube:i64 -1:i64, G8RC:i64:$rA) - Complexity = 8
                  // Dst: (SUBFME8:i64:i32 G8RC:i64:$rA)
                0, // EndSwitchType
/*7850*/      /*Scope*/ 28, /*->7879*/
/*7851*/        OPC_CheckInteger, 0, 
/*7853*/        OPC_MoveParent,
/*7854*/        OPC_RecordChild1, // #0 = $rA
/*7855*/        OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->7867
/*7858*/          OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFZE), 0|OPFL_GlueInput|OPFL_GlueOutput,
                      2/*#VTs*/, MVT::i32, MVT::i32, 1/*#Ops*/, 0, 
                  // Src: (sube:i32 0:i32, GPRC:i32:$rA) - Complexity = 8
                  // Dst: (SUBFZE:i32:i32 GPRC:i32:$rA)
                /*SwitchType*/ 9,  MVT::i64,// ->7878
/*7869*/          OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFZE8), 0|OPFL_GlueInput|OPFL_GlueOutput,
                      2/*#VTs*/, MVT::i64, MVT::i32, 1/*#Ops*/, 0, 
                  // Src: (sube:i64 0:i64, G8RC:i64:$rA) - Complexity = 8
                  // Dst: (SUBFZE8:i64:i32 G8RC:i64:$rA)
                0, // EndSwitchType
/*7879*/      0, /*End of Scope*/
/*7880*/    /*Scope*/ 28, /*->7909*/
/*7881*/      OPC_RecordChild0, // #0 = $rB
/*7882*/      OPC_RecordChild1, // #1 = $rA
/*7883*/      OPC_SwitchType /*2 cases */, 10,  MVT::i32,// ->7896
/*7886*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFE), 0|OPFL_GlueInput|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 1, 0, 
                // Src: (sube:i32 GPRC:i32:$rB, GPRC:i32:$rA) - Complexity = 3
                // Dst: (SUBFE:i32:i32 GPRC:i32:$rA, GPRC:i32:$rB)
              /*SwitchType*/ 10,  MVT::i64,// ->7908
/*7898*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFE8), 0|OPFL_GlueInput|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 1, 0, 
                // Src: (sube:i64 G8RC:i64:$rB, G8RC:i64:$rA) - Complexity = 3
                // Dst: (SUBFE8:i64:i32 G8RC:i64:$rA, G8RC:i64:$rB)
              0, // EndSwitchType
/*7909*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 69,  TARGET_VAL(ISD::ADDC),// ->7982
/*7913*/    OPC_RecordChild0, // #0 = $rA
/*7914*/    OPC_RecordChild1, // #1 = $imm
/*7915*/    OPC_Scope, 38, /*->7955*/ // 3 children in Scope
/*7917*/      OPC_MoveChild, 1,
/*7919*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7922*/      OPC_CheckPredicate, 0, // Predicate_immSExt16
/*7924*/      OPC_MoveParent,
/*7925*/      OPC_SwitchType /*2 cases */, 12,  MVT::i32,// ->7940
/*7928*/        OPC_EmitConvertToTarget, 1,
/*7930*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIC), 0|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 0, 2, 
                // Src: (addc:i32 GPRC:i32:$rA, (imm:i32)<<P:Predicate_immSExt16>>:$imm) - Complexity = 7
                // Dst: (ADDIC:i32:i32 GPRC:i32:$rA, (imm:i32):$imm)
              /*SwitchType*/ 12,  MVT::i64,// ->7954
/*7942*/        OPC_EmitConvertToTarget, 1,
/*7944*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ADDIC8), 0|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 0, 2, 
                // Src: (addc:i64 G8RC:i64:$rA, (imm:i64)<<P:Predicate_immSExt16>>:$imm) - Complexity = 7
                // Dst: (ADDIC8:i64:i32 G8RC:i64:$rA, (imm:i64):$imm)
              0, // EndSwitchType
/*7955*/    /*Scope*/ 12, /*->7968*/
/*7956*/      OPC_CheckType, MVT::i32,
/*7958*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ADDC), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (addc:i32 GPRC:i32:$rA, GPRC:i32:$rB) - Complexity = 3
              // Dst: (ADDC:i32:i32 GPRC:i32:$rA, GPRC:i32:$rB)
/*7968*/    /*Scope*/ 12, /*->7981*/
/*7969*/      OPC_CheckType, MVT::i64,
/*7971*/      OPC_MorphNodeTo, TARGET_VAL(PPC::ADDC8), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (addc:i64 G8RC:i64:$rA, G8RC:i64:$rB) - Complexity = 3
              // Dst: (ADDC8:i64:i32 G8RC:i64:$rA, G8RC:i64:$rB)
/*7981*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 50,  TARGET_VAL(ISD::MUL),// ->8035
/*7985*/    OPC_RecordChild0, // #0 = $rA
/*7986*/    OPC_RecordChild1, // #1 = $imm
/*7987*/    OPC_Scope, 21, /*->8010*/ // 3 children in Scope
/*7989*/      OPC_MoveChild, 1,
/*7991*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*7994*/      OPC_CheckPredicate, 0, // Predicate_immSExt16
/*7996*/      OPC_MoveParent,
/*7997*/      OPC_CheckType, MVT::i32,
/*7999*/      OPC_EmitConvertToTarget, 1,
/*8001*/      OPC_MorphNodeTo, TARGET_VAL(PPC::MULLI), 0,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 2, 
              // Src: (mul:i32 GPRC:i32:$rA, (imm:i32)<<P:Predicate_immSExt16>>:$imm) - Complexity = 7
              // Dst: (MULLI:i32 GPRC:i32:$rA, (imm:i32):$imm)
/*8010*/    /*Scope*/ 11, /*->8022*/
/*8011*/      OPC_CheckType, MVT::i32,
/*8013*/      OPC_MorphNodeTo, TARGET_VAL(PPC::MULLW), 0,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (mul:i32 GPRC:i32:$rA, GPRC:i32:$rB) - Complexity = 3
              // Dst: (MULLW:i32 GPRC:i32:$rA, GPRC:i32:$rB)
/*8022*/    /*Scope*/ 11, /*->8034*/
/*8023*/      OPC_CheckType, MVT::i64,
/*8025*/      OPC_MorphNodeTo, TARGET_VAL(PPC::MULLD), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (mul:i64 G8RC:i64:$rA, G8RC:i64:$rB) - Complexity = 3
              // Dst: (MULLD:i64 G8RC:i64:$rA, G8RC:i64:$rB)
/*8034*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 71,  TARGET_VAL(ISD::SUBC),// ->8109
/*8038*/    OPC_RecordChild0, // #0 = $imm
/*8039*/    OPC_Scope, 39, /*->8080*/ // 2 children in Scope
/*8041*/      OPC_MoveChild, 0,
/*8043*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*8046*/      OPC_CheckPredicate, 0, // Predicate_immSExt16
/*8048*/      OPC_MoveParent,
/*8049*/      OPC_RecordChild1, // #1 = $rA
/*8050*/      OPC_SwitchType /*2 cases */, 12,  MVT::i32,// ->8065
/*8053*/        OPC_EmitConvertToTarget, 0,
/*8055*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFIC), 0|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 1, 2, 
                // Src: (subc:i32 (imm:i32)<<P:Predicate_immSExt16>>:$imm, GPRC:i32:$rA) - Complexity = 7
                // Dst: (SUBFIC:i32:i32 GPRC:i32:$rA, (imm:i32):$imm)
              /*SwitchType*/ 12,  MVT::i64,// ->8079
/*8067*/        OPC_EmitConvertToTarget, 0,
/*8069*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFIC8), 0|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 1, 2, 
                // Src: (subc:i64 (imm:i64)<<P:Predicate_immSExt16>>:$imm, G8RC:i64:$rA) - Complexity = 7
                // Dst: (SUBFIC8:i64:i32 G8RC:i64:$rA, (imm:i64):$imm)
              0, // EndSwitchType
/*8080*/    /*Scope*/ 27, /*->8108*/
/*8081*/      OPC_RecordChild1, // #1 = $rA
/*8082*/      OPC_SwitchType /*2 cases */, 10,  MVT::i32,// ->8095
/*8085*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFC), 0|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 1, 0, 
                // Src: (subc:i32 GPRC:i32:$rB, GPRC:i32:$rA) - Complexity = 3
                // Dst: (SUBFC:i32:i32 GPRC:i32:$rA, GPRC:i32:$rB)
              /*SwitchType*/ 10,  MVT::i64,// ->8107
/*8097*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SUBFC8), 0|OPFL_GlueOutput,
                    2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 1, 0, 
                // Src: (subc:i64 G8RC:i64:$rB, G8RC:i64:$rA) - Complexity = 3
                // Dst: (SUBFC8:i64:i32 G8RC:i64:$rA, G8RC:i64:$rB)
              0, // EndSwitchType
/*8108*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 114,  TARGET_VAL(ISD::SRA),// ->8226
/*8112*/    OPC_RecordChild0, // #0 = $rS
/*8113*/    OPC_RecordChild1, // #1 = $SH
/*8114*/    OPC_Scope, 38, /*->8154*/ // 5 children in Scope
/*8116*/      OPC_MoveChild, 1,
/*8118*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*8121*/      OPC_CheckType, MVT::i32,
/*8123*/      OPC_MoveParent,
/*8124*/      OPC_SwitchType /*2 cases */, 12,  MVT::i32,// ->8139
/*8127*/        OPC_EmitConvertToTarget, 1,
/*8129*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SRAWI), 0,
                    2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 0, 2, 
                // Src: (sra:i32 GPRC:i32:$rS, (imm:i32):$SH) - Complexity = 6
                // Dst: (SRAWI:i32:i32 GPRC:i32:$rS, (imm:i32):$SH)
              /*SwitchType*/ 12,  MVT::i64,// ->8153
/*8141*/        OPC_EmitConvertToTarget, 1,
/*8143*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SRADI), 0,
                    2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 0, 2, 
                // Src: (sra:i64 G8RC:i64:$rS, (imm:i32):$SH) - Complexity = 6
                // Dst: (SRADI:i64:i32 G8RC:i64:$rS, (imm:i32):$SH)
              0, // EndSwitchType
/*8154*/    /*Scope*/ 28, /*->8183*/
/*8155*/      OPC_CheckChild1Type, MVT::i32,
/*8157*/      OPC_SwitchType /*2 cases */, 10,  MVT::i32,// ->8170
/*8160*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SRAW), 0,
                    2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (sra:i32 GPRC:i32:$rS, GPRC:i32:$rB) - Complexity = 3
                // Dst: (SRAW:i32:i32 GPRC:i32:$rS, GPRC:i32:$rB)
              /*SwitchType*/ 10,  MVT::i64,// ->8182
/*8172*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SRAD), 0,
                    2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (sra:i64 G8RC:i64:$rS, GPRC:i32:$rB) - Complexity = 3
                // Dst: (SRAD:i64:i32 G8RC:i64:$rS, GPRC:i32:$rB)
              0, // EndSwitchType
/*8183*/    /*Scope*/ 13, /*->8197*/
/*8184*/      OPC_CheckChild1Type, MVT::v16i8,
/*8186*/      OPC_CheckType, MVT::v16i8,
/*8188*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRAB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (sra:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 3
              // Dst: (VSRAB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*8197*/    /*Scope*/ 13, /*->8211*/
/*8198*/      OPC_CheckChild1Type, MVT::v8i16,
/*8200*/      OPC_CheckType, MVT::v8i16,
/*8202*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRAH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (sra:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 3
              // Dst: (VSRAH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*8211*/    /*Scope*/ 13, /*->8225*/
/*8212*/      OPC_CheckChild1Type, MVT::v4i32,
/*8214*/      OPC_CheckType, MVT::v4i32,
/*8216*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRAW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (sra:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 3
              // Dst: (VSRAW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*8225*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 126,  TARGET_VAL(ISD::SHL),// ->8355
/*8229*/    OPC_RecordChild0, // #0 = $in
/*8230*/    OPC_RecordChild1, // #1 = $imm
/*8231*/    OPC_Scope, 52, /*->8285*/ // 5 children in Scope
/*8233*/      OPC_MoveChild, 1,
/*8235*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*8238*/      OPC_CheckType, MVT::i32,
/*8240*/      OPC_MoveParent,
/*8241*/      OPC_SwitchType /*2 cases */, 21,  MVT::i32,// ->8265
/*8244*/        OPC_EmitConvertToTarget, 1,
/*8246*/        OPC_EmitInteger, MVT::i32, 0, 
/*8249*/        OPC_EmitConvertToTarget, 1,
/*8251*/        OPC_EmitNodeXForm, 5, 4, // SHL32
/*8254*/        OPC_MorphNodeTo, TARGET_VAL(PPC::RLWINM), 0,
                    1/*#VTs*/, MVT::i32, 4/*#Ops*/, 0, 2, 3, 5, 
                // Src: (shl:i32 GPRC:i32:$in, (imm:i32):$imm) - Complexity = 6
                // Dst: (RLWINM:i32 GPRC:i32:$in, (imm:i32):$imm, 0:i32, (SHL32:i32 (imm:i32):$imm))
              /*SwitchType*/ 17,  MVT::i64,// ->8284
/*8267*/        OPC_EmitConvertToTarget, 1,
/*8269*/        OPC_EmitConvertToTarget, 1,
/*8271*/        OPC_EmitNodeXForm, 6, 3, // SHL64
/*8274*/        OPC_MorphNodeTo, TARGET_VAL(PPC::RLDICR), 0,
                    1/*#VTs*/, MVT::i64, 3/*#Ops*/, 0, 2, 4, 
                // Src: (shl:i64 G8RC:i64:$in, (imm:i32):$imm) - Complexity = 6
                // Dst: (RLDICR:i64 G8RC:i64:$in, (imm:i32):$imm, (SHL64:i32 (imm:i32):$imm))
              0, // EndSwitchType
/*8285*/    /*Scope*/ 26, /*->8312*/
/*8286*/      OPC_CheckChild1Type, MVT::i32,
/*8288*/      OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->8300
/*8291*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SLW), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (shl:i32 GPRC:i32:$rS, GPRC:i32:$rB) - Complexity = 3
                // Dst: (SLW:i32 GPRC:i32:$rS, GPRC:i32:$rB)
              /*SwitchType*/ 9,  MVT::i64,// ->8311
/*8302*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SLD), 0,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                // Src: (shl:i64 G8RC:i64:$rS, GPRC:i32:$rB) - Complexity = 3
                // Dst: (SLD:i64 G8RC:i64:$rS, GPRC:i32:$rB)
              0, // EndSwitchType
/*8312*/    /*Scope*/ 13, /*->8326*/
/*8313*/      OPC_CheckChild1Type, MVT::v16i8,
/*8315*/      OPC_CheckType, MVT::v16i8,
/*8317*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSLB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (shl:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 3
              // Dst: (VSLB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*8326*/    /*Scope*/ 13, /*->8340*/
/*8327*/      OPC_CheckChild1Type, MVT::v8i16,
/*8329*/      OPC_CheckType, MVT::v8i16,
/*8331*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSLH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (shl:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 3
              // Dst: (VSLH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*8340*/    /*Scope*/ 13, /*->8354*/
/*8341*/      OPC_CheckChild1Type, MVT::v4i32,
/*8343*/      OPC_CheckType, MVT::v4i32,
/*8345*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSLW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (shl:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 3
              // Dst: (VSLW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*8354*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 126,  TARGET_VAL(ISD::SRL),// ->8484
/*8358*/    OPC_RecordChild0, // #0 = $in
/*8359*/    OPC_RecordChild1, // #1 = $imm
/*8360*/    OPC_Scope, 52, /*->8414*/ // 5 children in Scope
/*8362*/      OPC_MoveChild, 1,
/*8364*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*8367*/      OPC_CheckType, MVT::i32,
/*8369*/      OPC_MoveParent,
/*8370*/      OPC_SwitchType /*2 cases */, 21,  MVT::i32,// ->8394
/*8373*/        OPC_EmitConvertToTarget, 1,
/*8375*/        OPC_EmitNodeXForm, 7, 2, // SRL32
/*8378*/        OPC_EmitConvertToTarget, 1,
/*8380*/        OPC_EmitInteger, MVT::i32, 31, 
/*8383*/        OPC_MorphNodeTo, TARGET_VAL(PPC::RLWINM), 0,
                    1/*#VTs*/, MVT::i32, 4/*#Ops*/, 0, 3, 4, 5, 
                // Src: (srl:i32 GPRC:i32:$in, (imm:i32):$imm) - Complexity = 6
                // Dst: (RLWINM:i32 GPRC:i32:$in, (SRL32:i32 (imm:i32):$imm), (imm:i32):$imm, 31:i32)
              /*SwitchType*/ 17,  MVT::i64,// ->8413
/*8396*/        OPC_EmitConvertToTarget, 1,
/*8398*/        OPC_EmitNodeXForm, 8, 2, // SRL64
/*8401*/        OPC_EmitConvertToTarget, 1,
/*8403*/        OPC_MorphNodeTo, TARGET_VAL(PPC::RLDICL), 0,
                    1/*#VTs*/, MVT::i64, 3/*#Ops*/, 0, 3, 4, 
                // Src: (srl:i64 G8RC:i64:$in, (imm:i32):$imm) - Complexity = 6
                // Dst: (RLDICL:i64 G8RC:i64:$in, (SRL64:i32 (imm:i32):$imm), (imm:i32):$imm)
              0, // EndSwitchType
/*8414*/    /*Scope*/ 26, /*->8441*/
/*8415*/      OPC_CheckChild1Type, MVT::i32,
/*8417*/      OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->8429
/*8420*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SRW), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
                // Src: (srl:i32 GPRC:i32:$rS, GPRC:i32:$rB) - Complexity = 3
                // Dst: (SRW:i32 GPRC:i32:$rS, GPRC:i32:$rB)
              /*SwitchType*/ 9,  MVT::i64,// ->8440
/*8431*/        OPC_MorphNodeTo, TARGET_VAL(PPC::SRD), 0,
                    1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
                // Src: (srl:i64 G8RC:i64:$rS, GPRC:i32:$rB) - Complexity = 3
                // Dst: (SRD:i64 G8RC:i64:$rS, GPRC:i32:$rB)
              0, // EndSwitchType
/*8441*/    /*Scope*/ 13, /*->8455*/
/*8442*/      OPC_CheckChild1Type, MVT::v16i8,
/*8444*/      OPC_CheckType, MVT::v16i8,
/*8446*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (srl:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB) - Complexity = 3
              // Dst: (VSRB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*8455*/    /*Scope*/ 13, /*->8469*/
/*8456*/      OPC_CheckChild1Type, MVT::v8i16,
/*8458*/      OPC_CheckType, MVT::v8i16,
/*8460*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (srl:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB) - Complexity = 3
              // Dst: (VSRH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*8469*/    /*Scope*/ 13, /*->8483*/
/*8470*/      OPC_CheckChild1Type, MVT::v4i32,
/*8472*/      OPC_CheckType, MVT::v4i32,
/*8474*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSRW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (srl:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB) - Complexity = 3
              // Dst: (VSRW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*8483*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 92,  TARGET_VAL(ISD::ROTL),// ->8579
/*8487*/    OPC_RecordChild0, // #0 = $in
/*8488*/    OPC_RecordChild1, // #1 = $imm
/*8489*/    OPC_Scope, 48, /*->8539*/ // 2 children in Scope
/*8491*/      OPC_MoveChild, 1,
/*8493*/      OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*8496*/      OPC_CheckType, MVT::i32,
/*8498*/      OPC_MoveParent,
/*8499*/      OPC_SwitchType /*2 cases */, 19,  MVT::i32,// ->8521
/*8502*/        OPC_EmitConvertToTarget, 1,
/*8504*/        OPC_EmitInteger, MVT::i32, 0, 
/*8507*/        OPC_EmitInteger, MVT::i32, 31, 
/*8510*/        OPC_MorphNodeTo, TARGET_VAL(PPC::RLWINM), 0,
                    1/*#VTs*/, MVT::i32, 4/*#Ops*/, 0, 2, 3, 4, 
                // Src: (rotl:i32 GPRC:i32:$in, (imm:i32):$imm) - Complexity = 6
                // Dst: (RLWINM:i32 GPRC:i32:$in, (imm:i32):$imm, 0:i32, 31:i32)
              /*SwitchType*/ 15,  MVT::i64,// ->8538
/*8523*/        OPC_EmitConvertToTarget, 1,
/*8525*/        OPC_EmitInteger, MVT::i32, 0, 
/*8528*/        OPC_MorphNodeTo, TARGET_VAL(PPC::RLDICL), 0,
                    1/*#VTs*/, MVT::i64, 3/*#Ops*/, 0, 2, 3, 
                // Src: (rotl:i64 G8RC:i64:$in, (imm:i32):$imm) - Complexity = 6
                // Dst: (RLDICL:i64 G8RC:i64:$in, (imm:i32):$imm, 0:i32)
              0, // EndSwitchType
/*8539*/    /*Scope*/ 38, /*->8578*/
/*8540*/      OPC_CheckChild1Type, MVT::i32,
/*8542*/      OPC_SwitchType /*2 cases */, 17,  MVT::i32,// ->8562
/*8545*/        OPC_EmitInteger, MVT::i32, 0, 
/*8548*/        OPC_EmitInteger, MVT::i32, 31, 
/*8551*/        OPC_MorphNodeTo, TARGET_VAL(PPC::RLWNM), 0,
                    1/*#VTs*/, MVT::i32, 4/*#Ops*/, 0, 1, 2, 3, 
                // Src: (rotl:i32 GPRC:i32:$in, GPRC:i32:$sh) - Complexity = 3
                // Dst: (RLWNM:i32 GPRC:i32:$in, GPRC:i32:$sh, 0:i32, 31:i32)
              /*SwitchType*/ 13,  MVT::i64,// ->8577
/*8564*/        OPC_EmitInteger, MVT::i32, 0, 
/*8567*/        OPC_MorphNodeTo, TARGET_VAL(PPC::RLDCL), 0,
                    1/*#VTs*/, MVT::i64, 3/*#Ops*/, 0, 1, 2, 
                // Src: (rotl:i64 G8RC:i64:$in, GPRC:i32:$sh) - Complexity = 3
                // Dst: (RLDCL:i64 G8RC:i64:$in, GPRC:i32:$sh, 0:i32)
              0, // EndSwitchType
/*8578*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 53,  TARGET_VAL(PPCISD::TOC_ENTRY),// ->8635
/*8582*/    OPC_RecordChild0, // #0 = $disp
/*8583*/    OPC_MoveChild, 0,
/*8585*/    OPC_SwitchOpcode /*3 cases */, 13,  TARGET_VAL(ISD::TargetGlobalAddress),// ->8602
/*8589*/      OPC_MoveParent,
/*8590*/      OPC_RecordChild1, // #1 = $reg
/*8591*/      OPC_CheckType, MVT::i64,
/*8593*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LDtoc), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (PPCtoc_entry:i64 (tglobaladdr:i64):$disp, G8RC:i64:$reg) - Complexity = 6
              // Dst: (LDtoc:i64 (tglobaladdr:i64):$disp, G8RC:i64:$reg)
            /*SwitchOpcode*/ 13,  TARGET_VAL(ISD::TargetJumpTable),// ->8618
/*8605*/      OPC_MoveParent,
/*8606*/      OPC_RecordChild1, // #1 = $reg
/*8607*/      OPC_CheckType, MVT::i64,
/*8609*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LDtocJTI), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (PPCtoc_entry:i64 (tjumptable:i64):$disp, G8RC:i64:$reg) - Complexity = 6
              // Dst: (LDtocJTI:i64 (tjumptable:i64):$disp, G8RC:i64:$reg)
            /*SwitchOpcode*/ 13,  TARGET_VAL(ISD::TargetConstantPool),// ->8634
/*8621*/      OPC_MoveParent,
/*8622*/      OPC_RecordChild1, // #1 = $reg
/*8623*/      OPC_CheckType, MVT::i64,
/*8625*/      OPC_MorphNodeTo, TARGET_VAL(PPC::LDtocCPT), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (PPCtoc_entry:i64 (tconstpool:i64):$disp, G8RC:i64:$reg) - Complexity = 6
              // Dst: (LDtocCPT:i64 (tconstpool:i64):$disp, G8RC:i64:$reg)
            0, // EndSwitchOpcode
          /*SwitchOpcode*/ 97,  TARGET_VAL(ISD::Constant),// ->8735
/*8638*/    OPC_RecordNode,   // #0 = $imm
/*8639*/    OPC_SwitchType /*2 cases */, 59,  MVT::i32,// ->8701
/*8642*/      OPC_Scope, 12, /*->8656*/ // 3 children in Scope
/*8644*/        OPC_CheckPredicate, 0, // Predicate_immSExt16
/*8646*/        OPC_EmitConvertToTarget, 0,
/*8648*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 1, 
                // Src: (imm:i32)<<P:Predicate_immSExt16>>:$imm - Complexity = 4
                // Dst: (LI:i32 (imm:i32):$imm)
/*8656*/      /*Scope*/ 15, /*->8672*/
/*8657*/        OPC_CheckPredicate, 1, // Predicate_imm16ShiftedSExt
/*8659*/        OPC_EmitConvertToTarget, 0,
/*8661*/        OPC_EmitNodeXForm, 0, 1, // HI16
/*8664*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 2, 
                // Src: (imm:i32)<<P:Predicate_imm16ShiftedSExt>><<X:HI16>>:$imm - Complexity = 4
                // Dst: (LIS:i32 (HI16:i32 (imm:i32):$imm))
/*8672*/      /*Scope*/ 27, /*->8700*/
/*8673*/        OPC_EmitConvertToTarget, 0,
/*8675*/        OPC_EmitNodeXForm, 0, 1, // HI16
/*8678*/        OPC_EmitNode, TARGET_VAL(PPC::LIS), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 2,  // Results = #3
/*8686*/        OPC_EmitConvertToTarget, 0,
/*8688*/        OPC_EmitNodeXForm, 1, 4, // LO16
/*8691*/        OPC_MorphNodeTo, TARGET_VAL(PPC::ORI), 0,
                    1/*#VTs*/, MVT::i32, 2/*#Ops*/, 3, 5, 
                // Src: (imm:i32):$imm - Complexity = 3
                // Dst: (ORI:i32 (LIS:i32 (HI16:i32 (imm:i32):$imm)), (LO16:i32 (imm:i32):$imm))
/*8700*/      0, /*End of Scope*/
            /*SwitchType*/ 31,  MVT::i64,// ->8734
/*8703*/      OPC_Scope, 12, /*->8717*/ // 2 children in Scope
/*8705*/        OPC_CheckPredicate, 0, // Predicate_immSExt16
/*8707*/        OPC_EmitConvertToTarget, 0,
/*8709*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LI8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 1, 
                // Src: (imm:i64)<<P:Predicate_immSExt16>>:$imm - Complexity = 4
                // Dst: (LI8:i64 (imm:i64):$imm)
/*8717*/      /*Scope*/ 15, /*->8733*/
/*8718*/        OPC_CheckPredicate, 1, // Predicate_imm16ShiftedSExt
/*8720*/        OPC_EmitConvertToTarget, 0,
/*8722*/        OPC_EmitNodeXForm, 0, 1, // HI16
/*8725*/        OPC_MorphNodeTo, TARGET_VAL(PPC::LIS8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 2, 
                // Src: (imm:i64)<<P:Predicate_imm16ShiftedSExt>><<X:HI16>>:$imm - Complexity = 4
                // Dst: (LIS8:i64 (HI16:i64 (imm:i64):$imm))
/*8733*/      0, /*End of Scope*/
            0, // EndSwitchType
          /*SwitchOpcode*/ 28,  TARGET_VAL(PPCISD::SHL),// ->8766
/*8738*/    OPC_RecordChild0, // #0 = $rS
/*8739*/    OPC_RecordChild1, // #1 = $rB
/*8740*/    OPC_CheckChild1Type, MVT::i32,
/*8742*/    OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->8754
/*8745*/      OPC_MorphNodeTo, TARGET_VAL(PPC::SLW), 0,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCshl:i32 GPRC:i32:$rS, GPRC:i32:$rB) - Complexity = 3
              // Dst: (SLW:i32 GPRC:i32:$rS, GPRC:i32:$rB)
            /*SwitchType*/ 9,  MVT::i64,// ->8765
/*8756*/      OPC_MorphNodeTo, TARGET_VAL(PPC::SLD), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (PPCshl:i64 G8RC:i64:$rS, GPRC:i32:$rB) - Complexity = 3
              // Dst: (SLD:i64 G8RC:i64:$rS, GPRC:i32:$rB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 28,  TARGET_VAL(PPCISD::SRL),// ->8797
/*8769*/    OPC_RecordChild0, // #0 = $rS
/*8770*/    OPC_RecordChild1, // #1 = $rB
/*8771*/    OPC_CheckChild1Type, MVT::i32,
/*8773*/    OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->8785
/*8776*/      OPC_MorphNodeTo, TARGET_VAL(PPC::SRW), 0,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCsrl:i32 GPRC:i32:$rS, GPRC:i32:$rB) - Complexity = 3
              // Dst: (SRW:i32 GPRC:i32:$rS, GPRC:i32:$rB)
            /*SwitchType*/ 9,  MVT::i64,// ->8796
/*8787*/      OPC_MorphNodeTo, TARGET_VAL(PPC::SRD), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (PPCsrl:i64 G8RC:i64:$rS, GPRC:i32:$rB) - Complexity = 3
              // Dst: (SRD:i64 G8RC:i64:$rS, GPRC:i32:$rB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 30,  TARGET_VAL(PPCISD::SRA),// ->8830
/*8800*/    OPC_RecordChild0, // #0 = $rS
/*8801*/    OPC_RecordChild1, // #1 = $rB
/*8802*/    OPC_CheckChild1Type, MVT::i32,
/*8804*/    OPC_SwitchType /*2 cases */, 10,  MVT::i32,// ->8817
/*8807*/      OPC_MorphNodeTo, TARGET_VAL(PPC::SRAW), 0,
                  2/*#VTs*/, MVT::i32, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCsra:i32 GPRC:i32:$rS, GPRC:i32:$rB) - Complexity = 3
              // Dst: (SRAW:i32:i32 GPRC:i32:$rS, GPRC:i32:$rB)
            /*SwitchType*/ 10,  MVT::i64,// ->8829
/*8819*/      OPC_MorphNodeTo, TARGET_VAL(PPC::SRAD), 0,
                  2/*#VTs*/, MVT::i64, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCsra:i64 G8RC:i64:$rS, GPRC:i32:$rB) - Complexity = 3
              // Dst: (SRAD:i64:i32 G8RC:i64:$rS, GPRC:i32:$rB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 23,  TARGET_VAL(ISD::CTLZ),// ->8856
/*8833*/    OPC_RecordChild0, // #0 = $rS
/*8834*/    OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->8845
/*8837*/      OPC_MorphNodeTo, TARGET_VAL(PPC::CNTLZW), 0,
                  1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
              // Src: (ctlz:i32 GPRC:i32:$rS) - Complexity = 3
              // Dst: (CNTLZW:i32 GPRC:i32:$rS)
            /*SwitchType*/ 8,  MVT::i64,// ->8855
/*8847*/      OPC_MorphNodeTo, TARGET_VAL(PPC::CNTLZD), 0,
                  1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
              // Src: (ctlz:i64 G8RC:i64:$rS) - Complexity = 3
              // Dst: (CNTLZD:i64 G8RC:i64:$rS)
            0, // EndSwitchType
          /*SwitchOpcode*/ 69,  TARGET_VAL(ISD::SIGN_EXTEND_INREG),// ->8928
/*8859*/    OPC_RecordChild0, // #0 = $rS
/*8860*/    OPC_MoveChild, 1,
/*8862*/    OPC_Scope, 25, /*->8889*/ // 3 children in Scope
/*8864*/      OPC_CheckValueType, MVT::i8,
/*8866*/      OPC_MoveParent,
/*8867*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->8878
/*8870*/        OPC_MorphNodeTo, TARGET_VAL(PPC::EXTSB), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (sext_inreg:i32 GPRC:i32:$rS, i8:Other) - Complexity = 3
                // Dst: (EXTSB:i32 GPRC:i32:$rS)
              /*SwitchType*/ 8,  MVT::i64,// ->8888
/*8880*/        OPC_MorphNodeTo, TARGET_VAL(PPC::EXTSB8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (sext_inreg:i64 G8RC:i64:$rS, i8:Other) - Complexity = 3
                // Dst: (EXTSB8:i64 G8RC:i64:$rS)
              0, // EndSwitchType
/*8889*/    /*Scope*/ 25, /*->8915*/
/*8890*/      OPC_CheckValueType, MVT::i16,
/*8892*/      OPC_MoveParent,
/*8893*/      OPC_SwitchType /*2 cases */, 8,  MVT::i32,// ->8904
/*8896*/        OPC_MorphNodeTo, TARGET_VAL(PPC::EXTSH), 0,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
                // Src: (sext_inreg:i32 GPRC:i32:$rS, i16:Other) - Complexity = 3
                // Dst: (EXTSH:i32 GPRC:i32:$rS)
              /*SwitchType*/ 8,  MVT::i64,// ->8914
/*8906*/        OPC_MorphNodeTo, TARGET_VAL(PPC::EXTSH8), 0,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
                // Src: (sext_inreg:i64 G8RC:i64:$rS, i16:Other) - Complexity = 3
                // Dst: (EXTSH8:i64 G8RC:i64:$rS)
              0, // EndSwitchType
/*8915*/    /*Scope*/ 11, /*->8927*/
/*8916*/      OPC_CheckValueType, MVT::i32,
/*8918*/      OPC_MoveParent,
/*8919*/      OPC_MorphNodeTo, TARGET_VAL(PPC::EXTSW), 0,
                  1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
              // Src: (sext_inreg:i64 G8RC:i64:$rS, i32:Other) - Complexity = 3
              // Dst: (EXTSW:i64 G8RC:i64:$rS)
/*8927*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::SDIV),// ->8957
/*8931*/    OPC_RecordChild0, // #0 = $rA
/*8932*/    OPC_RecordChild1, // #1 = $rB
/*8933*/    OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->8945
/*8936*/      OPC_MorphNodeTo, TARGET_VAL(PPC::DIVW), 0,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (sdiv:i32 GPRC:i32:$rA, GPRC:i32:$rB) - Complexity = 3
              // Dst: (DIVW:i32 GPRC:i32:$rA, GPRC:i32:$rB)
            /*SwitchType*/ 9,  MVT::i64,// ->8956
/*8947*/      OPC_MorphNodeTo, TARGET_VAL(PPC::DIVD), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (sdiv:i64 G8RC:i64:$rA, G8RC:i64:$rB) - Complexity = 3
              // Dst: (DIVD:i64 G8RC:i64:$rA, G8RC:i64:$rB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::UDIV),// ->8986
/*8960*/    OPC_RecordChild0, // #0 = $rA
/*8961*/    OPC_RecordChild1, // #1 = $rB
/*8962*/    OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->8974
/*8965*/      OPC_MorphNodeTo, TARGET_VAL(PPC::DIVWU), 0,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (udiv:i32 GPRC:i32:$rA, GPRC:i32:$rB) - Complexity = 3
              // Dst: (DIVWU:i32 GPRC:i32:$rA, GPRC:i32:$rB)
            /*SwitchType*/ 9,  MVT::i64,// ->8985
/*8976*/      OPC_MorphNodeTo, TARGET_VAL(PPC::DIVDU), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (udiv:i64 G8RC:i64:$rA, G8RC:i64:$rB) - Complexity = 3
              // Dst: (DIVDU:i64 G8RC:i64:$rA, G8RC:i64:$rB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::MULHS),// ->9015
/*8989*/    OPC_RecordChild0, // #0 = $rA
/*8990*/    OPC_RecordChild1, // #1 = $rB
/*8991*/    OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->9003
/*8994*/      OPC_MorphNodeTo, TARGET_VAL(PPC::MULHW), 0,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (mulhs:i32 GPRC:i32:$rA, GPRC:i32:$rB) - Complexity = 3
              // Dst: (MULHW:i32 GPRC:i32:$rA, GPRC:i32:$rB)
            /*SwitchType*/ 9,  MVT::i64,// ->9014
/*9005*/      OPC_MorphNodeTo, TARGET_VAL(PPC::MULHD), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (mulhs:i64 G8RC:i64:$rA, G8RC:i64:$rB) - Complexity = 3
              // Dst: (MULHD:i64 G8RC:i64:$rA, G8RC:i64:$rB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::MULHU),// ->9044
/*9018*/    OPC_RecordChild0, // #0 = $rA
/*9019*/    OPC_RecordChild1, // #1 = $rB
/*9020*/    OPC_SwitchType /*2 cases */, 9,  MVT::i32,// ->9032
/*9023*/      OPC_MorphNodeTo, TARGET_VAL(PPC::MULHWU), 0,
                  1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (mulhu:i32 GPRC:i32:$rA, GPRC:i32:$rB) - Complexity = 3
              // Dst: (MULHWU:i32 GPRC:i32:$rA, GPRC:i32:$rB)
            /*SwitchType*/ 9,  MVT::i64,// ->9043
/*9034*/      OPC_MorphNodeTo, TARGET_VAL(PPC::MULHDU), 0,
                  1/*#VTs*/, MVT::i64, 2/*#Ops*/, 0, 1, 
              // Src: (mulhu:i64 G8RC:i64:$rA, G8RC:i64:$rB) - Complexity = 3
              // Dst: (MULHDU:i64 G8RC:i64:$rA, G8RC:i64:$rB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 11,  TARGET_VAL(ISD::READCYCLECOUNTER),// ->9058
/*9047*/    OPC_RecordNode,   // #0 = 'readcyclecounter' chained node
/*9048*/    OPC_CheckType, MVT::i64,
/*9050*/    OPC_EmitMergeInputChains1_0,
/*9051*/    OPC_MorphNodeTo, TARGET_VAL(PPC::MFTB8), 0|OPFL_Chain,
                1/*#VTs*/, MVT::i64, 0/*#Ops*/, 
            // Src: (readcyclecounter:i64) - Complexity = 3
            // Dst: (MFTB8:i64)
          /*SwitchOpcode*/ 11,  TARGET_VAL(PPCISD::EXTSW_32),// ->9072
/*9061*/    OPC_RecordChild0, // #0 = $rS
/*9062*/    OPC_CheckType, MVT::i32,
/*9064*/    OPC_MorphNodeTo, TARGET_VAL(PPC::EXTSW_32), 0,
                1/*#VTs*/, MVT::i32, 1/*#Ops*/, 0, 
            // Src: (PPCextsw_32:i32 GPRC:i32:$rS) - Complexity = 3
            // Dst: (EXTSW_32:i32 GPRC:i32:$rS)
          /*SwitchOpcode*/ 13,  TARGET_VAL(ISD::SIGN_EXTEND),// ->9088
/*9075*/    OPC_RecordChild0, // #0 = $rS
/*9076*/    OPC_CheckChild0Type, MVT::i32,
/*9078*/    OPC_CheckType, MVT::i64,
/*9080*/    OPC_MorphNodeTo, TARGET_VAL(PPC::EXTSW_32_64), 0,
                1/*#VTs*/, MVT::i64, 1/*#Ops*/, 0, 
            // Src: (sext:i64 GPRC:i32:$rS) - Complexity = 3
            // Dst: (EXTSW_32_64:i64 GPRC:i32:$rS)
          /*SwitchOpcode*/ 15,  TARGET_VAL(ISD::TRUNCATE),// ->9106
/*9091*/    OPC_RecordChild0, // #0 = $in
/*9092*/    OPC_CheckType, MVT::i32,
/*9094*/    OPC_EmitInteger, MVT::i32, PPC::sub_32,
/*9097*/    OPC_MorphNodeTo, TARGET_VAL(TargetOpcode::EXTRACT_SUBREG), 0,
                1/*#VTs*/, MVT::i32, 2/*#Ops*/, 0, 1, 
            // Src: (trunc:i32 G8RC:i64:$in) - Complexity = 3
            // Dst: (EXTRACT_SUBREG:i32 G8RC:i64:$in, sub_32:i32)
          /*SwitchOpcode*/ 25,  TARGET_VAL(ISD::ANY_EXTEND),// ->9134
/*9109*/    OPC_RecordChild0, // #0 = $in
/*9110*/    OPC_CheckChild0Type, MVT::i32,
/*9112*/    OPC_CheckType, MVT::i64,
/*9114*/    OPC_EmitNode, TARGET_VAL(TargetOpcode::IMPLICIT_DEF), 0,
                1/*#VTs*/, MVT::i64, 0/*#Ops*/,  // Results = #1
/*9121*/    OPC_EmitInteger, MVT::i32, PPC::sub_32,
/*9124*/    OPC_MorphNodeTo, TARGET_VAL(TargetOpcode::INSERT_SUBREG), 0,
                1/*#VTs*/, MVT::i64, 3/*#Ops*/, 1, 0, 2, 
            // Src: (anyext:i64 GPRC:i32:$in) - Complexity = 3
            // Dst: (INSERT_SUBREG:i64 (IMPLICIT_DEF:i64), GPRC:i32:$in, sub_32:i32)
          /*SwitchOpcode*/ 41,  TARGET_VAL(ISD::ZERO_EXTEND),// ->9178
/*9137*/    OPC_RecordChild0, // #0 = $in
/*9138*/    OPC_CheckChild0Type, MVT::i32,
/*9140*/    OPC_CheckType, MVT::i64,
/*9142*/    OPC_EmitNode, TARGET_VAL(TargetOpcode::IMPLICIT_DEF), 0,
                1/*#VTs*/, MVT::i64, 0/*#Ops*/,  // Results = #1
/*9149*/    OPC_EmitInteger, MVT::i32, PPC::sub_32,
/*9152*/    OPC_EmitNode, TARGET_VAL(TargetOpcode::INSERT_SUBREG), 0,
                1/*#VTs*/, MVT::i64, 3/*#Ops*/, 1, 0, 2,  // Results = #3
/*9162*/    OPC_EmitInteger, MVT::i32, 0, 
/*9165*/    OPC_EmitInteger, MVT::i32, 32, 
/*9168*/    OPC_MorphNodeTo, TARGET_VAL(PPC::RLDICL), 0,
                1/*#VTs*/, MVT::i64, 3/*#Ops*/, 3, 4, 5, 
            // Src: (zext:i64 GPRC:i32:$in) - Complexity = 3
            // Dst: (RLDICL:i64 (INSERT_SUBREG:i64 (IMPLICIT_DEF:i64), GPRC:i32:$in, sub_32:i32), 0:i32, 32:i32)
          /*SwitchOpcode*/ 29|128,1/*157*/,  TARGET_VAL(ISD::FNEG),// ->9339
/*9182*/    OPC_Scope, 102, /*->9286*/ // 3 children in Scope
/*9184*/      OPC_MoveChild, 0,
/*9186*/      OPC_SwitchOpcode /*2 cases */, 68,  TARGET_VAL(ISD::FMA),// ->9258
/*9190*/        OPC_RecordChild0, // #0 = $FRA
/*9191*/        OPC_RecordChild1, // #1 = $FRC
/*9192*/        OPC_Scope, 34, /*->9228*/ // 2 children in Scope
/*9194*/          OPC_MoveChild, 2,
/*9196*/          OPC_CheckOpcode, TARGET_VAL(ISD::FNEG),
/*9199*/          OPC_RecordChild0, // #2 = $FRB
/*9200*/          OPC_MoveParent,
/*9201*/          OPC_MoveParent,
/*9202*/          OPC_SwitchType /*2 cases */, 10,  MVT::f64,// ->9215
/*9205*/            OPC_MorphNodeTo, TARGET_VAL(PPC::FNMSUB), 0,
                        1/*#VTs*/, MVT::f64, 3/*#Ops*/, 0, 1, 2, 
                    // Src: (fneg:f64 (fma:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, (fneg:f64 F8RC:f64:$FRB))) - Complexity = 9
                    // Dst: (FNMSUB:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, F8RC:f64:$FRB)
                  /*SwitchType*/ 10,  MVT::f32,// ->9227
/*9217*/            OPC_MorphNodeTo, TARGET_VAL(PPC::FNMSUBS), 0,
                        1/*#VTs*/, MVT::f32, 3/*#Ops*/, 0, 1, 2, 
                    // Src: (fneg:f32 (fma:f32 F4RC:f32:$FRA, F4RC:f32:$FRC, (fneg:f32 F4RC:f32:$FRB))) - Complexity = 9
                    // Dst: (FNMSUBS:f32 F4RC:f32:$FRA, F4RC:f32:$FRC, F4RC:f32:$FRB)
                  0, // EndSwitchType
/*9228*/        /*Scope*/ 28, /*->9257*/
/*9229*/          OPC_RecordChild2, // #2 = $FRB
/*9230*/          OPC_MoveParent,
/*9231*/          OPC_SwitchType /*2 cases */, 10,  MVT::f64,// ->9244
/*9234*/            OPC_MorphNodeTo, TARGET_VAL(PPC::FNMADD), 0,
                        1/*#VTs*/, MVT::f64, 3/*#Ops*/, 0, 1, 2, 
                    // Src: (fneg:f64 (fma:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, F8RC:f64:$FRB)) - Complexity = 6
                    // Dst: (FNMADD:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, F8RC:f64:$FRB)
                  /*SwitchType*/ 10,  MVT::f32,// ->9256
/*9246*/            OPC_MorphNodeTo, TARGET_VAL(PPC::FNMADDS), 0,
                        1/*#VTs*/, MVT::f32, 3/*#Ops*/, 0, 1, 2, 
                    // Src: (fneg:f32 (fma:f32 F4RC:f32:$FRA, F4RC:f32:$FRC, F4RC:f32:$FRB)) - Complexity = 6
                    // Dst: (FNMADDS:f32 F4RC:f32:$FRA, F4RC:f32:$FRC, F4RC:f32:$FRB)
                  0, // EndSwitchType
/*9257*/        0, /*End of Scope*/
              /*SwitchOpcode*/ 24,  TARGET_VAL(ISD::FABS),// ->9285
/*9261*/        OPC_RecordChild0, // #0 = $frB
/*9262*/        OPC_MoveParent,
/*9263*/        OPC_SwitchType /*2 cases */, 8,  MVT::f32,// ->9274
/*9266*/          OPC_MorphNodeTo, TARGET_VAL(PPC::FNABSS), 0,
                      1/*#VTs*/, MVT::f32, 1/*#Ops*/, 0, 
                  // Src: (fneg:f32 (fabs:f32 F4RC:f32:$frB)) - Complexity = 6
                  // Dst: (FNABSS:f32 F4RC:f32:$frB)
                /*SwitchType*/ 8,  MVT::f64,// ->9284
/*9276*/          OPC_MorphNodeTo, TARGET_VAL(PPC::FNABSD), 0,
                      1/*#VTs*/, MVT::f64, 1/*#Ops*/, 0, 
                  // Src: (fneg:f64 (fabs:f64 F8RC:f64:$frB)) - Complexity = 6
                  // Dst: (FNABSD:f64 F8RC:f64:$frB)
                0, // EndSwitchType
              0, // EndSwitchOpcode
/*9286*/    /*Scope*/ 23, /*->9310*/
/*9287*/      OPC_RecordChild0, // #0 = $frB
/*9288*/      OPC_SwitchType /*2 cases */, 8,  MVT::f32,// ->9299
/*9291*/        OPC_MorphNodeTo, TARGET_VAL(PPC::FNEGS), 0,
                    1/*#VTs*/, MVT::f32, 1/*#Ops*/, 0, 
                // Src: (fneg:f32 F4RC:f32:$frB) - Complexity = 3
                // Dst: (FNEGS:f32 F4RC:f32:$frB)
              /*SwitchType*/ 8,  MVT::f64,// ->9309
/*9301*/        OPC_MorphNodeTo, TARGET_VAL(PPC::FNEGD), 0,
                    1/*#VTs*/, MVT::f64, 1/*#Ops*/, 0, 
                // Src: (fneg:f64 F8RC:f64:$frB) - Complexity = 3
                // Dst: (FNEGD:f64 F8RC:f64:$frB)
              0, // EndSwitchType
/*9310*/    /*Scope*/ 27, /*->9338*/
/*9311*/      OPC_MoveChild, 0,
/*9313*/      OPC_CheckOpcode, TARGET_VAL(ISD::FMA),
/*9316*/      OPC_RecordChild0, // #0 = $vA
/*9317*/      OPC_RecordChild1, // #1 = $vC
/*9318*/      OPC_MoveChild, 2,
/*9320*/      OPC_CheckOpcode, TARGET_VAL(ISD::FNEG),
/*9323*/      OPC_RecordChild0, // #2 = $vB
/*9324*/      OPC_MoveParent,
/*9325*/      OPC_MoveParent,
/*9326*/      OPC_CheckType, MVT::v4f32,
/*9328*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VNMSUBFP), 0,
                  1/*#VTs*/, MVT::v4f32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (fneg:v4f32 (fma:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vC, (fneg:v4f32 VRRC:v4f32:$vB))) - Complexity = 9
              // Dst: (VNMSUBFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vC, VRRC:v4f32:$vB)
/*9338*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 24,  TARGET_VAL(PPCISD::MTFSF),// ->9366
/*9342*/    OPC_CaptureGlueInput,
/*9343*/    OPC_RecordChild0, // #0 = $FM
/*9344*/    OPC_MoveChild, 0,
/*9346*/    OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*9349*/    OPC_CheckType, MVT::i32,
/*9351*/    OPC_MoveParent,
/*9352*/    OPC_RecordChild1, // #1 = $rT
/*9353*/    OPC_RecordChild2, // #2 = $FRB
/*9354*/    OPC_EmitConvertToTarget, 0,
/*9356*/    OPC_MorphNodeTo, TARGET_VAL(PPC::MTFSF), 0|OPFL_GlueInput,
                1/*#VTs*/, MVT::f64, 3/*#Ops*/, 3, 1, 2, 
            // Src: (PPCmtfsf:f64 (imm:i32):$FM, F8RC:f64:$rT, F8RC:f64:$FRB) - Complexity = 6
            // Dst: (MTFSF:f64 (imm:i32):$FM, F8RC:f64:$rT, F8RC:f64:$FRB)
          /*SwitchOpcode*/ 78,  TARGET_VAL(ISD::FMA),// ->9447
/*9369*/    OPC_RecordChild0, // #0 = $FRA
/*9370*/    OPC_RecordChild1, // #1 = $FRC
/*9371*/    OPC_Scope, 33, /*->9406*/ // 2 children in Scope
/*9373*/      OPC_MoveChild, 2,
/*9375*/      OPC_CheckOpcode, TARGET_VAL(ISD::FNEG),
/*9378*/      OPC_RecordChild0, // #2 = $FRB
/*9379*/      OPC_MoveParent,
/*9380*/      OPC_SwitchType /*2 cases */, 10,  MVT::f64,// ->9393
/*9383*/        OPC_MorphNodeTo, TARGET_VAL(PPC::FMSUB), 0,
                    1/*#VTs*/, MVT::f64, 3/*#Ops*/, 0, 1, 2, 
                // Src: (fma:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, (fneg:f64 F8RC:f64:$FRB)) - Complexity = 6
                // Dst: (FMSUB:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, F8RC:f64:$FRB)
              /*SwitchType*/ 10,  MVT::f32,// ->9405
/*9395*/        OPC_MorphNodeTo, TARGET_VAL(PPC::FMSUBS), 0,
                    1/*#VTs*/, MVT::f32, 3/*#Ops*/, 0, 1, 2, 
                // Src: (fma:f32 F4RC:f32:$FRA, F4RC:f32:$FRC, (fneg:f32 F4RC:f32:$FRB)) - Complexity = 6
                // Dst: (FMSUBS:f32 F4RC:f32:$FRA, F4RC:f32:$FRC, F4RC:f32:$FRB)
              0, // EndSwitchType
/*9406*/    /*Scope*/ 39, /*->9446*/
/*9407*/      OPC_RecordChild2, // #2 = $FRB
/*9408*/      OPC_SwitchType /*3 cases */, 10,  MVT::f64,// ->9421
/*9411*/        OPC_MorphNodeTo, TARGET_VAL(PPC::FMADD), 0,
                    1/*#VTs*/, MVT::f64, 3/*#Ops*/, 0, 1, 2, 
                // Src: (fma:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, F8RC:f64:$FRB) - Complexity = 3
                // Dst: (FMADD:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, F8RC:f64:$FRB)
              /*SwitchType*/ 10,  MVT::f32,// ->9433
/*9423*/        OPC_MorphNodeTo, TARGET_VAL(PPC::FMADDS), 0,
                    1/*#VTs*/, MVT::f32, 3/*#Ops*/, 0, 1, 2, 
                // Src: (fma:f32 F4RC:f32:$FRA, F4RC:f32:$FRC, F4RC:f32:$FRB) - Complexity = 3
                // Dst: (FMADDS:f32 F4RC:f32:$FRA, F4RC:f32:$FRC, F4RC:f32:$FRB)
              /*SwitchType*/ 10,  MVT::v4f32,// ->9445
/*9435*/        OPC_MorphNodeTo, TARGET_VAL(PPC::VMADDFP), 0,
                    1/*#VTs*/, MVT::v4f32, 3/*#Ops*/, 0, 1, 2, 
                // Src: (fma:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vC, VRRC:v4f32:$vB) - Complexity = 3
                // Dst: (VMADDFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vC, VRRC:v4f32:$vB)
              0, // EndSwitchType
/*9446*/    0, /*End of Scope*/
          /*SwitchOpcode*/ 11,  TARGET_VAL(PPCISD::FCTIWZ),// ->9461
/*9450*/    OPC_RecordChild0, // #0 = $frB
/*9451*/    OPC_CheckType, MVT::f64,
/*9453*/    OPC_MorphNodeTo, TARGET_VAL(PPC::FCTIWZ), 0,
                1/*#VTs*/, MVT::f64, 1/*#Ops*/, 0, 
            // Src: (PPCfctiwz:f64 F8RC:f64:$frB) - Complexity = 3
            // Dst: (FCTIWZ:f64 F8RC:f64:$frB)
          /*SwitchOpcode*/ 9,  TARGET_VAL(ISD::FP_ROUND),// ->9473
/*9464*/    OPC_RecordChild0, // #0 = $frB
/*9465*/    OPC_MorphNodeTo, TARGET_VAL(PPC::FRSP), 0,
                1/*#VTs*/, MVT::f32, 1/*#Ops*/, 0, 
            // Src: (fround:f32 F8RC:f64:$frB) - Complexity = 3
            // Dst: (FRSP:f32 F8RC:f64:$frB)
          /*SwitchOpcode*/ 23,  TARGET_VAL(ISD::FSQRT),// ->9499
/*9476*/    OPC_RecordChild0, // #0 = $frB
/*9477*/    OPC_SwitchType /*2 cases */, 8,  MVT::f64,// ->9488
/*9480*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FSQRT), 0,
                  1/*#VTs*/, MVT::f64, 1/*#Ops*/, 0, 
              // Src: (fsqrt:f64 F8RC:f64:$frB) - Complexity = 3
              // Dst: (FSQRT:f64 F8RC:f64:$frB)
            /*SwitchType*/ 8,  MVT::f32,// ->9498
/*9490*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FSQRTS), 0,
                  1/*#VTs*/, MVT::f32, 1/*#Ops*/, 0, 
              // Src: (fsqrt:f32 F4RC:f32:$frB) - Complexity = 3
              // Dst: (FSQRTS:f32 F4RC:f32:$frB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 23,  TARGET_VAL(ISD::FABS),// ->9525
/*9502*/    OPC_RecordChild0, // #0 = $frB
/*9503*/    OPC_SwitchType /*2 cases */, 8,  MVT::f32,// ->9514
/*9506*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FABSS), 0,
                  1/*#VTs*/, MVT::f32, 1/*#Ops*/, 0, 
              // Src: (fabs:f32 F4RC:f32:$frB) - Complexity = 3
              // Dst: (FABSS:f32 F4RC:f32:$frB)
            /*SwitchType*/ 8,  MVT::f64,// ->9524
/*9516*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FABSD), 0,
                  1/*#VTs*/, MVT::f64, 1/*#Ops*/, 0, 
              // Src: (fabs:f64 F8RC:f64:$frB) - Complexity = 3
              // Dst: (FABSD:f64 F8RC:f64:$frB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 7,  TARGET_VAL(PPCISD::MFFS),// ->9535
/*9528*/    OPC_MorphNodeTo, TARGET_VAL(PPC::MFFS), 0|OPFL_GlueOutput,
                1/*#VTs*/, MVT::f64, 0/*#Ops*/, 
            // Src: (PPCmffs:f64) - Complexity = 3
            // Dst: (MFFS:f64)
          /*SwitchOpcode*/ 14,  TARGET_VAL(PPCISD::FADDRTZ),// ->9552
/*9538*/    OPC_CaptureGlueInput,
/*9539*/    OPC_RecordChild0, // #0 = $FRA
/*9540*/    OPC_RecordChild1, // #1 = $FRB
/*9541*/    OPC_CheckType, MVT::f64,
/*9543*/    OPC_MorphNodeTo, TARGET_VAL(PPC::FADDrtz), 0|OPFL_GlueInput|OPFL_GlueOutput,
                1/*#VTs*/, MVT::f64, 2/*#Ops*/, 0, 1, 
            // Src: (PPCfaddrtz:f64 F8RC:f64:$FRA, F8RC:f64:$FRB) - Complexity = 3
            // Dst: (FADDrtz:f64 F8RC:f64:$FRA, F8RC:f64:$FRB)
          /*SwitchOpcode*/ 29,  TARGET_VAL(PPCISD::FSEL),// ->9584
/*9555*/    OPC_RecordChild0, // #0 = $FRA
/*9556*/    OPC_RecordChild1, // #1 = $FRC
/*9557*/    OPC_RecordChild2, // #2 = $FRB
/*9558*/    OPC_SwitchType /*2 cases */, 10,  MVT::f64,// ->9571
/*9561*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FSELD), 0,
                  1/*#VTs*/, MVT::f64, 3/*#Ops*/, 0, 1, 2, 
              // Src: (PPCfsel:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, F8RC:f64:$FRB) - Complexity = 3
              // Dst: (FSELD:f64 F8RC:f64:$FRA, F8RC:f64:$FRC, F8RC:f64:$FRB)
            /*SwitchType*/ 10,  MVT::f32,// ->9583
/*9573*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FSELS), 0,
                  1/*#VTs*/, MVT::f32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (PPCfsel:f32 F8RC:f64:$FRA, F4RC:f32:$FRC, F4RC:f32:$FRB) - Complexity = 3
              // Dst: (FSELS:f32 F8RC:f64:$FRA, F4RC:f32:$FRC, F4RC:f32:$FRB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 37,  TARGET_VAL(ISD::FADD),// ->9624
/*9587*/    OPC_RecordChild0, // #0 = $FRA
/*9588*/    OPC_RecordChild1, // #1 = $FRB
/*9589*/    OPC_SwitchType /*3 cases */, 9,  MVT::f64,// ->9601
/*9592*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FADD), 0,
                  1/*#VTs*/, MVT::f64, 2/*#Ops*/, 0, 1, 
              // Src: (fadd:f64 F8RC:f64:$FRA, F8RC:f64:$FRB) - Complexity = 3
              // Dst: (FADD:f64 F8RC:f64:$FRA, F8RC:f64:$FRB)
            /*SwitchType*/ 9,  MVT::f32,// ->9612
/*9603*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FADDS), 0,
                  1/*#VTs*/, MVT::f32, 2/*#Ops*/, 0, 1, 
              // Src: (fadd:f32 F4RC:f32:$FRA, F4RC:f32:$FRB) - Complexity = 3
              // Dst: (FADDS:f32 F4RC:f32:$FRA, F4RC:f32:$FRB)
            /*SwitchType*/ 9,  MVT::v4f32,// ->9623
/*9614*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VADDFP), 0,
                  1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 0, 1, 
              // Src: (fadd:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB) - Complexity = 3
              // Dst: (VADDFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::FDIV),// ->9653
/*9627*/    OPC_RecordChild0, // #0 = $FRA
/*9628*/    OPC_RecordChild1, // #1 = $FRB
/*9629*/    OPC_SwitchType /*2 cases */, 9,  MVT::f64,// ->9641
/*9632*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FDIV), 0,
                  1/*#VTs*/, MVT::f64, 2/*#Ops*/, 0, 1, 
              // Src: (fdiv:f64 F8RC:f64:$FRA, F8RC:f64:$FRB) - Complexity = 3
              // Dst: (FDIV:f64 F8RC:f64:$FRA, F8RC:f64:$FRB)
            /*SwitchType*/ 9,  MVT::f32,// ->9652
/*9643*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FDIVS), 0,
                  1/*#VTs*/, MVT::f32, 2/*#Ops*/, 0, 1, 
              // Src: (fdiv:f32 F4RC:f32:$FRA, F4RC:f32:$FRB) - Complexity = 3
              // Dst: (FDIVS:f32 F4RC:f32:$FRA, F4RC:f32:$FRB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 45,  TARGET_VAL(ISD::FMUL),// ->9701
/*9656*/    OPC_RecordChild0, // #0 = $FRA
/*9657*/    OPC_RecordChild1, // #1 = $FRC
/*9658*/    OPC_SwitchType /*3 cases */, 9,  MVT::f64,// ->9670
/*9661*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FMUL), 0,
                  1/*#VTs*/, MVT::f64, 2/*#Ops*/, 0, 1, 
              // Src: (fmul:f64 F8RC:f64:$FRA, F8RC:f64:$FRC) - Complexity = 3
              // Dst: (FMUL:f64 F8RC:f64:$FRA, F8RC:f64:$FRC)
            /*SwitchType*/ 9,  MVT::f32,// ->9681
/*9672*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FMULS), 0,
                  1/*#VTs*/, MVT::f32, 2/*#Ops*/, 0, 1, 
              // Src: (fmul:f32 F4RC:f32:$FRA, F4RC:f32:$FRC) - Complexity = 3
              // Dst: (FMULS:f32 F4RC:f32:$FRA, F4RC:f32:$FRC)
            /*SwitchType*/ 17,  MVT::v4f32,// ->9700
/*9683*/      OPC_EmitNode, TARGET_VAL(PPC::V_SET0), 0,
                  1/*#VTs*/, MVT::v4i32, 0/*#Ops*/,  // Results = #2
/*9690*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VMADDFP), 0,
                  1/*#VTs*/, MVT::v4f32, 3/*#Ops*/, 0, 1, 2, 
              // Src: (fmul:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB) - Complexity = 3
              // Dst: (VMADDFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB, (V_SET0:v4i32))
            0, // EndSwitchType
          /*SwitchOpcode*/ 37,  TARGET_VAL(ISD::FSUB),// ->9741
/*9704*/    OPC_RecordChild0, // #0 = $FRA
/*9705*/    OPC_RecordChild1, // #1 = $FRB
/*9706*/    OPC_SwitchType /*3 cases */, 9,  MVT::f64,// ->9718
/*9709*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FSUB), 0,
                  1/*#VTs*/, MVT::f64, 2/*#Ops*/, 0, 1, 
              // Src: (fsub:f64 F8RC:f64:$FRA, F8RC:f64:$FRB) - Complexity = 3
              // Dst: (FSUB:f64 F8RC:f64:$FRA, F8RC:f64:$FRB)
            /*SwitchType*/ 9,  MVT::f32,// ->9729
/*9720*/      OPC_MorphNodeTo, TARGET_VAL(PPC::FSUBS), 0,
                  1/*#VTs*/, MVT::f32, 2/*#Ops*/, 0, 1, 
              // Src: (fsub:f32 F4RC:f32:$FRA, F4RC:f32:$FRB) - Complexity = 3
              // Dst: (FSUBS:f32 F4RC:f32:$FRA, F4RC:f32:$FRB)
            /*SwitchType*/ 9,  MVT::v4f32,// ->9740
/*9731*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VSUBFP), 0,
                  1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 0, 1, 
              // Src: (fsub:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB) - Complexity = 3
              // Dst: (VSUBFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
            0, // EndSwitchType
          /*SwitchOpcode*/ 13,  TARGET_VAL(ISD::FP_EXTEND),// ->9757
/*9744*/    OPC_RecordChild0, // #0 = $src
/*9745*/    OPC_EmitInteger, MVT::i32, PPC::F8RCRegClassID,
/*9748*/    OPC_MorphNodeTo, TARGET_VAL(TargetOpcode::COPY_TO_REGCLASS), 0,
                1/*#VTs*/, MVT::f64, 2/*#Ops*/, 0, 1, 
            // Src: (fextend:f64 F4RC:f32:$src) - Complexity = 3
            // Dst: (COPY_TO_REGCLASS:f64 F4RC:f32:$src, F8RC:f64)
          /*SwitchOpcode*/ 11,  TARGET_VAL(PPCISD::FCFID),// ->9771
/*9760*/    OPC_RecordChild0, // #0 = $frB
/*9761*/    OPC_CheckType, MVT::f64,
/*9763*/    OPC_MorphNodeTo, TARGET_VAL(PPC::FCFID), 0,
                1/*#VTs*/, MVT::f64, 1/*#Ops*/, 0, 
            // Src: (PPCfcfid:f64 F8RC:f64:$frB) - Complexity = 3
            // Dst: (FCFID:f64 F8RC:f64:$frB)
          /*SwitchOpcode*/ 11,  TARGET_VAL(PPCISD::FCTIDZ),// ->9785
/*9774*/    OPC_RecordChild0, // #0 = $frB
/*9775*/    OPC_CheckType, MVT::f64,
/*9777*/    OPC_MorphNodeTo, TARGET_VAL(PPC::FCTIDZ), 0,
                1/*#VTs*/, MVT::f64, 1/*#Ops*/, 0, 
            // Src: (PPCfctidz:f64 F8RC:f64:$frB) - Complexity = 3
            // Dst: (FCTIDZ:f64 F8RC:f64:$frB)
          /*SwitchOpcode*/ 84|128,1/*212*/,  TARGET_VAL(PPCISD::VCMP),// ->10001
/*9789*/    OPC_RecordChild0, // #0 = $vA
/*9790*/    OPC_RecordChild1, // #1 = $vB
/*9791*/    OPC_MoveChild, 2,
/*9793*/    OPC_Scope, 14, /*->9809*/ // 13 children in Scope
/*9795*/      OPC_CheckInteger, 6, 
/*9797*/      OPC_MoveParent,
/*9798*/      OPC_CheckType, MVT::v16i8,
/*9800*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPEQUB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB, 6:i32) - Complexity = 8
              // Dst: (VCMPEQUB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*9809*/    /*Scope*/ 15, /*->9825*/
/*9810*/      OPC_CheckInteger, 6|128,6/*774*/, 
/*9813*/      OPC_MoveParent,
/*9814*/      OPC_CheckType, MVT::v16i8,
/*9816*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTSB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB, 774:i32) - Complexity = 8
              // Dst: (VCMPGTSB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*9825*/    /*Scope*/ 15, /*->9841*/
/*9826*/      OPC_CheckInteger, 6|128,4/*518*/, 
/*9829*/      OPC_MoveParent,
/*9830*/      OPC_CheckType, MVT::v16i8,
/*9832*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTUB), 0,
                  1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB, 518:i32) - Complexity = 8
              // Dst: (VCMPGTUB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*9841*/    /*Scope*/ 14, /*->9856*/
/*9842*/      OPC_CheckInteger, 70, 
/*9844*/      OPC_MoveParent,
/*9845*/      OPC_CheckType, MVT::v8i16,
/*9847*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPEQUH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB, 70:i32) - Complexity = 8
              // Dst: (VCMPEQUH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*9856*/    /*Scope*/ 15, /*->9872*/
/*9857*/      OPC_CheckInteger, 70|128,6/*838*/, 
/*9860*/      OPC_MoveParent,
/*9861*/      OPC_CheckType, MVT::v8i16,
/*9863*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTSH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB, 838:i32) - Complexity = 8
              // Dst: (VCMPGTSH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*9872*/    /*Scope*/ 15, /*->9888*/
/*9873*/      OPC_CheckInteger, 70|128,4/*582*/, 
/*9876*/      OPC_MoveParent,
/*9877*/      OPC_CheckType, MVT::v8i16,
/*9879*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTUH), 0,
                  1/*#VTs*/, MVT::v8i16, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB, 582:i32) - Complexity = 8
              // Dst: (VCMPGTUH:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*9888*/    /*Scope*/ 15, /*->9904*/
/*9889*/      OPC_CheckInteger, 6|128,1/*134*/, 
/*9892*/      OPC_MoveParent,
/*9893*/      OPC_CheckType, MVT::v4i32,
/*9895*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPEQUW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB, 134:i32) - Complexity = 8
              // Dst: (VCMPEQUW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*9904*/    /*Scope*/ 15, /*->9920*/
/*9905*/      OPC_CheckInteger, 6|128,7/*902*/, 
/*9908*/      OPC_MoveParent,
/*9909*/      OPC_CheckType, MVT::v4i32,
/*9911*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTSW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB, 902:i32) - Complexity = 8
              // Dst: (VCMPGTSW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*9920*/    /*Scope*/ 15, /*->9936*/
/*9921*/      OPC_CheckInteger, 6|128,5/*646*/, 
/*9924*/      OPC_MoveParent,
/*9925*/      OPC_CheckType, MVT::v4i32,
/*9927*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTUW), 0,
                  1/*#VTs*/, MVT::v4i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB, 646:i32) - Complexity = 8
              // Dst: (VCMPGTUW:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*9936*/    /*Scope*/ 15, /*->9952*/
/*9937*/      OPC_CheckInteger, 70|128,7/*966*/, 
/*9940*/      OPC_MoveParent,
/*9941*/      OPC_CheckType, MVT::v4f32,
/*9943*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPBFP), 0,
                  1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB, 966:i32) - Complexity = 8
              // Dst: (VCMPBFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*9952*/    /*Scope*/ 15, /*->9968*/
/*9953*/      OPC_CheckInteger, 70|128,1/*198*/, 
/*9956*/      OPC_MoveParent,
/*9957*/      OPC_CheckType, MVT::v4f32,
/*9959*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPEQFP), 0,
                  1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB, 198:i32) - Complexity = 8
              // Dst: (VCMPEQFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*9968*/    /*Scope*/ 15, /*->9984*/
/*9969*/      OPC_CheckInteger, 70|128,3/*454*/, 
/*9972*/      OPC_MoveParent,
/*9973*/      OPC_CheckType, MVT::v4f32,
/*9975*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGEFP), 0,
                  1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB, 454:i32) - Complexity = 8
              // Dst: (VCMPGEFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*9984*/    /*Scope*/ 15, /*->10000*/
/*9985*/      OPC_CheckInteger, 70|128,5/*710*/, 
/*9988*/      OPC_MoveParent,
/*9989*/      OPC_CheckType, MVT::v4f32,
/*9991*/      OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTFP), 0,
                  1/*#VTs*/, MVT::v4f32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB, 710:i32) - Complexity = 8
              // Dst: (VCMPGTFP:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*10000*/   0, /*End of Scope*/
          /*SwitchOpcode*/ 97|128,1/*225*/,  TARGET_VAL(PPCISD::VCMPo),// ->10230
/*10005*/   OPC_RecordChild0, // #0 = $vA
/*10006*/   OPC_RecordChild1, // #1 = $vB
/*10007*/   OPC_MoveChild, 2,
/*10009*/   OPC_Scope, 15, /*->10026*/ // 13 children in Scope
/*10011*/     OPC_CheckInteger, 6, 
/*10013*/     OPC_MoveParent,
/*10014*/     OPC_CheckType, MVT::v16i8,
/*10016*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPEQUBo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v16i8, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB, 6:i32) - Complexity = 8
              // Dst: (VCMPEQUBo:v16i8:i32 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10026*/   /*Scope*/ 16, /*->10043*/
/*10027*/     OPC_CheckInteger, 6|128,6/*774*/, 
/*10030*/     OPC_MoveParent,
/*10031*/     OPC_CheckType, MVT::v16i8,
/*10033*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTSBo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v16i8, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB, 774:i32) - Complexity = 8
              // Dst: (VCMPGTSBo:v16i8:i32 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10043*/   /*Scope*/ 16, /*->10060*/
/*10044*/     OPC_CheckInteger, 6|128,4/*518*/, 
/*10047*/     OPC_MoveParent,
/*10048*/     OPC_CheckType, MVT::v16i8,
/*10050*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTUBo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v16i8, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB, 518:i32) - Complexity = 8
              // Dst: (VCMPGTUBo:v16i8:i32 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10060*/   /*Scope*/ 15, /*->10076*/
/*10061*/     OPC_CheckInteger, 70, 
/*10063*/     OPC_MoveParent,
/*10064*/     OPC_CheckType, MVT::v8i16,
/*10066*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPEQUHo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v8i16, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB, 70:i32) - Complexity = 8
              // Dst: (VCMPEQUHo:v8i16:i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*10076*/   /*Scope*/ 16, /*->10093*/
/*10077*/     OPC_CheckInteger, 70|128,6/*838*/, 
/*10080*/     OPC_MoveParent,
/*10081*/     OPC_CheckType, MVT::v8i16,
/*10083*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTSHo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v8i16, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB, 838:i32) - Complexity = 8
              // Dst: (VCMPGTSHo:v8i16:i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*10093*/   /*Scope*/ 16, /*->10110*/
/*10094*/     OPC_CheckInteger, 70|128,4/*582*/, 
/*10097*/     OPC_MoveParent,
/*10098*/     OPC_CheckType, MVT::v8i16,
/*10100*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTUHo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v8i16, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v8i16 VRRC:v8i16:$vA, VRRC:v8i16:$vB, 582:i32) - Complexity = 8
              // Dst: (VCMPGTUHo:v8i16:i32 VRRC:v8i16:$vA, VRRC:v8i16:$vB)
/*10110*/   /*Scope*/ 16, /*->10127*/
/*10111*/     OPC_CheckInteger, 6|128,1/*134*/, 
/*10114*/     OPC_MoveParent,
/*10115*/     OPC_CheckType, MVT::v4i32,
/*10117*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPEQUWo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v4i32, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB, 134:i32) - Complexity = 8
              // Dst: (VCMPEQUWo:v4i32:i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*10127*/   /*Scope*/ 16, /*->10144*/
/*10128*/     OPC_CheckInteger, 6|128,7/*902*/, 
/*10131*/     OPC_MoveParent,
/*10132*/     OPC_CheckType, MVT::v4i32,
/*10134*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTSWo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v4i32, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB, 902:i32) - Complexity = 8
              // Dst: (VCMPGTSWo:v4i32:i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*10144*/   /*Scope*/ 16, /*->10161*/
/*10145*/     OPC_CheckInteger, 6|128,5/*646*/, 
/*10148*/     OPC_MoveParent,
/*10149*/     OPC_CheckType, MVT::v4i32,
/*10151*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTUWo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v4i32, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v4i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB, 646:i32) - Complexity = 8
              // Dst: (VCMPGTUWo:v4i32:i32 VRRC:v4i32:$vA, VRRC:v4i32:$vB)
/*10161*/   /*Scope*/ 16, /*->10178*/
/*10162*/     OPC_CheckInteger, 70|128,7/*966*/, 
/*10165*/     OPC_MoveParent,
/*10166*/     OPC_CheckType, MVT::v4f32,
/*10168*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPBFPo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v4f32, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB, 966:i32) - Complexity = 8
              // Dst: (VCMPBFPo:v4f32:i32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*10178*/   /*Scope*/ 16, /*->10195*/
/*10179*/     OPC_CheckInteger, 70|128,1/*198*/, 
/*10182*/     OPC_MoveParent,
/*10183*/     OPC_CheckType, MVT::v4f32,
/*10185*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPEQFPo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v4f32, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB, 198:i32) - Complexity = 8
              // Dst: (VCMPEQFPo:v4f32:i32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*10195*/   /*Scope*/ 16, /*->10212*/
/*10196*/     OPC_CheckInteger, 70|128,3/*454*/, 
/*10199*/     OPC_MoveParent,
/*10200*/     OPC_CheckType, MVT::v4f32,
/*10202*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGEFPo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v4f32, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB, 454:i32) - Complexity = 8
              // Dst: (VCMPGEFPo:v4f32:i32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*10212*/   /*Scope*/ 16, /*->10229*/
/*10213*/     OPC_CheckInteger, 70|128,5/*710*/, 
/*10216*/     OPC_MoveParent,
/*10217*/     OPC_CheckType, MVT::v4f32,
/*10219*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VCMPGTFPo), 0|OPFL_GlueOutput,
                  2/*#VTs*/, MVT::v4f32, MVT::i32, 2/*#Ops*/, 0, 1, 
              // Src: (PPCvcmp_o:v4f32 VRRC:v4f32:$vA, VRRC:v4f32:$vB, 710:i32) - Complexity = 8
              // Dst: (VCMPGTFPo:v4f32:i32 VRRC:v4f32:$vA, VRRC:v4f32:$vB)
/*10229*/   0, /*End of Scope*/
          /*SwitchOpcode*/ 52|128,2/*308*/,  TARGET_VAL(ISD::VECTOR_SHUFFLE),// ->10542
/*10234*/   OPC_Scope, 73, /*->10309*/ // 4 children in Scope
/*10236*/     OPC_RecordNode, // #0 = $UIMM
/*10237*/     OPC_RecordChild0, // #1 = $vB
/*10238*/     OPC_MoveChild, 1,
/*10240*/     OPC_CheckOpcode, TARGET_VAL(ISD::UNDEF),
/*10243*/     OPC_MoveParent,
/*10244*/     OPC_CheckType, MVT::v16i8,
/*10246*/     OPC_Scope, 14, /*->10262*/ // 4 children in Scope
/*10248*/       OPC_CheckPredicate, 67, // Predicate_vspltb_shuffle
/*10250*/       OPC_EmitNodeXForm, 9, 0, // VSPLTB_get_imm
/*10253*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VSPLTB), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 2, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vB, (undef:v16i8))<<P:Predicate_vspltb_shuffle>><<X:VSPLTB_get_imm>>:$UIMM - Complexity = 7
                // Dst: (VSPLTB:v16i8 (VSPLTB_get_imm:i32 (vector_shuffle:v16i8 VRRC:v16i8:$vB, (undef:v16i8)):$UIMM), VRRC:v16i8:$vB)
/*10262*/     /*Scope*/ 14, /*->10277*/
/*10263*/       OPC_CheckPredicate, 68, // Predicate_vsplth_shuffle
/*10265*/       OPC_EmitNodeXForm, 10, 0, // VSPLTH_get_imm
/*10268*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VSPLTH), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 2, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vB, (undef:v16i8))<<P:Predicate_vsplth_shuffle>><<X:VSPLTH_get_imm>>:$UIMM - Complexity = 7
                // Dst: (VSPLTH:v16i8 (VSPLTH_get_imm:i32 (vector_shuffle:v16i8 VRRC:v16i8:$vB, (undef:v16i8)):$UIMM), VRRC:v16i8:$vB)
/*10277*/     /*Scope*/ 14, /*->10292*/
/*10278*/       OPC_CheckPredicate, 69, // Predicate_vspltw_shuffle
/*10280*/       OPC_EmitNodeXForm, 11, 0, // VSPLTW_get_imm
/*10283*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VSPLTW), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 2, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vB, (undef:v16i8))<<P:Predicate_vspltw_shuffle>><<X:VSPLTW_get_imm>>:$UIMM - Complexity = 7
                // Dst: (VSPLTW:v16i8 (VSPLTW_get_imm:i32 (vector_shuffle:v16i8 VRRC:v16i8:$vB, (undef:v16i8)):$UIMM), VRRC:v16i8:$vB)
/*10292*/     /*Scope*/ 15, /*->10308*/
/*10293*/       OPC_CheckPredicate, 70, // Predicate_vsldoi_unary_shuffle
/*10295*/       OPC_EmitNodeXForm, 12, 0, // VSLDOI_unary_get_imm
/*10298*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VSLDOI), 0,
                    1/*#VTs*/, MVT::v16i8, 3/*#Ops*/, 1, 1, 2, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, (undef:v16i8))<<P:Predicate_vsldoi_unary_shuffle>><<X:VSLDOI_unary_get_imm>>:$in - Complexity = 7
                // Dst: (VSLDOI:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vA, (VSLDOI_unary_get_imm:i32 VRRC:v16i8:$in))
/*10308*/     0, /*End of Scope*/
/*10309*/   /*Scope*/ 107, /*->10417*/
/*10310*/     OPC_RecordChild0, // #0 = $vA
/*10311*/     OPC_MoveChild, 1,
/*10313*/     OPC_CheckOpcode, TARGET_VAL(ISD::UNDEF),
/*10316*/     OPC_MoveParent,
/*10317*/     OPC_CheckType, MVT::v16i8,
/*10319*/     OPC_Scope, 11, /*->10332*/ // 8 children in Scope
/*10321*/       OPC_CheckPredicate, 71, // Predicate_vpkuwum_unary_shuffle
/*10323*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VPKUWUM), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 0, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, (undef:v16i8))<<P:Predicate_vpkuwum_unary_shuffle>> - Complexity = 7
                // Dst: (VPKUWUM:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vA)
/*10332*/     /*Scope*/ 11, /*->10344*/
/*10333*/       OPC_CheckPredicate, 72, // Predicate_vpkuhum_unary_shuffle
/*10335*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VPKUHUM), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 0, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, (undef:v16i8))<<P:Predicate_vpkuhum_unary_shuffle>> - Complexity = 7
                // Dst: (VPKUHUM:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vA)
/*10344*/     /*Scope*/ 11, /*->10356*/
/*10345*/       OPC_CheckPredicate, 73, // Predicate_vmrglb_unary_shuffle
/*10347*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGLB), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 0, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, (undef:v16i8))<<P:Predicate_vmrglb_unary_shuffle>> - Complexity = 7
                // Dst: (VMRGLB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vA)
/*10356*/     /*Scope*/ 11, /*->10368*/
/*10357*/       OPC_CheckPredicate, 74, // Predicate_vmrglh_unary_shuffle
/*10359*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGLH), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 0, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, (undef:v16i8))<<P:Predicate_vmrglh_unary_shuffle>> - Complexity = 7
                // Dst: (VMRGLH:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vA)
/*10368*/     /*Scope*/ 11, /*->10380*/
/*10369*/       OPC_CheckPredicate, 75, // Predicate_vmrglw_unary_shuffle
/*10371*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGLW), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 0, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, (undef:v16i8))<<P:Predicate_vmrglw_unary_shuffle>> - Complexity = 7
                // Dst: (VMRGLW:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vA)
/*10380*/     /*Scope*/ 11, /*->10392*/
/*10381*/       OPC_CheckPredicate, 76, // Predicate_vmrghb_unary_shuffle
/*10383*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGHB), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 0, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, (undef:v16i8))<<P:Predicate_vmrghb_unary_shuffle>> - Complexity = 7
                // Dst: (VMRGHB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vA)
/*10392*/     /*Scope*/ 11, /*->10404*/
/*10393*/       OPC_CheckPredicate, 77, // Predicate_vmrghh_unary_shuffle
/*10395*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGHH), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 0, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, (undef:v16i8))<<P:Predicate_vmrghh_unary_shuffle>> - Complexity = 7
                // Dst: (VMRGHH:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vA)
/*10404*/     /*Scope*/ 11, /*->10416*/
/*10405*/       OPC_CheckPredicate, 78, // Predicate_vmrghw_unary_shuffle
/*10407*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGHW), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 0, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, (undef:v16i8))<<P:Predicate_vmrghw_unary_shuffle>> - Complexity = 7
                // Dst: (VMRGHW:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vA)
/*10416*/     0, /*End of Scope*/
/*10417*/   /*Scope*/ 20, /*->10438*/
/*10418*/     OPC_RecordNode, // #0 = $SH
/*10419*/     OPC_RecordChild0, // #1 = $vA
/*10420*/     OPC_RecordChild1, // #2 = $vB
/*10421*/     OPC_CheckPredicate, 79, // Predicate_vsldoi_shuffle
/*10423*/     OPC_CheckType, MVT::v16i8,
/*10425*/     OPC_EmitNodeXForm, 13, 0, // VSLDOI_get_imm
/*10428*/     OPC_MorphNodeTo, TARGET_VAL(PPC::VSLDOI), 0,
                  1/*#VTs*/, MVT::v16i8, 3/*#Ops*/, 1, 2, 3, 
              // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)<<P:Predicate_vsldoi_shuffle>><<X:VSLDOI_get_imm>>:$SH - Complexity = 4
              // Dst: (VSLDOI:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB, (VSLDOI_get_imm:i32 (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB):$SH))
/*10438*/   /*Scope*/ 102, /*->10541*/
/*10439*/     OPC_RecordChild0, // #0 = $vA
/*10440*/     OPC_RecordChild1, // #1 = $vB
/*10441*/     OPC_CheckType, MVT::v16i8,
/*10443*/     OPC_Scope, 11, /*->10456*/ // 8 children in Scope
/*10445*/       OPC_CheckPredicate, 80, // Predicate_vmrghb_shuffle
/*10447*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGHB), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)<<P:Predicate_vmrghb_shuffle>> - Complexity = 4
                // Dst: (VMRGHB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10456*/     /*Scope*/ 11, /*->10468*/
/*10457*/       OPC_CheckPredicate, 81, // Predicate_vmrghh_shuffle
/*10459*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGHH), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)<<P:Predicate_vmrghh_shuffle>> - Complexity = 4
                // Dst: (VMRGHH:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10468*/     /*Scope*/ 11, /*->10480*/
/*10469*/       OPC_CheckPredicate, 82, // Predicate_vmrghw_shuffle
/*10471*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGHW), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)<<P:Predicate_vmrghw_shuffle>> - Complexity = 4
                // Dst: (VMRGHW:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10480*/     /*Scope*/ 11, /*->10492*/
/*10481*/       OPC_CheckPredicate, 83, // Predicate_vmrglb_shuffle
/*10483*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGLB), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)<<P:Predicate_vmrglb_shuffle>> - Complexity = 4
                // Dst: (VMRGLB:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10492*/     /*Scope*/ 11, /*->10504*/
/*10493*/       OPC_CheckPredicate, 84, // Predicate_vmrglh_shuffle
/*10495*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGLH), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)<<P:Predicate_vmrglh_shuffle>> - Complexity = 4
                // Dst: (VMRGLH:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10504*/     /*Scope*/ 11, /*->10516*/
/*10505*/       OPC_CheckPredicate, 85, // Predicate_vmrglw_shuffle
/*10507*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VMRGLW), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)<<P:Predicate_vmrglw_shuffle>> - Complexity = 4
                // Dst: (VMRGLW:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10516*/     /*Scope*/ 11, /*->10528*/
/*10517*/       OPC_CheckPredicate, 86, // Predicate_vpkuhum_shuffle
/*10519*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VPKUHUM), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)<<P:Predicate_vpkuhum_shuffle>> - Complexity = 4
                // Dst: (VPKUHUM:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10528*/     /*Scope*/ 11, /*->10540*/
/*10529*/       OPC_CheckPredicate, 87, // Predicate_vpkuwum_shuffle
/*10531*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VPKUWUM), 0,
                    1/*#VTs*/, MVT::v16i8, 2/*#Ops*/, 0, 1, 
                // Src: (vector_shuffle:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)<<P:Predicate_vpkuwum_shuffle>> - Complexity = 4
                // Dst: (VPKUWUM:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB)
/*10540*/     0, /*End of Scope*/
/*10541*/   0, /*End of Scope*/
          /*SwitchOpcode*/ 17,  TARGET_VAL(ISD::CALLSEQ_START),// ->10562
/*10545*/   OPC_RecordNode,   // #0 = 'callseq_start' chained node
/*10546*/   OPC_RecordChild1, // #1 = $amt
/*10547*/   OPC_MoveChild, 1,
/*10549*/   OPC_CheckOpcode, TARGET_VAL(ISD::TargetConstant),
/*10552*/   OPC_MoveParent,
/*10553*/   OPC_EmitMergeInputChains1_0,
/*10554*/   OPC_MorphNodeTo, TARGET_VAL(PPC::ADJCALLSTACKDOWN), 0|OPFL_Chain|OPFL_GlueOutput,
                1/*#VTs*/, MVT::i32, 1/*#Ops*/, 1, 
            // Src: (callseq_start (timm:i32):$amt) - Complexity = 6
            // Dst: (ADJCALLSTACKDOWN:i32 (timm:i32):$amt)
          /*SwitchOpcode*/ 98,  TARGET_VAL(PPCISD::CALL_Darwin),// ->10663
/*10565*/   OPC_RecordNode,   // #0 = 'PPCcall_Darwin' chained node
/*10566*/   OPC_CaptureGlueInput,
/*10567*/   OPC_RecordChild1, // #1 = $func
/*10568*/   OPC_MoveChild, 1,
/*10570*/   OPC_SwitchOpcode /*3 cases */, 30,  TARGET_VAL(ISD::Constant),// ->10604
/*10574*/     OPC_SwitchType /*2 cases */, 12,  MVT::i32,// ->10589
/*10577*/       OPC_MoveParent,
/*10578*/       OPC_EmitMergeInputChains1_0,
/*10579*/       OPC_EmitConvertToTarget, 1,
/*10581*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BLA_Darwin), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 2, 
                // Src: (PPCcall_Darwin (imm:i32):$func) - Complexity = 6
                // Dst: (BLA_Darwin:i32 (imm:i32):$func)
              /*SwitchType*/ 12,  MVT::i64,// ->10603
/*10591*/       OPC_MoveParent,
/*10592*/       OPC_EmitMergeInputChains1_0,
/*10593*/       OPC_EmitConvertToTarget, 1,
/*10595*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BLA8_Darwin), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 2, 
                // Src: (PPCcall_Darwin (imm:i64):$func) - Complexity = 6
                // Dst: (BLA8_Darwin:i64 (imm:i64):$func)
              0, // EndSwitchType
            /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::TargetGlobalAddress),// ->10633
/*10607*/     OPC_SwitchType /*2 cases */, 10,  MVT::i32,// ->10620
/*10610*/       OPC_MoveParent,
/*10611*/       OPC_EmitMergeInputChains1_0,
/*10612*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BL_Darwin), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 1, 
                // Src: (PPCcall_Darwin (tglobaladdr:i32):$dst) - Complexity = 6
                // Dst: (BL_Darwin:i32 (tglobaladdr:i32):$dst)
              /*SwitchType*/ 10,  MVT::i64,// ->10632
/*10622*/       OPC_MoveParent,
/*10623*/       OPC_EmitMergeInputChains1_0,
/*10624*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BL8_Darwin), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 1, 
                // Src: (PPCcall_Darwin (tglobaladdr:i64):$dst) - Complexity = 6
                // Dst: (BL8_Darwin:i64 (tglobaladdr:i64):$dst)
              0, // EndSwitchType
            /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::TargetExternalSymbol),// ->10662
/*10636*/     OPC_SwitchType /*2 cases */, 10,  MVT::i32,// ->10649
/*10639*/       OPC_MoveParent,
/*10640*/       OPC_EmitMergeInputChains1_0,
/*10641*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BL_Darwin), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 1, 
                // Src: (PPCcall_Darwin (texternalsym:i32):$dst) - Complexity = 6
                // Dst: (BL_Darwin:i32 (texternalsym:i32):$dst)
              /*SwitchType*/ 10,  MVT::i64,// ->10661
/*10651*/       OPC_MoveParent,
/*10652*/       OPC_EmitMergeInputChains1_0,
/*10653*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BL8_Darwin), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 1, 
                // Src: (PPCcall_Darwin (texternalsym:i64):$dst) - Complexity = 6
                // Dst: (BL8_Darwin:i64 (texternalsym:i64):$dst)
              0, // EndSwitchType
            0, // EndSwitchOpcode
          /*SwitchOpcode*/ 98,  TARGET_VAL(PPCISD::CALL_SVR4),// ->10764
/*10666*/   OPC_RecordNode,   // #0 = 'PPCcall_SVR4' chained node
/*10667*/   OPC_CaptureGlueInput,
/*10668*/   OPC_RecordChild1, // #1 = $func
/*10669*/   OPC_MoveChild, 1,
/*10671*/   OPC_SwitchOpcode /*3 cases */, 30,  TARGET_VAL(ISD::Constant),// ->10705
/*10675*/     OPC_SwitchType /*2 cases */, 12,  MVT::i32,// ->10690
/*10678*/       OPC_MoveParent,
/*10679*/       OPC_EmitMergeInputChains1_0,
/*10680*/       OPC_EmitConvertToTarget, 1,
/*10682*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BLA_SVR4), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 2, 
                // Src: (PPCcall_SVR4 (imm:i32):$func) - Complexity = 6
                // Dst: (BLA_SVR4:i32 (imm:i32):$func)
              /*SwitchType*/ 12,  MVT::i64,// ->10704
/*10692*/       OPC_MoveParent,
/*10693*/       OPC_EmitMergeInputChains1_0,
/*10694*/       OPC_EmitConvertToTarget, 1,
/*10696*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BLA8_ELF), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 2, 
                // Src: (PPCcall_SVR4 (imm:i64):$func) - Complexity = 6
                // Dst: (BLA8_ELF:i64 (imm:i64):$func)
              0, // EndSwitchType
            /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::TargetGlobalAddress),// ->10734
/*10708*/     OPC_SwitchType /*2 cases */, 10,  MVT::i32,// ->10721
/*10711*/       OPC_MoveParent,
/*10712*/       OPC_EmitMergeInputChains1_0,
/*10713*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BL_SVR4), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 1, 
                // Src: (PPCcall_SVR4 (tglobaladdr:i32):$dst) - Complexity = 6
                // Dst: (BL_SVR4:i32 (tglobaladdr:i32):$dst)
              /*SwitchType*/ 10,  MVT::i64,// ->10733
/*10723*/       OPC_MoveParent,
/*10724*/       OPC_EmitMergeInputChains1_0,
/*10725*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BL8_ELF), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 1, 
                // Src: (PPCcall_SVR4 (tglobaladdr:i64):$dst) - Complexity = 6
                // Dst: (BL8_ELF:i64 (tglobaladdr:i64):$dst)
              0, // EndSwitchType
            /*SwitchOpcode*/ 26,  TARGET_VAL(ISD::TargetExternalSymbol),// ->10763
/*10737*/     OPC_SwitchType /*2 cases */, 10,  MVT::i32,// ->10750
/*10740*/       OPC_MoveParent,
/*10741*/       OPC_EmitMergeInputChains1_0,
/*10742*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BL_SVR4), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i32, 1/*#Ops*/, 1, 
                // Src: (PPCcall_SVR4 (texternalsym:i32):$dst) - Complexity = 6
                // Dst: (BL_SVR4:i32 (texternalsym:i32):$dst)
              /*SwitchType*/ 10,  MVT::i64,// ->10762
/*10752*/       OPC_MoveParent,
/*10753*/       OPC_EmitMergeInputChains1_0,
/*10754*/       OPC_MorphNodeTo, TARGET_VAL(PPC::BL8_ELF), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                    1/*#VTs*/, MVT::i64, 1/*#Ops*/, 1, 
                // Src: (PPCcall_SVR4 (texternalsym:i64):$dst) - Complexity = 6
                // Dst: (BL8_ELF:i64 (texternalsym:i64):$dst)
              0, // EndSwitchType
            0, // EndSwitchOpcode
          /*SwitchOpcode*/ 19,  TARGET_VAL(PPCISD::MTFSB0),// ->10786
/*10767*/   OPC_CaptureGlueInput,
/*10768*/   OPC_RecordChild0, // #0 = $FM
/*10769*/   OPC_MoveChild, 0,
/*10771*/   OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*10774*/   OPC_CheckType, MVT::i32,
/*10776*/   OPC_MoveParent,
/*10777*/   OPC_EmitConvertToTarget, 0,
/*10779*/   OPC_MorphNodeTo, TARGET_VAL(PPC::MTFSB0), 0|OPFL_GlueInput|OPFL_GlueOutput,
                0/*#VTs*/, 1/*#Ops*/, 1, 
            // Src: (PPCmtfsb0 (imm:i32):$FM) - Complexity = 6
            // Dst: (MTFSB0 (imm:i32):$FM)
          /*SwitchOpcode*/ 19,  TARGET_VAL(PPCISD::MTFSB1),// ->10808
/*10789*/   OPC_CaptureGlueInput,
/*10790*/   OPC_RecordChild0, // #0 = $FM
/*10791*/   OPC_MoveChild, 0,
/*10793*/   OPC_CheckOpcode, TARGET_VAL(ISD::Constant),
/*10796*/   OPC_CheckType, MVT::i32,
/*10798*/   OPC_MoveParent,
/*10799*/   OPC_EmitConvertToTarget, 0,
/*10801*/   OPC_MorphNodeTo, TARGET_VAL(PPC::MTFSB1), 0|OPFL_GlueInput|OPFL_GlueOutput,
                0/*#VTs*/, 1/*#Ops*/, 1, 
            // Src: (PPCmtfsb1 (imm:i32):$FM) - Complexity = 6
            // Dst: (MTFSB1 (imm:i32):$FM)
          /*SwitchOpcode*/ 54,  TARGET_VAL(PPCISD::CALL_NOP_SVR4),// ->10865
/*10811*/   OPC_RecordNode,   // #0 = 'PPCcall_nop_SVR4' chained node
/*10812*/   OPC_CaptureGlueInput,
/*10813*/   OPC_RecordChild1, // #1 = $func
/*10814*/   OPC_MoveChild, 1,
/*10816*/   OPC_SwitchOpcode /*3 cases */, 14,  TARGET_VAL(ISD::Constant),// ->10834
/*10820*/     OPC_CheckType, MVT::i64,
/*10822*/     OPC_MoveParent,
/*10823*/     OPC_EmitMergeInputChains1_0,
/*10824*/     OPC_EmitConvertToTarget, 1,
/*10826*/     OPC_MorphNodeTo, TARGET_VAL(PPC::BLA8_NOP_ELF), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                  1/*#VTs*/, MVT::i64, 1/*#Ops*/, 2, 
              // Src: (PPCcall_nop_SVR4 (imm:i64):$func) - Complexity = 6
              // Dst: (BLA8_NOP_ELF:i64 (imm:i64):$func)
            /*SwitchOpcode*/ 12,  TARGET_VAL(ISD::TargetGlobalAddress),// ->10849
/*10837*/     OPC_CheckType, MVT::i64,
/*10839*/     OPC_MoveParent,
/*10840*/     OPC_EmitMergeInputChains1_0,
/*10841*/     OPC_MorphNodeTo, TARGET_VAL(PPC::BL8_NOP_ELF), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                  1/*#VTs*/, MVT::i64, 1/*#Ops*/, 1, 
              // Src: (PPCcall_nop_SVR4 (tglobaladdr:i64):$dst) - Complexity = 6
              // Dst: (BL8_NOP_ELF:i64 (tglobaladdr:i64):$dst)
            /*SwitchOpcode*/ 12,  TARGET_VAL(ISD::TargetExternalSymbol),// ->10864
/*10852*/     OPC_CheckType, MVT::i64,
/*10854*/     OPC_MoveParent,
/*10855*/     OPC_EmitMergeInputChains1_0,
/*10856*/     OPC_MorphNodeTo, TARGET_VAL(PPC::BL8_NOP_ELF), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic1,
                  1/*#VTs*/, MVT::i64, 1/*#Ops*/, 1, 
              // Src: (PPCcall_nop_SVR4 (texternalsym:i64):$dst) - Complexity = 6
              // Dst: (BL8_NOP_ELF:i64 (texternalsym:i64):$dst)
            0, // EndSwitchOpcode
          /*SwitchOpcode*/ 63,  TARGET_VAL(ISD::BUILD_VECTOR),// ->10931
/*10868*/   OPC_Scope, 48, /*->10918*/ // 2 children in Scope
/*10870*/     OPC_RecordNode, // #0 = $SIMM
/*10871*/     OPC_SwitchType /*3 cases */, 13,  MVT::v16i8,// ->10887
/*10874*/       OPC_CheckPredicate, 88, // Predicate_vecspltisb
/*10876*/       OPC_EmitNodeXForm, 14, 0, // VSPLTISB_get_imm
/*10879*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VSPLTISB), 0,
                    1/*#VTs*/, MVT::v16i8, 1/*#Ops*/, 1, 
                // Src: (build_vector:v16i8)<<P:Predicate_vecspltisb>><<X:VSPLTISB_get_imm>>:$SIMM - Complexity = 4
                // Dst: (VSPLTISB:v16i8 (VSPLTISB_get_imm:i32 (build_vector:v16i8):$SIMM))
              /*SwitchType*/ 13,  MVT::v8i16,// ->10902
/*10889*/       OPC_CheckPredicate, 89, // Predicate_vecspltish
/*10891*/       OPC_EmitNodeXForm, 15, 0, // VSPLTISH_get_imm
/*10894*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VSPLTISH), 0,
                    1/*#VTs*/, MVT::v8i16, 1/*#Ops*/, 1, 
                // Src: (build_vector:v8i16)<<P:Predicate_vecspltish>><<X:VSPLTISH_get_imm>>:$SIMM - Complexity = 4
                // Dst: (VSPLTISH:v8i16 (VSPLTISH_get_imm:i32 (build_vector:v8i16):$SIMM))
              /*SwitchType*/ 13,  MVT::v4i32,// ->10917
/*10904*/       OPC_CheckPredicate, 90, // Predicate_vecspltisw
/*10906*/       OPC_EmitNodeXForm, 16, 0, // VSPLTISW_get_imm
/*10909*/       OPC_MorphNodeTo, TARGET_VAL(PPC::VSPLTISW), 0,
                    1/*#VTs*/, MVT::v4i32, 1/*#Ops*/, 1, 
                // Src: (build_vector:v4i32)<<P:Predicate_vecspltisw>><<X:VSPLTISW_get_imm>>:$SIMM - Complexity = 4
                // Dst: (VSPLTISW:v4i32 (VSPLTISW_get_imm:i32 (build_vector:v4i32):$SIMM))
              0, // EndSwitchType
/*10918*/   /*Scope*/ 11, /*->10930*/
/*10919*/     OPC_CheckPredicate, 91, // Predicate_immAllZerosV
/*10921*/     OPC_CheckType, MVT::v4i32,
/*10923*/     OPC_MorphNodeTo, TARGET_VAL(PPC::V_SET0), 0,
                  1/*#VTs*/, MVT::v4i32, 0/*#Ops*/, 
              // Src: (build_vector:v4i32)<<P:Predicate_immAllZerosV>> - Complexity = 4
              // Dst: (V_SET0:v4i32)
/*10930*/   0, /*End of Scope*/
          /*SwitchOpcode*/ 83,  TARGET_VAL(ISD::BITCAST),// ->11017
/*10934*/   OPC_RecordChild0, // #0 = $src
/*10935*/   OPC_Scope, 19, /*->10956*/ // 4 children in Scope
/*10937*/     OPC_CheckChild0Type, MVT::v8i16,
/*10939*/     OPC_SwitchType /*3 cases */, 3,  MVT::v16i8,// ->10945
/*10942*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v16i8 VRRC:v8i16:$src) - Complexity = 3
                // Dst: VRRC:v16i8:$src
              /*SwitchType*/ 3,  MVT::v4i32,// ->10950
/*10947*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v4i32 VRRC:v8i16:$src) - Complexity = 3
                // Dst: VRRC:v4i32:$src
              /*SwitchType*/ 3,  MVT::v4f32,// ->10955
/*10952*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v4f32 VRRC:v8i16:$src) - Complexity = 3
                // Dst: VRRC:v4f32:$src
              0, // EndSwitchType
/*10956*/   /*Scope*/ 19, /*->10976*/
/*10957*/     OPC_CheckChild0Type, MVT::v4i32,
/*10959*/     OPC_SwitchType /*3 cases */, 3,  MVT::v16i8,// ->10965
/*10962*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v16i8 VRRC:v4i32:$src) - Complexity = 3
                // Dst: VRRC:v16i8:$src
              /*SwitchType*/ 3,  MVT::v8i16,// ->10970
/*10967*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v8i16 VRRC:v4i32:$src) - Complexity = 3
                // Dst: VRRC:v8i16:$src
              /*SwitchType*/ 3,  MVT::v4f32,// ->10975
/*10972*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v4f32 VRRC:v4i32:$src) - Complexity = 3
                // Dst: VRRC:v4f32:$src
              0, // EndSwitchType
/*10976*/   /*Scope*/ 19, /*->10996*/
/*10977*/     OPC_CheckChild0Type, MVT::v4f32,
/*10979*/     OPC_SwitchType /*3 cases */, 3,  MVT::v16i8,// ->10985
/*10982*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v16i8 VRRC:v4f32:$src) - Complexity = 3
                // Dst: VRRC:v16i8:$src
              /*SwitchType*/ 3,  MVT::v8i16,// ->10990
/*10987*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v8i16 VRRC:v4f32:$src) - Complexity = 3
                // Dst: VRRC:v8i16:$src
              /*SwitchType*/ 3,  MVT::v4i32,// ->10995
/*10992*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v4i32 VRRC:v4f32:$src) - Complexity = 3
                // Dst: VRRC:v4i32:$src
              0, // EndSwitchType
/*10996*/   /*Scope*/ 19, /*->11016*/
/*10997*/     OPC_CheckChild0Type, MVT::v16i8,
/*10999*/     OPC_SwitchType /*3 cases */, 3,  MVT::v8i16,// ->11005
/*11002*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v8i16 VRRC:v16i8:$src) - Complexity = 3
                // Dst: VRRC:v8i16:$src
              /*SwitchType*/ 3,  MVT::v4i32,// ->11010
/*11007*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v4i32 VRRC:v16i8:$src) - Complexity = 3
                // Dst: VRRC:v4i32:$src
              /*SwitchType*/ 3,  MVT::v4f32,// ->11015
/*11012*/       OPC_CompleteMatch, 1, 0, 
                // Src: (bitconvert:v4f32 VRRC:v16i8:$src) - Complexity = 3
                // Dst: VRRC:v4f32:$src
              0, // EndSwitchType
/*11016*/   0, /*End of Scope*/
          /*SwitchOpcode*/ 17,  TARGET_VAL(PPCISD::RET_FLAG),// ->11037
/*11020*/   OPC_RecordNode,   // #0 = 'retflag' chained node
/*11021*/   OPC_CaptureGlueInput,
/*11022*/   OPC_EmitMergeInputChains1_0,
/*11023*/   OPC_EmitInteger, MVT::i32, 20, 
/*11026*/   OPC_EmitRegister, MVT::i32, 0 /*zero_reg*/,
/*11029*/   OPC_MorphNodeTo, TARGET_VAL(PPC::BLR), 0|OPFL_Chain|OPFL_GlueInput|OPFL_Variadic0,
                0/*#VTs*/, 2/*#Ops*/, 1, 2, 
            // Src: (retflag) - Complexity = 3
            // Dst: (BLR)
          /*SwitchOpcode*/ 16,  TARGET_VAL(ISD::BR),// ->11056
/*11040*/   OPC_RecordNode,   // #0 = 'br' chained node
/*11041*/   OPC_RecordChild1, // #1 = $dst
/*11042*/   OPC_MoveChild, 1,
/*11044*/   OPC_CheckOpcode, TARGET_VAL(ISD::BasicBlock),
/*11047*/   OPC_MoveParent,
/*11048*/   OPC_EmitMergeInputChains1_0,
/*11049*/   OPC_MorphNodeTo, TARGET_VAL(PPC::B), 0|OPFL_Chain,
                0/*#VTs*/, 1/*#Ops*/, 1, 
            // Src: (br (bb:Other):$dst) - Complexity = 3
            // Dst: (B (bb:Other):$dst)
          /*SwitchOpcode*/ 26,  TARGET_VAL(PPCISD::BCTRL_Darwin),// ->11085
/*11059*/   OPC_RecordNode,   // #0 = 'PPCbctrl_Darwin' chained node
/*11060*/   OPC_CaptureGlueInput,
/*11061*/   OPC_Scope, 10, /*->11073*/ // 2 children in Scope
/*11063*/     OPC_CheckPatternPredicate, 0, // (!PPCSubTarget.isPPC64())
/*11065*/     OPC_EmitMergeInputChains1_0,
/*11066*/     OPC_MorphNodeTo, TARGET_VAL(PPC::BCTRL_Darwin), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic0,
                  1/*#VTs*/, MVT::i32, 0/*#Ops*/, 
              // Src: (PPCbctrl_Darwin) - Complexity = 3
              // Dst: (BCTRL_Darwin:i32)
/*11073*/   /*Scope*/ 10, /*->11084*/
/*11074*/     OPC_CheckPatternPredicate, 1, // (PPCSubTarget.isPPC64())
/*11076*/     OPC_EmitMergeInputChains1_0,
/*11077*/     OPC_MorphNodeTo, TARGET_VAL(PPC::BCTRL8_Darwin), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic0,
                  1/*#VTs*/, MVT::i64, 0/*#Ops*/, 
              // Src: (PPCbctrl_Darwin) - Complexity = 3
              // Dst: (BCTRL8_Darwin:i64)
/*11084*/   0, /*End of Scope*/
          /*SwitchOpcode*/ 26,  TARGET_VAL(PPCISD::BCTRL_SVR4),// ->11114
/*11088*/   OPC_RecordNode,   // #0 = 'PPCbctrl_SVR4' chained node
/*11089*/   OPC_CaptureGlueInput,
/*11090*/   OPC_Scope, 10, /*->11102*/ // 2 children in Scope
/*11092*/     OPC_CheckPatternPredicate, 0, // (!PPCSubTarget.isPPC64())
/*11094*/     OPC_EmitMergeInputChains1_0,
/*11095*/     OPC_MorphNodeTo, TARGET_VAL(PPC::BCTRL_SVR4), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic0,
                  1/*#VTs*/, MVT::i32, 0/*#Ops*/, 
              // Src: (PPCbctrl_SVR4) - Complexity = 3
              // Dst: (BCTRL_SVR4:i32)
/*11102*/   /*Scope*/ 10, /*->11113*/
/*11103*/     OPC_CheckPatternPredicate, 1, // (PPCSubTarget.isPPC64())
/*11105*/     OPC_EmitMergeInputChains1_0,
/*11106*/     OPC_MorphNodeTo, TARGET_VAL(PPC::BCTRL8_ELF), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput|OPFL_Variadic0,
                  1/*#VTs*/, MVT::i64, 0/*#Ops*/, 
              // Src: (PPCbctrl_SVR4) - Complexity = 3
              // Dst: (BCTRL8_ELF:i64)
/*11113*/   0, /*End of Scope*/
          /*SwitchOpcode*/ 8,  TARGET_VAL(ISD::TRAP),// ->11125
/*11117*/   OPC_RecordNode,   // #0 = 'trap' chained node
/*11118*/   OPC_EmitMergeInputChains1_0,
/*11119*/   OPC_MorphNodeTo, TARGET_VAL(PPC::TRAP), 0|OPFL_Chain,
                0/*#VTs*/, 0/*#Ops*/, 
            // Src: (trap) - Complexity = 3
            // Dst: (TRAP)
          /*SwitchOpcode*/ 10,  TARGET_VAL(PPCISD::CR6SET),// ->11138
/*11128*/   OPC_RecordNode,   // #0 = 'PPCcr6set' chained node
/*11129*/   OPC_CaptureGlueInput,
/*11130*/   OPC_EmitMergeInputChains1_0,
/*11131*/   OPC_MorphNodeTo, TARGET_VAL(PPC::CR6SET), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput,
                1/*#VTs*/, MVT::i32, 0/*#Ops*/, 
            // Src: (PPCcr6set) - Complexity = 3
            // Dst: (CR6SET:i32)
          /*SwitchOpcode*/ 10,  TARGET_VAL(PPCISD::CR6UNSET),// ->11151
/*11141*/   OPC_RecordNode,   // #0 = 'PPCcr6unset' chained node
/*11142*/   OPC_CaptureGlueInput,
/*11143*/   OPC_EmitMergeInputChains1_0,
/*11144*/   OPC_MorphNodeTo, TARGET_VAL(PPC::CR6UNSET), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput,
                1/*#VTs*/, MVT::i32, 0/*#Ops*/, 
            // Src: (PPCcr6unset) - Complexity = 3
            // Dst: (CR6UNSET:i32)
          /*SwitchOpcode*/ 29,  TARGET_VAL(PPCISD::MTCTR),// ->11183
/*11154*/   OPC_RecordNode,   // #0 = 'PPCmtctr' chained node
/*11155*/   OPC_CaptureGlueInput,
/*11156*/   OPC_RecordChild1, // #1 = $rS
/*11157*/   OPC_Scope, 11, /*->11170*/ // 2 children in Scope
/*11159*/     OPC_CheckChild1Type, MVT::i32,
/*11161*/     OPC_EmitMergeInputChains1_0,
/*11162*/     OPC_MorphNodeTo, TARGET_VAL(PPC::MTCTR), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput,
                  1/*#VTs*/, MVT::i32, 1/*#Ops*/, 1, 
              // Src: (PPCmtctr GPRC:i32:$rS) - Complexity = 3
              // Dst: (MTCTR:i32 GPRC:i32:$rS)
/*11170*/   /*Scope*/ 11, /*->11182*/
/*11171*/     OPC_CheckChild1Type, MVT::i64,
/*11173*/     OPC_EmitMergeInputChains1_0,
/*11174*/     OPC_MorphNodeTo, TARGET_VAL(PPC::MTCTR8), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput,
                  1/*#VTs*/, MVT::i64, 1/*#Ops*/, 1, 
              // Src: (PPCmtctr G8RC:i64:$rS) - Complexity = 3
              // Dst: (MTCTR8:i64 G8RC:i64:$rS)
/*11182*/   0, /*End of Scope*/
          /*SwitchOpcode*/ 15,  TARGET_VAL(PPCISD::VPERM),// ->11201
/*11186*/   OPC_RecordChild0, // #0 = $vA
/*11187*/   OPC_RecordChild1, // #1 = $vB
/*11188*/   OPC_RecordChild2, // #2 = $vC
/*11189*/   OPC_CheckType, MVT::v16i8,
/*11191*/   OPC_MorphNodeTo, TARGET_VAL(PPC::VPERM), 0,
                1/*#VTs*/, MVT::v16i8, 3/*#Ops*/, 0, 1, 2, 
            // Src: (PPCvperm:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB, VRRC:v16i8:$vC) - Complexity = 3
            // Dst: (VPERM:v16i8 VRRC:v16i8:$vA, VRRC:v16i8:$vB, VRRC:v16i8:$vC)
          /*SwitchOpcode*/ 13,  TARGET_VAL(ISD::FP_TO_SINT),// ->11217
/*11204*/   OPC_RecordChild0, // #0 = $vA
/*11205*/   OPC_CheckChild0Type, MVT::v4f32,
/*11207*/   OPC_CheckType, MVT::v4i32,
/*11209*/   OPC_MorphNodeTo, TARGET_VAL(PPC::VCTSXS_0), 0,
                1/*#VTs*/, MVT::v4i32, 1/*#Ops*/, 0, 
            // Src: (fp_to_sint:v4i32 VRRC:v4f32:$vA) - Complexity = 3
            // Dst: (VCTSXS_0:v4i32 VRRC:v4f32:$vA)
          /*SwitchOpcode*/ 13,  TARGET_VAL(ISD::FP_TO_UINT),// ->11233
/*11220*/   OPC_RecordChild0, // #0 = $vA
/*11221*/   OPC_CheckChild0Type, MVT::v4f32,
/*11223*/   OPC_CheckType, MVT::v4i32,
/*11225*/   OPC_MorphNodeTo, TARGET_VAL(PPC::VCTUXS_0), 0,
                1/*#VTs*/, MVT::v4i32, 1/*#Ops*/, 0, 
            // Src: (fp_to_uint:v4i32 VRRC:v4f32:$vA) - Complexity = 3
            // Dst: (VCTUXS_0:v4i32 VRRC:v4f32:$vA)
          /*SwitchOpcode*/ 15,  TARGET_VAL(PPCISD::VMADDFP),// ->11251
/*11236*/   OPC_RecordChild0, // #0 = $A
/*11237*/   OPC_RecordChild1, // #1 = $B
/*11238*/   OPC_RecordChild2, // #2 = $C
/*11239*/   OPC_CheckType, MVT::v4f32,
/*11241*/   OPC_MorphNodeTo, TARGET_VAL(PPC::VMADDFP), 0,
                1/*#VTs*/, MVT::v4f32, 3/*#Ops*/, 0, 1, 2, 
            // Src: (PPCvmaddfp:v4f32 VRRC:v4f32:$A, VRRC:v4f32:$B, VRRC:v4f32:$C) - Complexity = 3
            // Dst: (VMADDFP:v4f32 VRRC:v4f32:$A, VRRC:v4f32:$B, VRRC:v4f32:$C)
          /*SwitchOpcode*/ 15,  TARGET_VAL(PPCISD::VNMSUBFP),// ->11269
/*11254*/   OPC_RecordChild0, // #0 = $A
/*11255*/   OPC_RecordChild1, // #1 = $B
/*11256*/   OPC_RecordChild2, // #2 = $C
/*11257*/   OPC_CheckType, MVT::v4f32,
/*11259*/   OPC_MorphNodeTo, TARGET_VAL(PPC::VNMSUBFP), 0,
                1/*#VTs*/, MVT::v4f32, 3/*#Ops*/, 0, 1, 2, 
            // Src: (PPCvnmsubfp:v4f32 VRRC:v4f32:$A, VRRC:v4f32:$B, VRRC:v4f32:$C) - Complexity = 3
            // Dst: (VNMSUBFP:v4f32 VRRC:v4f32:$A, VRRC:v4f32:$B, VRRC:v4f32:$C)
          /*SwitchOpcode*/ 13,  TARGET_VAL(ISD::SINT_TO_FP),// ->11285
/*11272*/   OPC_RecordChild0, // #0 = $vA
/*11273*/   OPC_CheckChild0Type, MVT::v4i32,
/*11275*/   OPC_CheckType, MVT::v4f32,
/*11277*/   OPC_MorphNodeTo, TARGET_VAL(PPC::VCFSX_0), 0,
                1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
            // Src: (sint_to_fp:v4f32 VRRC:v4i32:$vA) - Complexity = 3
            // Dst: (VCFSX_0:v4f32 VRRC:v4i32:$vA)
          /*SwitchOpcode*/ 13,  TARGET_VAL(ISD::UINT_TO_FP),// ->11301
/*11288*/   OPC_RecordChild0, // #0 = $vA
/*11289*/   OPC_CheckChild0Type, MVT::v4i32,
/*11291*/   OPC_CheckType, MVT::v4f32,
/*11293*/   OPC_MorphNodeTo, TARGET_VAL(PPC::VCFUX_0), 0,
                1/*#VTs*/, MVT::v4f32, 1/*#Ops*/, 0, 
            // Src: (uint_to_fp:v4f32 VRRC:v4i32:$vA) - Complexity = 3
            // Dst: (VCFUX_0:v4f32 VRRC:v4i32:$vA)
          /*SwitchOpcode*/ 7,  TARGET_VAL(PPCISD::NOP),// ->11311
/*11304*/   OPC_CaptureGlueInput,
/*11305*/   OPC_MorphNodeTo, TARGET_VAL(PPC::NOP), 0|OPFL_GlueInput|OPFL_GlueOutput,
                0/*#VTs*/, 0/*#Ops*/, 
            // Src: (PPCnop) - Complexity = 3
            // Dst: (NOP)
          /*SwitchOpcode*/ 13,  TARGET_VAL(PPCISD::LOAD_TOC),// ->11327
/*11314*/   OPC_RecordNode,   // #0 = 'PPCload_toc' chained node
/*11315*/   OPC_CaptureGlueInput,
/*11316*/   OPC_RecordChild1, // #1 = $reg
/*11317*/   OPC_CheckChild1Type, MVT::i64,
/*11319*/   OPC_EmitMergeInputChains1_0,
/*11320*/   OPC_MorphNodeTo, TARGET_VAL(PPC::LDinto_toc), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput,
                0/*#VTs*/, 1/*#Ops*/, 1, 
            // Src: (PPCload_toc G8RC:i64:$reg) - Complexity = 3
            // Dst: (LDinto_toc G8RC:i64:$reg)
          /*SwitchOpcode*/ 9,  TARGET_VAL(PPCISD::TOC_RESTORE),// ->11339
/*11330*/   OPC_RecordNode,   // #0 = 'PPCtoc_restore' chained node
/*11331*/   OPC_CaptureGlueInput,
/*11332*/   OPC_EmitMergeInputChains1_0,
/*11333*/   OPC_MorphNodeTo, TARGET_VAL(PPC::LDtoc_restore), 0|OPFL_Chain|OPFL_GlueInput|OPFL_GlueOutput,
                0/*#VTs*/, 0/*#Ops*/, 
            // Src: (PPCtoc_restore) - Complexity = 3
            // Dst: (LDtoc_restore)
          0, // EndSwitchOpcode
    0
  }; // Total Array size is 11341 bytes

  // Opcode Histogram:
  // #OPC_Scope                          = 115
  // #OPC_RecordNode                     = 44
  // #OPC_RecordChild                    = 479
  // #OPC_RecordMemRef                   = 11
  // #OPC_CaptureGlueInput               = 21
  // #OPC_MoveChild                      = 140
  // #OPC_MoveParent                     = 367
  // #OPC_CheckSame                      = 0
  // #OPC_CheckPatternPredicate          = 4
  // #OPC_CheckPredicate                 = 189
  // #OPC_CheckOpcode                    = 81
  // #OPC_SwitchOpcode                   = 15
  // #OPC_CheckType                      = 158
  // #OPC_SwitchType                     = 91
  // #OPC_CheckChildType                 = 54
  // #OPC_CheckInteger                   = 199
  // #OPC_CheckCondCode                  = 0
  // #OPC_CheckValueType                 = 7
  // #OPC_CheckComplexPat                = 150
  // #OPC_CheckAndImm                    = 0
  // #OPC_CheckOrImm                     = 0
  // #OPC_CheckFoldableChainNode         = 0
  // #OPC_EmitInteger                    = 26
  // #OPC_EmitStringInteger              = 6
  // #OPC_EmitRegister                   = 1
  // #OPC_EmitConvertToTarget            = 79
  // #OPC_EmitMergeInputChains           = 202
  // #OPC_EmitCopyToReg                  = 0
  // #OPC_EmitNode                       = 10
  // #OPC_EmitNodeXForm                  = 38
  // #OPC_MarkGlueResults                = 0
  // #OPC_CompleteMatch                  = 12
  // #OPC_MorphNodeTo                    = 600

  #undef TARGET_VAL
  return SelectCodeCommon(N, MatcherTable,sizeof(MatcherTable));
}

virtual bool CheckPatternPredicate(unsigned PredNo) const {
  switch (PredNo) {
  default: llvm_unreachable("Invalid predicate in table?");
  case 0: return (!PPCSubTarget.isPPC64());
  case 1: return (PPCSubTarget.isPPC64());
  }
}

virtual bool CheckNodePredicate(SDNode *Node,
                                unsigned PredNo) const {
  switch (PredNo) {
  default: llvm_unreachable("Invalid predicate in table?");
  case 0: { // Predicate_immSExt16
    ConstantSDNode*N = cast<ConstantSDNode>(Node);

  // immSExt16 predicate - True if the immediate fits in a 16-bit sign extended
  // field.  Used by instructions like 'addi'.
  if (N->getValueType(0) == MVT::i32)
    return (int32_t)N->getZExtValue() == (short)N->getZExtValue();
  else
    return (int64_t)N->getZExtValue() == (short)N->getZExtValue();

  }
  case 1: { // Predicate_imm16ShiftedSExt
    ConstantSDNode*N = cast<ConstantSDNode>(Node);

  // imm16ShiftedSExt predicate - True if only bits in the top 16-bits of the
  // immediate are set.  Used by instructions like 'addis'.  Identical to 
  // imm16ShiftedZExt in 32-bit mode.
  if (N->getZExtValue() & 0xFFFF) return false;
  if (N->getValueType(0) == MVT::i32)
    return true;
  // For 64-bit, make sure it is sext right.
  return N->getZExtValue() == (uint64_t)(int)N->getZExtValue();

  }
  case 2: { // Predicate_unindexedload
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getAddressingMode() == ISD::UNINDEXED;

  }
  case 3: { // Predicate_zextload
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getExtensionType() == ISD::ZEXTLOAD;

  }
  case 4: { // Predicate_zextloadi8
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i8;

  }
  case 5: { // Predicate_sextload
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getExtensionType() == ISD::SEXTLOAD;

  }
  case 6: { // Predicate_sextloadi16
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i16;

  }
  case 7: { // Predicate_zextloadi16
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i16;

  }
  case 8: { // Predicate_load
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getExtensionType() == ISD::NON_EXTLOAD;

  }
  case 9: { // Predicate_zextloadi1
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i1;

  }
  case 10: { // Predicate_extload
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getExtensionType() == ISD::EXTLOAD;

  }
  case 11: { // Predicate_extloadi1
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i1;

  }
  case 12: { // Predicate_extloadi8
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i8;

  }
  case 13: { // Predicate_extloadi16
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i16;

  }
  case 14: { // Predicate_sextloadi32
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i32;

  }
  case 15: { // Predicate_zextloadi32
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i32;

  }
  case 16: { // Predicate_extloadi32
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::i32;

  }
  case 17: { // Predicate_extloadf32
    SDNode *N = Node;

  return cast<LoadSDNode>(N)->getMemoryVT() == MVT::f32;

  }
  case 18: { // Predicate_unindexedstore
    SDNode *N = Node;

  return cast<StoreSDNode>(N)->getAddressingMode() == ISD::UNINDEXED;

  }
  case 19: { // Predicate_truncstore
    SDNode *N = Node;

  return cast<StoreSDNode>(N)->isTruncatingStore();

  }
  case 20: { // Predicate_truncstorei8
    SDNode *N = Node;

  return cast<StoreSDNode>(N)->getMemoryVT() == MVT::i8;

  }
  case 21: { // Predicate_truncstorei16
    SDNode *N = Node;

  return cast<StoreSDNode>(N)->getMemoryVT() == MVT::i16;

  }
  case 22: { // Predicate_store
    SDNode *N = Node;

  return !cast<StoreSDNode>(N)->isTruncatingStore();

  }
  case 23: { // Predicate_itruncstore
    SDNode *N = Node;

  return cast<StoreSDNode>(N)->isTruncatingStore();

  }
  case 24: { // Predicate_pre_truncst
    SDNode *N = Node;

  ISD::MemIndexedMode AM = cast<StoreSDNode>(N)->getAddressingMode();
  return AM == ISD::PRE_INC || AM == ISD::PRE_DEC;

  }
  case 25: { // Predicate_pre_truncsti8
    SDNode *N = Node;

  return cast<StoreSDNode>(N)->getMemoryVT() == MVT::i8;

  }
  case 26: { // Predicate_pre_truncsti16
    SDNode *N = Node;

  return cast<StoreSDNode>(N)->getMemoryVT() == MVT::i16;

  }
  case 27: { // Predicate_istore
    SDNode *N = Node;

  return !cast<StoreSDNode>(N)->isTruncatingStore();

  }
  case 28: { // Predicate_pre_store
    SDNode *N = Node;

  ISD::MemIndexedMode AM = cast<StoreSDNode>(N)->getAddressingMode();
  return AM == ISD::PRE_INC || AM == ISD::PRE_DEC;

  }
  case 29: { // Predicate_truncstorei32
    SDNode *N = Node;

  return cast<StoreSDNode>(N)->getMemoryVT() == MVT::i32;

  }
  case 30: { // Predicate_pre_truncsti32
    SDNode *N = Node;

  return cast<StoreSDNode>(N)->getMemoryVT() == MVT::i32;

  }
  case 31: { // Predicate_atomic_load_add_8
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i8;
  
  }
  case 32: { // Predicate_atomic_load_add_16
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i16;
  
  }
  case 33: { // Predicate_atomic_load_add_32
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i32;
  
  }
  case 34: { // Predicate_atomic_load_add_64
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i64;
  
  }
  case 35: { // Predicate_atomic_load_sub_8
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i8;
  
  }
  case 36: { // Predicate_atomic_load_sub_16
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i16;
  
  }
  case 37: { // Predicate_atomic_load_sub_32
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i32;
  
  }
  case 38: { // Predicate_atomic_load_sub_64
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i64;
  
  }
  case 39: { // Predicate_atomic_load_and_8
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i8;
  
  }
  case 40: { // Predicate_atomic_load_and_16
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i16;
  
  }
  case 41: { // Predicate_atomic_load_and_32
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i32;
  
  }
  case 42: { // Predicate_atomic_load_and_64
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i64;
  
  }
  case 43: { // Predicate_atomic_load_or_8
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i8;
  
  }
  case 44: { // Predicate_atomic_load_or_16
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i16;
  
  }
  case 45: { // Predicate_atomic_load_or_32
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i32;
  
  }
  case 46: { // Predicate_atomic_load_or_64
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i64;
  
  }
  case 47: { // Predicate_atomic_load_xor_8
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i8;
  
  }
  case 48: { // Predicate_atomic_load_xor_16
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i16;
  
  }
  case 49: { // Predicate_atomic_load_xor_32
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i32;
  
  }
  case 50: { // Predicate_atomic_load_xor_64
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i64;
  
  }
  case 51: { // Predicate_atomic_load_nand_8
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i8;
  
  }
  case 52: { // Predicate_atomic_load_nand_16
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i16;
  
  }
  case 53: { // Predicate_atomic_load_nand_32
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i32;
  
  }
  case 54: { // Predicate_atomic_load_nand_64
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i64;
  
  }
  case 55: { // Predicate_atomic_cmp_swap_8
    SDNode *N = Node;

  return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i8;

  }
  case 56: { // Predicate_atomic_cmp_swap_16
    SDNode *N = Node;

  return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i16;

  }
  case 57: { // Predicate_atomic_cmp_swap_32
    SDNode *N = Node;

  return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i32;

  }
  case 58: { // Predicate_atomic_cmp_swap_64
    SDNode *N = Node;

  return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i64;

  }
  case 59: { // Predicate_atomic_swap_8
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i8;
  
  }
  case 60: { // Predicate_atomic_swap_16
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i16;
  
  }
  case 61: { // Predicate_atomic_swap_32
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i32;
  
  }
  case 62: { // Predicate_atomic_swap_64
    SDNode *N = Node;

    return cast<AtomicSDNode>(N)->getMemoryVT() == MVT::i64;
  
  }
  case 63: { // Predicate_immAllOnesV
    SDNode *N = Node;

  return ISD::isBuildVectorAllOnes(N);

  }
  case 64: { // Predicate_immZExt16
    ConstantSDNode*N = cast<ConstantSDNode>(Node);

  // immZExt16 predicate - True if the immediate fits in a 16-bit zero extended
  // field.  Used by instructions like 'ori'.
  return (uint64_t)N->getZExtValue() == (unsigned short)N->getZExtValue();

  }
  case 65: { // Predicate_imm16ShiftedZExt
    ConstantSDNode*N = cast<ConstantSDNode>(Node);

  // imm16ShiftedZExt predicate - True if only bits in the top 16-bits of the
  // immediate are set.  Used by instructions like 'xoris'.
  return (N->getZExtValue() & ~uint64_t(0xFFFF0000)) == 0;

  }
  case 66: { // Predicate_maskimm32
    ConstantSDNode*N = cast<ConstantSDNode>(Node);

  // maskImm predicate - True if immediate is a run of ones.
  unsigned mb, me;
  if (N->getValueType(0) == MVT::i32)
    return isRunOfOnes((unsigned)N->getZExtValue(), mb, me);
  else
    return false;

  }
  case 67: { // Predicate_vspltb_shuffle
    SDNode *N = Node;

  return PPC::isSplatShuffleMask(cast<ShuffleVectorSDNode>(N), 1);

  }
  case 68: { // Predicate_vsplth_shuffle
    SDNode *N = Node;

  return PPC::isSplatShuffleMask(cast<ShuffleVectorSDNode>(N), 2);

  }
  case 69: { // Predicate_vspltw_shuffle
    SDNode *N = Node;

  return PPC::isSplatShuffleMask(cast<ShuffleVectorSDNode>(N), 4);

  }
  case 70: { // Predicate_vsldoi_unary_shuffle
    SDNode *N = Node;

  return PPC::isVSLDOIShuffleMask(N, true) != -1;

  }
  case 71: { // Predicate_vpkuwum_unary_shuffle
    SDNode *N = Node;

  return PPC::isVPKUWUMShuffleMask(cast<ShuffleVectorSDNode>(N), true);

  }
  case 72: { // Predicate_vpkuhum_unary_shuffle
    SDNode *N = Node;

  return PPC::isVPKUHUMShuffleMask(cast<ShuffleVectorSDNode>(N), true);

  }
  case 73: { // Predicate_vmrglb_unary_shuffle
    SDNode *N = Node;

  return PPC::isVMRGLShuffleMask(cast<ShuffleVectorSDNode>(N), 1, true);

  }
  case 74: { // Predicate_vmrglh_unary_shuffle
    SDNode *N = Node;

  return PPC::isVMRGLShuffleMask(cast<ShuffleVectorSDNode>(N), 2, true);

  }
  case 75: { // Predicate_vmrglw_unary_shuffle
    SDNode *N = Node;

  return PPC::isVMRGLShuffleMask(cast<ShuffleVectorSDNode>(N), 4, true);

  }
  case 76: { // Predicate_vmrghb_unary_shuffle
    SDNode *N = Node;

  return PPC::isVMRGHShuffleMask(cast<ShuffleVectorSDNode>(N), 1, true);

  }
  case 77: { // Predicate_vmrghh_unary_shuffle
    SDNode *N = Node;

  return PPC::isVMRGHShuffleMask(cast<ShuffleVectorSDNode>(N), 2, true);

  }
  case 78: { // Predicate_vmrghw_unary_shuffle
    SDNode *N = Node;

  return PPC::isVMRGHShuffleMask(cast<ShuffleVectorSDNode>(N), 4, true);

  }
  case 79: { // Predicate_vsldoi_shuffle
    SDNode *N = Node;

  return PPC::isVSLDOIShuffleMask(N, false) != -1;

  }
  case 80: { // Predicate_vmrghb_shuffle
    SDNode *N = Node;

  return PPC::isVMRGHShuffleMask(cast<ShuffleVectorSDNode>(N), 1, false);

  }
  case 81: { // Predicate_vmrghh_shuffle
    SDNode *N = Node;

  return PPC::isVMRGHShuffleMask(cast<ShuffleVectorSDNode>(N), 2, false);

  }
  case 82: { // Predicate_vmrghw_shuffle
    SDNode *N = Node;

  return PPC::isVMRGHShuffleMask(cast<ShuffleVectorSDNode>(N), 4, false);

  }
  case 83: { // Predicate_vmrglb_shuffle
    SDNode *N = Node;

  return PPC::isVMRGLShuffleMask(cast<ShuffleVectorSDNode>(N), 1, false);

  }
  case 84: { // Predicate_vmrglh_shuffle
    SDNode *N = Node;

  return PPC::isVMRGLShuffleMask(cast<ShuffleVectorSDNode>(N), 2, false);

  }
  case 85: { // Predicate_vmrglw_shuffle
    SDNode *N = Node;

  return PPC::isVMRGLShuffleMask(cast<ShuffleVectorSDNode>(N), 4, false);

  }
  case 86: { // Predicate_vpkuhum_shuffle
    SDNode *N = Node;

  return PPC::isVPKUHUMShuffleMask(cast<ShuffleVectorSDNode>(N), false);

  }
  case 87: { // Predicate_vpkuwum_shuffle
    SDNode *N = Node;

  return PPC::isVPKUWUMShuffleMask(cast<ShuffleVectorSDNode>(N), false);

  }
  case 88: { // Predicate_vecspltisb
    SDNode *N = Node;

  return PPC::get_VSPLTI_elt(N, 1, *CurDAG).getNode() != 0;

  }
  case 89: { // Predicate_vecspltish
    SDNode *N = Node;

  return PPC::get_VSPLTI_elt(N, 2, *CurDAG).getNode() != 0;

  }
  case 90: { // Predicate_vecspltisw
    SDNode *N = Node;

  return PPC::get_VSPLTI_elt(N, 4, *CurDAG).getNode() != 0;

  }
  case 91: { // Predicate_immAllZerosV
    SDNode *N = Node;

  return ISD::isBuildVectorAllZeros(N);

  }
  }
}

virtual bool CheckComplexPattern(SDNode *Root, SDNode *Parent,
                                 SDValue N, unsigned PatternNo,
         SmallVectorImpl<std::pair<SDValue, SDNode*> > &Result) {
  unsigned NextRes = Result.size();
  switch (PatternNo) {
  default: llvm_unreachable("Invalid pattern # in table?");
  case 0:
    Result.resize(NextRes+2);
    return SelectAddrIdxOnly(N, Result[NextRes+0].first, Result[NextRes+1].first);
  case 1:
    Result.resize(NextRes+2);
    return SelectAddrImm(N, Result[NextRes+0].first, Result[NextRes+1].first);
  case 2:
    Result.resize(NextRes+2);
    return SelectAddrIdx(N, Result[NextRes+0].first, Result[NextRes+1].first);
  case 3:
    Result.resize(NextRes+2);
    return SelectAddrImmShift(N, Result[NextRes+0].first, Result[NextRes+1].first);
  case 4:
    Result.resize(NextRes+1);
    return SelectAddrImmOffs(N, Result[NextRes+0].first);
  case 5:
    Result.resize(NextRes+1);
    return SelectAddrIdxOffs(N, Result[NextRes+0].first);
  }
}

virtual SDValue RunSDNodeXForm(SDValue V, unsigned XFormNo) {
  switch (XFormNo) {
  default: llvm_unreachable("Invalid xform # in table?");
  case 0: {  // HI16
    ConstantSDNode *N = cast<ConstantSDNode>(V.getNode());

  // Transformation function: shift the immediate value down into the low bits.
  return getI32Imm((unsigned)N->getZExtValue() >> 16);

  }
  case 1: {  // LO16
    ConstantSDNode *N = cast<ConstantSDNode>(V.getNode());

  // Transformation function: get the low 16 bits.
  return getI32Imm((unsigned short)N->getZExtValue());

  }
  case 2: {  // HA16
    ConstantSDNode *N = cast<ConstantSDNode>(V.getNode());

  // Transformation function: shift the immediate value down into the low bits.
  signed int Val = N->getZExtValue();
  return getI32Imm((Val - (signed short)Val) >> 16);

  }
  case 3: {  // MB
    ConstantSDNode *N = cast<ConstantSDNode>(V.getNode());

  // Transformation function: get the start bit of a mask
  unsigned mb = 0, me;
  (void)isRunOfOnes((unsigned)N->getZExtValue(), mb, me);
  return getI32Imm(mb);

  }
  case 4: {  // ME
    ConstantSDNode *N = cast<ConstantSDNode>(V.getNode());

  // Transformation function: get the end bit of a mask
  unsigned mb, me = 0;
  (void)isRunOfOnes((unsigned)N->getZExtValue(), mb, me);
  return getI32Imm(me);

  }
  case 5: {  // SHL32
    ConstantSDNode *N = cast<ConstantSDNode>(V.getNode());

  // Transformation function: 31 - imm
  return getI32Imm(31 - N->getZExtValue());

  }
  case 6: {  // SHL64
    ConstantSDNode *N = cast<ConstantSDNode>(V.getNode());

  // Transformation function: 63 - imm
  return getI32Imm(63 - N->getZExtValue());

  }
  case 7: {  // SRL32
    ConstantSDNode *N = cast<ConstantSDNode>(V.getNode());

  // Transformation function: 32 - imm
  return N->getZExtValue() ? getI32Imm(32 - N->getZExtValue()) : getI32Imm(0);

  }
  case 8: {  // SRL64
    ConstantSDNode *N = cast<ConstantSDNode>(V.getNode());

  // Transformation function: 64 - imm
  return N->getZExtValue() ? getI32Imm(64 - N->getZExtValue()) : getI32Imm(0);

  }
  case 9: {  // VSPLTB_get_imm
    SDNode *N = V.getNode();

  return getI32Imm(PPC::getVSPLTImmediate(N, 1));

  }
  case 10: {  // VSPLTH_get_imm
    SDNode *N = V.getNode();

  return getI32Imm(PPC::getVSPLTImmediate(N, 2));

  }
  case 11: {  // VSPLTW_get_imm
    SDNode *N = V.getNode();

  return getI32Imm(PPC::getVSPLTImmediate(N, 4));

  }
  case 12: {  // VSLDOI_unary_get_imm
    SDNode *N = V.getNode();

  return getI32Imm(PPC::isVSLDOIShuffleMask(N, true));

  }
  case 13: {  // VSLDOI_get_imm
    SDNode *N = V.getNode();

  return getI32Imm(PPC::isVSLDOIShuffleMask(N, false));

  }
  case 14: {  // VSPLTISB_get_imm
    SDNode *N = V.getNode();

  return PPC::get_VSPLTI_elt(N, 1, *CurDAG);

  }
  case 15: {  // VSPLTISH_get_imm
    SDNode *N = V.getNode();

  return PPC::get_VSPLTI_elt(N, 2, *CurDAG);

  }
  case 16: {  // VSPLTISW_get_imm
    SDNode *N = V.getNode();

  return PPC::get_VSPLTI_elt(N, 4, *CurDAG);

  }
  }
}

