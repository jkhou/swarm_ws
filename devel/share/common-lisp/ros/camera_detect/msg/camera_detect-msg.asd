
(cl:in-package :asdf)

(defsystem "camera_detect-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "zzw" :depends-on ("_package_zzw"))
    (:file "_package_zzw" :depends-on ("_package"))
  ))