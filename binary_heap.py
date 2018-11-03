


INF = int(1e14)

def left(l, i):
    p = 2*i+1
    return p, l[p] if p < len(l) else INF

def right(l, i):
    p = 2*i+2
    return p, l[p] if p < len(l) else INF

def parent(l, i):
    p = (i-1) // 2
    return p, l[p]


def bubble_up(l, i):
    if i== 0:
        return

    p, pv = parent(l, i)

    if pv > l[i]:
        l[i], l[p] = l[p], l[i]
        bubble_up(l, p)

def bubble_down(l, i):
    if i >= len(l):
        return

    e, ev = left(l, i)
    d, dv = right(l, i)

    m = min(l[i], ev, dv)
    if m == l[i]:
        return

    if m == ev:
        l[i], l[e] = l[e], l[i]
        return bubble_down(l, e)

    l[i], l[d] = l[d], l[i]
    return bubble_down(l, d)


def extract_min(l):
    x = l[0]
    l[len(l)-1], l[0] = l[0], l[len(l)-1]
    l.pop()
    bubble_down(l, 0)
    return x

def heapify(l):
    for i in range(len(l)):
        bubble_up(l, i)


example =  [4, 5, 2, 3, 8, 1, 7, 6]

print(example)
heapify(example)

print(example)

print("-------------")
print(extract_min(example))
print(example)

print("-------------")
print(extract_min(example))
print(example)

print("-------------")
print(extract_min(example))
print(example)

print("-------------")
print(extract_min(example))
print(example)

print("-------------")
print(extract_min(example))
print(example)

print("-------------")
print(extract_min(example))
print(example)

print("-------------")
print(extract_min(example))
print(example)

print("-------------")
print(extract_min(example))
print(example)

