;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::TofsenseFrame0)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'TofsenseFrame0 (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::TOFSENSEFRAME0")
  (make-package "NLINK_PARSER::TOFSENSEFRAME0"))

(in-package "ROS")
;;//! \htmlinclude TofsenseFrame0.msg.html


(defclass nlink_parser::TofsenseFrame0
  :super ros::object
  :slots (_id _system_time _dis _dis_status _signal_strength ))

(defmethod nlink_parser::TofsenseFrame0
  (:init
   (&key
    ((:id __id) 0)
    ((:system_time __system_time) 0)
    ((:dis __dis) 0.0)
    ((:dis_status __dis_status) 0)
    ((:signal_strength __signal_strength) 0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _system_time (round __system_time))
   (setq _dis (float __dis))
   (setq _dis_status (round __dis_status))
   (setq _signal_strength (round __signal_strength))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:system_time
   (&optional __system_time)
   (if __system_time (setq _system_time __system_time)) _system_time)
  (:dis
   (&optional __dis)
   (if __dis (setq _dis __dis)) _dis)
  (:dis_status
   (&optional __dis_status)
   (if __dis_status (setq _dis_status __dis_status)) _dis_status)
  (:signal_strength
   (&optional __signal_strength)
   (if __signal_strength (setq _signal_strength __signal_strength)) _signal_strength)
  (:serialization-length
   ()
   (+
    ;; uint8 _id
    1
    ;; uint32 _system_time
    4
    ;; float32 _dis
    4
    ;; uint8 _dis_status
    1
    ;; uint16 _signal_strength
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _id
       (write-byte _id s)
     ;; uint32 _system_time
       (write-long _system_time s)
     ;; float32 _dis
       (sys::poke _dis (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _dis_status
       (write-byte _dis_status s)
     ;; uint16 _signal_strength
       (write-word _signal_strength s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint32 _system_time
     (setq _system_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _dis
     (setq _dis (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _dis_status
     (setq _dis_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint16 _signal_strength
     (setq _signal_strength (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get nlink_parser::TofsenseFrame0 :md5sum-) "f4da8cb7f97b8a39238865249f6b98ed")
(setf (get nlink_parser::TofsenseFrame0 :datatype-) "nlink_parser/TofsenseFrame0")
(setf (get nlink_parser::TofsenseFrame0 :definition-)
      "uint8 id
uint32 system_time
float32 dis
uint8 dis_status
uint16 signal_strength

")



(provide :nlink_parser/TofsenseFrame0 "f4da8cb7f97b8a39238865249f6b98ed")


