;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::LinktrackAoaNode0)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'LinktrackAoaNode0 (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::LINKTRACKAOANODE0")
  (make-package "NLINK_PARSER::LINKTRACKAOANODE0"))

(in-package "ROS")
;;//! \htmlinclude LinktrackAoaNode0.msg.html


(defclass nlink_parser::LinktrackAoaNode0
  :super ros::object
  :slots (_role _id _dis _angle _fp_rssi _rx_rssi ))

(defmethod nlink_parser::LinktrackAoaNode0
  (:init
   (&key
    ((:role __role) 0)
    ((:id __id) 0)
    ((:dis __dis) 0.0)
    ((:angle __angle) 0.0)
    ((:fp_rssi __fp_rssi) 0.0)
    ((:rx_rssi __rx_rssi) 0.0)
    )
   (send-super :init)
   (setq _role (round __role))
   (setq _id (round __id))
   (setq _dis (float __dis))
   (setq _angle (float __angle))
   (setq _fp_rssi (float __fp_rssi))
   (setq _rx_rssi (float __rx_rssi))
   self)
  (:role
   (&optional __role)
   (if __role (setq _role __role)) _role)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:dis
   (&optional __dis)
   (if __dis (setq _dis __dis)) _dis)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:fp_rssi
   (&optional __fp_rssi)
   (if __fp_rssi (setq _fp_rssi __fp_rssi)) _fp_rssi)
  (:rx_rssi
   (&optional __rx_rssi)
   (if __rx_rssi (setq _rx_rssi __rx_rssi)) _rx_rssi)
  (:serialization-length
   ()
   (+
    ;; uint8 _role
    1
    ;; uint8 _id
    1
    ;; float32 _dis
    4
    ;; float32 _angle
    4
    ;; float32 _fp_rssi
    4
    ;; float32 _rx_rssi
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _role
       (write-byte _role s)
     ;; uint8 _id
       (write-byte _id s)
     ;; float32 _dis
       (sys::poke _dis (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _angle
       (sys::poke _angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _fp_rssi
       (sys::poke _fp_rssi (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rx_rssi
       (sys::poke _rx_rssi (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _role
     (setq _role (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _dis
     (setq _dis (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _angle
     (setq _angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _fp_rssi
     (setq _fp_rssi (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rx_rssi
     (setq _rx_rssi (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get nlink_parser::LinktrackAoaNode0 :md5sum-) "14ecc209e569ea4b0a93a8b73bd0cd13")
(setf (get nlink_parser::LinktrackAoaNode0 :datatype-) "nlink_parser/LinktrackAoaNode0")
(setf (get nlink_parser::LinktrackAoaNode0 :definition-)
      "uint8 role
uint8 id
float32 dis
float32 angle
float32 fp_rssi
float32 rx_rssi

")



(provide :nlink_parser/LinktrackAoaNode0 "14ecc209e569ea4b0a93a8b73bd0cd13")


