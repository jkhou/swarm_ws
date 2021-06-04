// Auto-generated. Do not edit!

// (in-package nlink_parser.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class LinktrackTag {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.role = null;
      this.id = null;
      this.pos_3d = null;
      this.dis_arr = null;
    }
    else {
      if (initObj.hasOwnProperty('role')) {
        this.role = initObj.role
      }
      else {
        this.role = 0;
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('pos_3d')) {
        this.pos_3d = initObj.pos_3d
      }
      else {
        this.pos_3d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('dis_arr')) {
        this.dis_arr = initObj.dis_arr
      }
      else {
        this.dis_arr = new Array(8).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LinktrackTag
    // Serialize message field [role]
    bufferOffset = _serializer.uint8(obj.role, buffer, bufferOffset);
    // Serialize message field [id]
    bufferOffset = _serializer.uint8(obj.id, buffer, bufferOffset);
    // Check that the constant length array field [pos_3d] has the right length
    if (obj.pos_3d.length !== 3) {
      throw new Error('Unable to serialize array field pos_3d - length must be 3')
    }
    // Serialize message field [pos_3d]
    bufferOffset = _arraySerializer.float32(obj.pos_3d, buffer, bufferOffset, 3);
    // Check that the constant length array field [dis_arr] has the right length
    if (obj.dis_arr.length !== 8) {
      throw new Error('Unable to serialize array field dis_arr - length must be 8')
    }
    // Serialize message field [dis_arr]
    bufferOffset = _arraySerializer.float32(obj.dis_arr, buffer, bufferOffset, 8);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LinktrackTag
    let len;
    let data = new LinktrackTag(null);
    // Deserialize message field [role]
    data.role = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [id]
    data.id = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [pos_3d]
    data.pos_3d = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [dis_arr]
    data.dis_arr = _arrayDeserializer.float32(buffer, bufferOffset, 8)
    return data;
  }

  static getMessageSize(object) {
    return 46;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nlink_parser/LinktrackTag';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4a4bf3020fbef59e2422a9233d276302';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 role
    uint8 id
    float32[3] pos_3d
    float32[8] dis_arr
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LinktrackTag(null);
    if (msg.role !== undefined) {
      resolved.role = msg.role;
    }
    else {
      resolved.role = 0
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.pos_3d !== undefined) {
      resolved.pos_3d = msg.pos_3d;
    }
    else {
      resolved.pos_3d = new Array(3).fill(0)
    }

    if (msg.dis_arr !== undefined) {
      resolved.dis_arr = msg.dis_arr;
    }
    else {
      resolved.dis_arr = new Array(8).fill(0)
    }

    return resolved;
    }
};

module.exports = LinktrackTag;
