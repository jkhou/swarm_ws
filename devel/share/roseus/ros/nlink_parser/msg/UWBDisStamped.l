;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::UWBDisStamped)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'UWBDisStamped (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::UWBDISSTAMPED")
  (make-package "NLINK_PARSER::UWBDISSTAMPED"))

(in-package "ROS")
;;//! \htmlinclude UWBDisStamped.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nlink_parser::UWBDisStamped
  :super ros::object
  :slots (_header _distance ))

(defmethod nlink_parser::UWBDisStamped
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:distance __distance) (make-array 4 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _distance __distance)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64[4] _distance
    (* 8    4)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64[4] _distance
     (dotimes (i 4)
       (sys::poke (elt _distance i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64[4] _distance
   (dotimes (i (length _distance))
     (setf (elt _distance i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;;
   self)
  )

(setf (get nlink_parser::UWBDisStamped :md5sum-) "2e9778231341331f56c760171dbc8c3f")
(setf (get nlink_parser::UWBDisStamped :datatype-) "nlink_parser/UWBDisStamped")
(setf (get nlink_parser::UWBDisStamped :definition-)
      "std_msgs/Header header
float64[4] distance
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



(provide :nlink_parser/UWBDisStamped "2e9778231341331f56c760171dbc8c3f")


