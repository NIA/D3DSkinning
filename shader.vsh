vs_1_1
dcl_position v0
dcl_color v1
dcl_texcoord v2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; c0 - c1 is view matrix        ;;
;;                               ;;
;; r0 is `skinned' vertex        ;;
;; r1 is transformed vertex      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

mov r0, v0
mul r0.x, r0.x, v2.x
m4x4 r1, r0, c0
mov oPos, r1
mov oD0, v1
