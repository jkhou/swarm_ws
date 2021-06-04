;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::TofsenseCascade)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'TofsenseCascade (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::TOFSENSECASCADE")
  (make-package "NLINK_PARSER::TOFSENSECASCADE"))

(in-package "ROS")
;;//! \htmlinclude TofsenseCascade.msg.html


(defclass nlink_parser::TofsenseCascade
  :super ros::object
  :slots (_nodes ))

(defmethod nlink_parser::TofsenseCascade
  (:init
   (&key
    ((:nodes __nodes) (let (r) (dotimes (i 0) (push (instance nlink_parser::TofsenseFrame0 :init) r)) r))
    )
   (send-super :init)
   (setq _nodes __nodes)
   self)
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
    ;; nlink_parser/TofsenseFrame0[] _nodes
    (apply #'+ (send-all _nodes :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; nlink_parser/TofsenseFrame0[] _nodes
     (write-long (length _nodes) s)
     (dolist (elem _nodes)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; nlink_parser/TofsenseFrame0[] _nodes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _nodes (let (r) (dotimes (i n) (push (instance nlink_parser::TofsenseFrame0 :init) r)) r))
     (dolist (elem- _nodes)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get nlink_parser::TofsenseCascade :md5sum-) "6f5a4318b44b44ec8258733a82bf1f6c")
(setf (get nlink_parser::TofsenseCascade :datatype-) "nlink_parser/TofsenseCascade")
(setf (get nlink_parser::TofsenseCascade :definition-)
      "TofsenseFrame0[] nodes

================================================================================
MSG: nlink_parser/TofsenseFrame0
uint8 id
uint32 system_time
float32 dis
uint8 dis_status
uint16 signal_strength

")



(provide :nlink_parser/TofsenseCascade "6f5a4318b44b44ec8258733a82bf1f6c")


