vs_1_1
dcl_position v0
dcl_color v1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; c0 is FINAL_RADIUS            ;;
;; c1 is t                       ;;
;; c2 - c5 is matrix             ;;
;; c111 is 1.0f                  ;;
;; c112 is -1.0f                 ;;
;;                               ;;
;; r0.x is 1/current radius      ;;
;; r1.x is a quotient            ;;
;; r2 is a vertex after morphing ;;
;; r3 is 1.0f in non-const mem   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

def c111, 1.0, 1.0, 1.0, 1.0 ;constant one

dp3 r0, v0, v0
rsq r0, r0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  r1.x = 1+t*((FINAL_RADIUS/r0) -1)   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

mov r3, c111
mad r1, r0, c0, -r3
mad r1, r1, c1, r3

mul r2.xyz, v0.xyz, r1.x
mov r2.w, c111.w

m4x4 oPos, r2, c2
mov oD0, v1
