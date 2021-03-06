#pragma once

#include <map>
#include "Animations/Joint/JointTransform.hpp"
#include "KeyframeData.hpp"

namespace acid
{
	/// <summary>
	/// Represents one keyframe of an animation. This contains the timestamp of the keyframe,
	/// which is the time (in seconds) from the start of the animation when this keyframe occurs.
	/// <para>
	/// It also contains the desired local-space transforms of all of the joints in the animated entity at this keyframe in the animation.
	/// The joint transforms are stored in a map, indexed by the name of the joint that they should be applied to.
	/// </para>
	/// </summary>
	class ACID_EXPORT Keyframe
	{
	private:
		Time m_timeStamp;
		std::map<std::string, JointTransform> m_pose;
	public:
		/// <summary>
		/// Creates a new keyframe at a timestamp.
		/// </summary>
		/// <param name="timeStamp"> The time that this keyframe occurs during the animation. </param>
		/// <param name="pose"> The local-space transforms for all the joints at this keyframe, indexed by the name of the joint that they should be applied to. </param>
		Keyframe(const Time &timeStamp, const std::map<std::string, JointTransform> &pose);

		/// <summary>
		/// Creates a new keyframe at a timestamp.
		/// </summary>
		/// <param name="data"> The data to load the keyframe from. </param>
		explicit Keyframe(const KeyframeData &data);

		/// <summary>
		/// Gets the time in seconds of the keyframe in the animation.
		/// </summary>
		/// <returns> The time in seconds. </returns>
		Time GetTimeStamp() const { return m_timeStamp; }

		/// <summary>
		/// Gets the desired local-space transforms of all the joints at this keyframe, of the animation,
		/// indexed by the name of the joint that they correspond to.
		/// </summary>
		/// <returns> The desired local-space transforms. </returns>
		std::map<std::string, JointTransform> GetPose() const { return m_pose; }
	};
}
