#pragma once

#include "Leap.h"

#include <algorithm>

using namespace Leap;

/**
 * Hand gesture recognizer that will return an array of matches against
 * a list of predefined finger and hand poses.
 */
class GestureMatcher
{
public:
    GestureMatcher();
    ~GestureMatcher();

    enum WhichHand
    {
        AnyHand,
        LeftHand,
        RightHand
    };

    enum GestureType
    {
        // Finger gestures (these would not throw your hand's orientation off much)
        TriggerFinger,           // bend your index finger as if pulling a trigger
        LowerFist,               // grab with your middle, ring, pinky fingers
        Pinch,                   // pinch with your thumb and index fingers
        Thumbpress,              // point the thumb towards the direction of your pinky

        // Hand gestures (these would significantly change the orientation of your hand)
        FlippingTheBird,         // flip someone off with your middle finger
		Point,					 // index finger exended, all other fingers bent
        RockOut,                     // pinky and index finger extended, middle and ring bent
        Victory,                 // V shape with your index, middle fingers, other fingers curled
        SpreadHand,              // flat hand, fingers spread
        ThumbUp,                 // thumb points up, remaining fingers form a fist
		Gun,					 // index finger and thumb exended, all other fingers bent
        ThumbInward,             // thumb points towards the left for the right hand and vice versa

        TODO_LiveLongAndProsper, // Spock's trademark greeting
        TODO_DiverOkay,          // Diver's "I'm Okay" sign.
        TODO_FistBump,           // a Fist Bump gesture

        // Two handed gestures
        Timeout,                 // both Hands form a T shape, signals a Timeout in sports
        TouchpadAxisX,           // Touchpad emulation: index finger of other hand points towards palm 
        TouchpadAxisY,           // Touchpad emulation: index finger of other hand points towards palm 

        NUM_GESTURES,

        INVALID_GESTURE = -1
    };

    // default orientation vectors with respect to the Leap's coordinate system
    // in Head Mounted Mode.
    static const Vector RightVector;
    static const Vector InVector;
    static const Vector UpVector;

    /**
     * Perform gesture detection and quantification for the specified hand.
     * If AnyHand is specified, the gesture classifications will be merged together (typically std::max)
     */
    bool MatchGestures(const Frame &frame, WhichHand which, float (&result)[NUM_GESTURES],
                       Vector right = RightVector, Vector in = InVector, Vector up = UpVector);

    /**
     * Map the GestureType enum to a string name.
     */
    static std::string GestureNameFromType(GestureType gesture)
    {
        switch (gesture)
        {
        case TriggerFinger: return "TriggerFinger"; break;
        case LowerFist: return "LowerFist"; break;
        case Pinch: return "Pinch"; break;
        case Thumbpress: return "Thumbpress"; break;
        case Point: return "Point"; break;
        case RockOut: return "RockOut"; break;
        case FlippingTheBird: return "FlippingTheBird"; break;
        case Victory: return "Victory"; break;
        case SpreadHand: return "SpreadHand"; break;
        case ThumbUp: return "ThumbUp"; break;
        case Gun: return "Gun"; break;
        case Timeout: return "Timeout"; break;
        case TouchpadAxisX: return "TouchpadAxisX"; break;
        case TouchpadAxisY: return "TouchpadAxisY"; break;
        default: return ""; break;
        }
    }

    /**
     * Map a string name to the GestureType enum. Case Sensitive!
     * Be sure to check the return code for INVALID_GESTURE
     */
    GestureType GestureTypeFromName(std::string &name)
    {
             if (name.compare("TriggerFinger") == 0) return TriggerFinger;
        else if (name.compare("LowerFist") == 0) return LowerFist;
        else if (name.compare("Pinch") == 0) return Pinch;
        else if (name.compare("Thumbpress") == 0) return Thumbpress;
        else if (name.compare("Point") == 0) return Point;
        else if (name.compare("RockOut") == 0) return RockOut;
        else if (name.compare("FlippingTheBird") == 0) return FlippingTheBird;
        else if (name.compare("Victory") == 0) return Victory;
        else if (name.compare("SpreadHand") == 0) return SpreadHand;
        else if (name.compare("ThumbUp") == 0) return ThumbUp;
        else if (name.compare("Gun") == 0) return Gun;
        else if (name.compare("Timeout") == 0) return Timeout;
        else if (name.compare("TouchpadAxisX") == 0) return TouchpadAxisX;
        else if (name.compare("TouchpadAxisY") == 0) return TouchpadAxisY;
        else return INVALID_GESTURE;
    }

protected:

    // some utility functions

    float maprange(float input, float minimum, float maximum)
    {
        float mapped = (input - minimum) / (maximum - minimum);
        return std::max(std::min(mapped, 1.0f), 0.0f);
    }

    void merge(float &result, float value)
    {
        result = std::max(result, value);
    }

protected:

    // place state variables here (if any)
};
