from django.shortcuts import render
from django.http import HttpResponse
# Create your views here.


# data = {"1": True, "2": False, "3": False, "4": False, "5": False, "6": False, "7": False, "8": False, "9": False, "10": False}
data = {"1": True}




def access(request, id):
    return HttpResponse(id)

def render_manageport(request):
    if request.method == 'POST':
        print('es')
    
    # print("no")
    # print(request)
    return render(request, 'manageport/index.html', {
        "data_list":data
    })

def render_404(request, string):
    return HttpResponse("<h1>error 404<h1>")