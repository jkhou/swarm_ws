;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::LinktrackNodeframe1)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'LinktrackNodeframe1 (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::LINKTRACKNODEFRAME1")
  (make-package "NLINK_PARSER::LINKTRACKNODEFRAME1"))

(in-package "ROS")
;;//! \htmlinclude LinktrackNodeframe1.msg.html


(defclass nlink_parser::LinktrackNodeframe1
  :super ros::object
  :slots (_role _id _local_time _system_time _voltage _nodes ))

(defmethod nlink_parser::LinktrackNodeframe1
  (:init
   (&key
    ((:role __role) 0)
    ((:id __id) 0)
    ((:local_time __local_time) 0)
    ((:system_time __system_time) 0)
    ((:voltage __voltage) 0.0)
    ((:nodes __nodes) (let (r) (dotimes (i 0) (push (instance nlink_parser::LinktrackNode1 :init) r)) r))
    )
   (send-super :init)
   (setq _role (round __role))
   (setq _id (round __id))
   (setq _local_time (round __local_time))
   (setq _system_time (round __system_time))
   (setq _voltage (float __voltage))
   (setq _nodes __nodes)
   self)
  (:role
   (&optional __role)
   (if __role (setq _role __role)) _role)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:local_time
   (&optional __local_time)
   (if __local_time (setq _local_time __local_time)) _local_time)
  (:system_time
   (&optional __system_time)
   (if __system_time (setq _system_time __system_time)) _system_time)
  (:voltage
   (&optional __voltage)
   (if __voltage (setq _voltage __voltage)) _voltage)
  (:nodes
   (&rest __nodes)
   (if (keywordp (car __nodes))
       (send* _nodes __nodes)
     (progn
       (if __nodes (setq _nodes (car __nodes)))
       _nodes)))
  (:serialization-length
   ()
   (+
    ;; uint8 _role
    1
    ;; uint8 _id
    1
    ;; uint32 _local_time
    4
    ;; uint32 _system_time
    4
    ;; float32 _voltage
    4
    ;; nlink_parser/LinktrackNode1[] _nodes
    (apply #'+ (send-all _nodes :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _role
       (write-byte _role s)
     ;; uint8 _id
       (write-byte _id s)
     ;; uint32 _local_time
       (write-long _local_time s)
     ;; uint32 _system_time
       (write-long _system_time s)
     ;; float32 _voltage
       (sys::poke _voltage (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; nlink_parser/LinktrackNode1[] _nodes
     (write-long (length _nodes) s)
     (dolist (elem _nodes)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _role
     (setq _role (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint32 _local_time
     (setq _local_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _system_time
     (setq _system_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _voltage
     (setq _voltage (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; nlink_parser/LinktrackNode1[] _nodes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _nodes (let (r) (dotimes (i n) (push (instance nlink_parser::LinktrackNode1 :init) r)) r))
     (dolist (elem- _nodes)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get nlink_parser::LinktrackNodeframe1 :md5sum-) "0a522663cdf935548d202960a37f14ce")
(setf (get nlink_parser::LinktrackNodeframe1 :datatype-) "nlink_parser/LinktrackNodeframe1")
(setf (get nlink_parser::LinktrackNodeframe1 :definition-)
      "uint8 role
uint8 id
uint32 local_time
uint32 system_time
float32 voltage
LinktrackNode1[] nodes

================================================================================
MSG: nlink_parser/LinktrackNode1
uint8 role
uint8 id
float32[3] pos_3d

")



(provide :nlink_parser/LinktrackNodeframe1 "0a522663cdf935548d202960a37f14ce")


