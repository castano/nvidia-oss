

#if 0

/// <summary>
/// A very lightweight reader/writer lock.  It uses a single word of memory, and
/// only spins when contention arises (no events are necessary).
/// </summary>
class ReaderWriterSpinLockPerProc
{
 
    public void EnterReadLock()
	{
        SPW sw = new SPW();
        int tid = readLockIndex();
 
        // Wait until there are no writers.
        while (true) {
            while (m_writer == 1) sw.backoff();
 
            // Try to take the read lock.
            Atomic::Increment(&m_readers[tid].m_taken);

            if (m_writer == 0) {
                // Success, no writer, proceed.
                break;
            }
 
            // Back off, to let the writer go through.
            Atomic::decrement(&m_readers[tid].m_taken);
        }
    }
 
    public void EnterWriteLock() {
        SPW sw = new SPW();
        while (true) {
            if (m_writer == 0 && Interlocked.Exchange(ref m_writer, 1) == 0) {
                // We now hold the write lock, and prevent new readers.
                // But we must ensure no readers exist before proceeding.
                for (int i = 0; i < m_readers.Length; i++)
                    while (m_readers[i].m_taken != 0) sw.SpinOnce();
 
                break;
            }
 
            // We failed to take the write lock; wait a bit and retry.
            sw.SpinOnce();
        }
    }
 
    public void ExitReadLock() {
        // Just note that the current reader has left the lock.
        Interlocked.Decrement(ref m_readers[ReadLockIndex].m_taken);
    }
 
    public void ExitWriteLock() {
        // No need for a CAS.
        m_writer = 0;
    }

private:

	private int readLockIndex()
	{
        return Thread::threadId() % m_readers.count();
	}

    volatile int m_writer;
    volatile Array<ReadEntry> m_readers; // = new ReadEntry[Environment.ProcessorCount * 16];

    [StructLayout(LayoutKind.Sequential, Size = 128)]
    struct ReadEntry {
        internal volatile int m_taken;
    }
	
};

#endif // 0