;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::LinktrackNode0)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'LinktrackNode0 (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::LINKTRACKNODE0")
  (make-package "NLINK_PARSER::LINKTRACKNODE0"))

(in-package "ROS")
;;//! \htmlinclude LinktrackNode0.msg.html


(defclass nlink_parser::LinktrackNode0
  :super ros::object
  :slots (_role _id _data ))

(defmethod nlink_parser::LinktrackNode0
  (:init
   (&key
    ((:role __role) 0)
    ((:id __id) 0)
    ((:data __data) (make-array 0 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _role (round __role))
   (setq _id (round __id))
   (setq _data __data)
   self)
  (:role
   (&optional __role)
   (if __role (setq _role __role)) _role)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; uint8 _role
    1
    ;; uint8 _id
    1
    ;; uint8[] _data
    (* 1    (length _data)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _role
       (write-byte _role s)
     ;; uint8 _id
       (write-byte _id s)
     ;; uint8[] _data
     (write-long (length _data) s)
     (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _role
     (setq _role (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8[] _data
   (let ((n (sys::peek buf ptr- :integer))) (incf ptr- 4)
     (setq _data (make-array n :element-type :char))
     (replace _data buf :start2 ptr-) (incf ptr- n))
   ;;
   self)
  )

(setf (get nlink_parser::LinktrackNode0 :md5sum-) "039fd4e4d2076d4b4621aa4a72ea3366")
(setf (get nlink_parser::LinktrackNode0 :datatype-) "nlink_parser/LinktrackNode0")
(setf (get nlink_parser::LinktrackNode0 :definition-)
      "uint8 role
uint8 id
uint8[] data

")



(provide :nlink_parser/LinktrackNode0 "039fd4e4d2076d4b4621aa4a72ea3366")


