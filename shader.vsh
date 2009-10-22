vs_1_1
dcl_position v0
dcl_color v1
dcl_texcoord v2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; c0 - c3 is view matrix        ;;
;; c4 - c7 is 1st bone matrix    ;;
;; c8 - c11 is 2nd bone matrix   ;;
;;                               ;;
;; c111 is 1.0f                  ;;
;;                               ;;
;; r0 is vertex after 1st bone   ;;
;; r1 is vertex after 2nd bone   ;;
;; r2 is transformed vertex      ;;
;;                               ;;
;; r3 is 2nd weight (1st is v2)  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

def c111, 1.0, 1.0, 1.0, 1.0 ;constant one

add r3, -v2, c111

m4x4 r0, v0, c4
mul r0.xyz, r0.xyz, v2.x
m4x4 r1, v0, c8
mul r1.xyz, r1.xyz, r3.x

add r1.xyz, r0.xyz, r1.xyz

m4x4 r2, r1, c0

mov oPos, r2
mov oD0, v1
