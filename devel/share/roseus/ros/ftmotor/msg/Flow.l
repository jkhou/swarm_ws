;; Auto-generated. Do not edit!


(when (boundp 'ftmotor::Flow)
  (if (not (find-package "FTMOTOR"))
    (make-package "FTMOTOR"))
  (shadow 'Flow (find-package "FTMOTOR")))
(unless (find-package "FTMOTOR::FLOW")
  (make-package "FTMOTOR::FLOW"))

(in-package "ROS")
;;//! \htmlinclude Flow.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass ftmotor::Flow
  :super ros::object
  :slots (_header _vx _vy _pos _theta _hight _valid _quality ))

(defmethod ftmotor::Flow
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:vx __vx) 0.0)
    ((:vy __vy) 0.0)
    ((:pos __pos) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:theta __theta) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:hight __hight) 0.0)
    ((:valid __valid) 0)
    ((:quality __quality) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _vx (float __vx))
   (setq _vy (float __vy))
   (setq _pos __pos)
   (setq _theta __theta)
   (setq _hight (float __hight))
   (setq _valid (round __valid))
   (setq _quality (round __quality))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:vx
   (&optional __vx)
   (if __vx (setq _vx __vx)) _vx)
  (:vy
   (&optional __vy)
   (if __vy (setq _vy __vy)) _vy)
  (:pos
   (&optional __pos)
   (if __pos (setq _pos __pos)) _pos)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:hight
   (&optional __hight)
   (if __hight (setq _hight __hight)) _hight)
  (:valid
   (&optional __valid)
   (if __valid (setq _valid __valid)) _valid)
  (:quality
   (&optional __quality)
   (if __quality (setq _quality __quality)) _quality)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _vx
    4
    ;; float32 _vy
    4
    ;; float32[3] _pos
    (* 4    3)
    ;; float32[3] _theta
    (* 4    3)
    ;; float32 _hight
    4
    ;; uint8 _valid
    1
    ;; uint8 _quality
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _vx
       (sys::poke _vx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy
       (sys::poke _vy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32[3] _pos
     (dotimes (i 3)
       (sys::poke (elt _pos i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _theta
     (dotimes (i 3)
       (sys::poke (elt _theta i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32 _hight
       (sys::poke _hight (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _valid
       (write-byte _valid s)
     ;; uint8 _quality
       (write-byte _quality s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _vx
     (setq _vx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy
     (setq _vy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32[3] _pos
   (dotimes (i (length _pos))
     (setf (elt _pos i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _theta
   (dotimes (i (length _theta))
     (setf (elt _theta i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32 _hight
     (setq _hight (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _valid
     (setq _valid (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _quality
     (setq _quality (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get ftmotor::Flow :md5sum-) "25d2bfe030c1d5b1bb0b07b36bea3b01")
(setf (get ftmotor::Flow :datatype-) "ftmotor/Flow")
(setf (get ftmotor::Flow :definition-)
      "Header header
float32 vx
float32 vy
float32[3] pos
float32[3] theta
float32 hight
uint8 valid
uint8 quality
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :ftmotor/Flow "25d2bfe030c1d5b1bb0b07b36bea3b01")


