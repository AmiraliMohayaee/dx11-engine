#ifndef NON_COPYABLE_H_INCLUDED
#define NON_COPYABLE_H_INCLUDED

namespace DXEngine
{
	class NonCopyable
	{
	protected:
		NonCopyable() {} // protected so we can call from subclasses

	private:
		NonCopyable(const NonCopyable&);

		//private copy ctr and assignment opp; cannot be copied. No given defenitions
		NonCopyable& operator=(const NonCopyable&);
	};
}

#endif