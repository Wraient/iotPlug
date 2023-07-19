from django.shortcuts import render
from django.http import HttpResponse
# Create your views here.

def access(request, id):
    return HttpResponse(id)

def render_manageport(request):
    return HttpResponse("<h1>WORK IN PROGRESS<h1>")

def render_404(request, string):
    return HttpResponse("<h1>error 404<h1>")