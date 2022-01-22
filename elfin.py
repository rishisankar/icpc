def partition_timestamps(ts: List[float], threshold: int) -> List[MRMSnippet]:
    """Return list of MRMSnippets corresponding to partition of *sorted* array of MRM
    packet timestamps based on threshold in seconds (i.e. timestamps are considered part
    of the same snippet if they differ by less than the threshold).

    Uses bisect module to find snippet boundaries in ~O(k*log(n)), where k is number of
    partitions in the end. This is faster than scanning linearly and finding time deltas
    to define snippets/intervals.
    """

    snippets: List[MRMSnippet] = []

    i = 0
    while i < len(ts):
      # find index of rightmost value <= (current + threshold)
      j = bisect.bisect_right(ts, ts[i] + threshold) - 1
      cur = i
      while cur < j:
        cur = j
        j = bisect.bisect_right(ts, ts[cur] + threshold) - 1
      start_dt = dt.datetime.fromtimestamp(ts[i])
      end_dt = dt.datetime.fromtimestamp(ts[j])
      snippets.append(MRMSnippet(start_dt, end_dt, j - i + 1))
      i = j + 1

    return snippets
