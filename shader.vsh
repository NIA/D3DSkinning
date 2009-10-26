vs_1_1
dcl_position v0
dcl_color v1
dcl_texcoord v2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; c0 - c3 is view matrix        ;;
;; c4 - c7 is 1st bone matrix    ;;
;; c8 - c11 is 2nd bone matrix   ;;
;;                               ;;
;; r0 is vertex after 1st bone   ;;
;; r1 is vertex after 2nd bone   ;;
;; r2 is transformed vertex      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

m4x4 r0, v0, c4
mul r0.xyz, r0.xyz, v2.x
m4x4 r1, v0, c8
mad r1.xyz, r1.xyz, v2.y, r0.xyz

m4x4 oPos, r1, c0
mov oD0, v1
