// Auto-generated. Do not edit!

// (in-package nlink_parser.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class SwarmPos {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.swarm_pos = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('swarm_pos')) {
        this.swarm_pos = initObj.swarm_pos
      }
      else {
        this.swarm_pos = new Array(16).fill(new geometry_msgs.msg.Point());
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SwarmPos
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Check that the constant length array field [swarm_pos] has the right length
    if (obj.swarm_pos.length !== 16) {
      throw new Error('Unable to serialize array field swarm_pos - length must be 16')
    }
    // Serialize message field [swarm_pos]
    obj.swarm_pos.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SwarmPos
    let len;
    let data = new SwarmPos(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [swarm_pos]
    len = 16;
    data.swarm_pos = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.swarm_pos[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 384;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nlink_parser/SwarmPos';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1c5deeae29fc99ca2d59a905d86e689d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    geometry_msgs/Point[16] swarm_pos
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
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SwarmPos(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.swarm_pos !== undefined) {
      resolved.swarm_pos = new Array(16)
      for (let i = 0; i < resolved.swarm_pos.length; ++i) {
        if (msg.swarm_pos.length > i) {
          resolved.swarm_pos[i] = geometry_msgs.msg.Point.Resolve(msg.swarm_pos[i]);
        }
        else {
          resolved.swarm_pos[i] = new geometry_msgs.msg.Point();
        }
      }
    }
    else {
      resolved.swarm_pos = new Array(16).fill(new geometry_msgs.msg.Point())
    }

    return resolved;
    }
};

module.exports = SwarmPos;
