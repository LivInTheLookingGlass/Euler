# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

from os import environ, path, sep
from subprocess import CalledProcessError, check_call
from sys import path as sys_path

from sphinxcontrib.domaintools import custom_domain
if 'TERMUX_VERSION' not in environ:
    from ghlinguist import linguist
    import matplotlib.pyplot as plt

basedir = path.abspath(path.join(path.dirname(__file__), '..'))
sys_path.insert(0, basedir)
sys_path.insert(0, basedir + sep + 'python')
js_source_path = basedir + sep + 'javascript'

project = 'Euler'
copyright = '2024, Olivia Appleton'
author = 'Olivia Appleton'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.duration',
    'sphinx.ext.extlinks',
    'sphinx.ext.githubpages',
    'sphinx.ext.graphviz',
    'sphinx.ext.inheritance_diagram',
    'sphinx.ext.intersphinx',
    'sphinx.ext.mathjax',
    'sphinx.ext.todo',
    'sphinx-favicon',
    'sphinx-notfound-page',
    # 'breathe',
    # 'javasphinx',
    # 'sphinx_autodoc_typehints',
    # 'sphinx_pyreverse',
    'sphinx_csharp.csharp',
    'sphinxcontrib.makedomain',
]

try:
    check_call(['rpm-ostree', '--version'])
    IS_SILVERBLUE = True
except Exception:
    IS_SILVERBLUE = False

if 'TERMUX_VERSION' not in environ and not IS_SILVERBLUE:
    extensions.append('sphinx_js')

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

language = 'english'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

favicons = [
    {
        "rel": "apple-touch-icon",
        "href": "https://projecteuler.net/favicons/apple-touch-icon.png",
    },
    {"href": "https://projecteuler.net/favicons/favicon-32x32.png"},
    {"href": "https://projecteuler.net/favicons/favicon-16x16.png"},
    {"href": "https://projecteuler.net/favicons/favicon.ico"},
]

# -- Options for todo extension ----------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/extensions/todo.html#configuration

todo_include_todos = True

extlinks = {'prob': ('https://projecteuler.net/problem=%s',
                     'Problem #%s')}

intersphinx_mapping = {
    'python':           ('https://docs.python.org/3', None),
    'matplotlib':       ('https://matplotlib.org/stable/', None),
    'Sphinx':           ('https://www.sphinx-doc.org/en/stable/', None),
    'sortedcontainers': ('https://grantjenks.com/docs/sortedcontainers/', None),
    'u-msgpack-python': ('https://u-msgpack-python.readthedocs.io/en/latest/', None),
    'pytest':           ('https://docs.pytest.org/en/stable/', None),
    'coverage':         ('https://coverage.readthedocs.io/en/latest/', None)
}

def setup(app):
    if 'TERMUX_VERSION' not in environ:
        langs = linguist(basedir)
        labels = [lang[0] for lang in langs]
        sizes = [lang[1] for lang in langs]
        fig, ax = plt.subplots()
        ax.pie(sizes, labels=labels, autopct='%1.1f%%', labeldistance=None, pctdistance=0.8)
        plt.legend(title='Languages', loc='center left', bbox_to_anchor=(1, 0))
        plt.savefig('languages.svg', transparent=True)

    app.add_domain(custom_domain(
        'RustDomain',
        'rust',
        'Rust',
        {
            'fn': {
            },
            'struct': {
            },
            'var': {
            },
        }
    ))

