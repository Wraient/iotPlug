from django.shortcuts import render
from django.http import HttpResponse
# Create your views here.


data = {"1": True}

def access(request, id):
    return HttpResponse(id)

def render_manageport(request):

    return render(request, 'manageport/index.html', {
        "data_list":data
    })


def render_404(request, string):
    return HttpResponse("<h1>error 404<h1>")