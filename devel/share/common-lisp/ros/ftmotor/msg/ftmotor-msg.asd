
(cl:in-package :asdf)

(defsystem "ftmotor-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Flow" :depends-on ("_package_Flow"))
    (:file "_package_Flow" :depends-on ("_package"))
  ))